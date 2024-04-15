#include <filesystem>
#include <iostream>

#include "catalogTree.hpp"
#include "threadPool.hpp"
#include <args/arg.hpp>
#include <args_parse/parser.hpp>

std::vector<std::unique_ptr<args::Arg>> getTestArgs();
args_parse::Parser getParser(const int argc, const char** argv);

class CatalogTask : public Task {
private:
    Catalog* _catalog;
public:
    CatalogTask(ThreadPool& pool, Catalog* catalog)
	: Task(pool), _catalog(catalog) {}
    void execute() override {
        /// Устанавливаем id потока 
        _catalog->threadId = std::this_thread::get_id();

        std::filesystem::path path(_catalog->path);
        std::filesystem::directory_iterator end_itr;

        for (std::filesystem::directory_iterator itr(path); itr != end_itr; ++itr) {
            /// Это каталог
            if (itr->is_directory()) {
                Catalog* catalog = new Catalog(itr->path().string(), itr->path().filename().string());
                _catalog->content->catalogs.push_back(catalog);

                pool.enqueue(new CatalogTask(pool, catalog));
            }
            else {
                /// Это файл
                File* file = new File;
                file->path = itr->path().parent_path().string();
                file->name = itr->path().filename().string();
                _catalog->content->files.push_back(file);
            }
        }
    }
};

std::string path;
int threadCount = 1;
int sleepTime = 1;

int main(int argc, const char** argv)
{
    auto parser = getParser(argc, argv);
    auto result = parser.parse();

    if (!result.isOk()) std::cout << result.error << std::endl;

    if(path == "")
    {
        std::cout << "Ведите путь" << std::endl;
        return 0;
    }

    Catalog* catalog = new Catalog(path);
    CatalogTree tree(catalog);
	ThreadPool threadPool(threadCount);

    threadPool.enqueue(new CatalogTask(threadPool, tree.getCatalog()));

    std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
    tree.print();

    return 0;
}

args_parse::Parser getParser(const int argc, const char** argv)
{
    args_parse::Parser parser(argc, argv);
    auto args = std::move(getTestArgs());

    for (auto& arg : args)
    {
        parser.addArg(std::move(arg));
    }

    return parser;
}

auto stringValidator = args::Validator<std::string>();
auto intValidator = args::Validator<int>();
auto boolValidator = args::Validator<bool>();

types::Result<bool> helpFunc(const args::Arg* arg, const args_parse::Parser* parser)
{
    auto args = parser->getArgs();

    for (auto& arg : args)
    {
        std::cout << "--" << arg->getLongArg() << std::setw(50) << arg->getDescription() << std::endl;
        std::cout << "-" << arg->getShortArg() << std::endl;
    }

    return { true };
}
 

types::Result<bool> pathFunc(const args::Arg* arg, const args_parse::Parser* parser)
{
    args::ValueArg<std::string>* d
		= const_cast<args::ValueArg<std::string>*>(dynamic_cast<const args::ValueArg<std::string>*>(arg));
    path = d->getValue();
    return { true };
}

types::Result<bool> countFunc(const args::Arg* arg, const args_parse::Parser* parser)
{
    args::ValueArg<int>* d
        = const_cast<args::ValueArg<int>*>(dynamic_cast<const args::ValueArg<int>*>(arg));
    threadCount = d->getValue();

    return { true };
}

types::Result<bool> sleepFunc(const args::Arg* arg, const args_parse::Parser* parser)
{
    args::ValueArg<int>* d
        = const_cast<args::ValueArg<int>*>(dynamic_cast<const args::ValueArg<int>*>(arg));
    sleepTime = d->getValue();

    return { true };
}

std::vector<std::unique_ptr<args::Arg>> getTestArgs()
{
    std::vector< std::unique_ptr<args::Arg>> args;

    args.push_back(std::make_unique<args::EmptyArg>('h', "help",
        "help argument",
        helpFunc));
    args.push_back(std::make_unique<args::ValueArg<std::string>>('p', "path",
        "path for start catalog",
        pathFunc, &stringValidator));
    args.push_back(std::make_unique<args::ValueArg<int>>('c', "count",
        "count of threads in thread pool",
        countFunc, &intValidator));
    args.push_back(std::make_unique<args::ValueArg<int>>('t', "time",
        "time for sleep",
        sleepFunc, &intValidator));


    return args;
}