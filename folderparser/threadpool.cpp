#include "threadPool.hpp"

ThreadPool::ThreadPool(int numThreads) : stop(false)
{
	for (int i = 0; i < numThreads; ++i)
		workers.emplace_back(
			[this]
			{
				/// Поток ожидает задачу.
				while (true)
				{
					std::unique_lock<std::mutex> lock(this->queue_mutex);
					/// Освободим если threadpool остановлен, либо есть какая-то задача
					this->condition.wait(lock,
						[this] { return this->stop || !this->tasks.empty(); });
					if (this->stop && this->tasks.empty())
						return;
					/// Берем задчу.
					auto task = this->tasks.front();
					this->tasks.pop();

					lock.unlock();

					task->execute();
				}
			}
	);
}

inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers)
        worker.join();
}

void ThreadPool::enqueue(Task* task)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    if (stop)
        throw std::runtime_error("Thread pool оставновлен, но мы пытаемся выполнить задачу.");
    tasks.emplace(task);
    condition.notify_one();
}
