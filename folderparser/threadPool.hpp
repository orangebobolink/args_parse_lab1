#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadPool;


/**
 * \brief Абстрактный класс для задач
 */
class Task {
public:
    Task(ThreadPool& pool) : pool(pool) {}
    virtual ~Task() = default;
    virtual void execute() = 0;
protected:
    ThreadPool& pool;
};

/**
 * \brief Реализация thread pool
 */
class ThreadPool {
private:
	/**
     * \brief Существующие потоки.
     */
    std::vector<std::thread> workers;
    /**
     * \brief Задчи.
     */
    std::queue<Task*> tasks;
    std::mutex queue_mutex;
    /**
    * \brief Условная переменная для ожидания задач.
    */
    std::condition_variable condition;
    bool stop;

public:
    ThreadPool(int numThreads);
    ~ThreadPool();

	void enqueue(Task* task);
};
 
