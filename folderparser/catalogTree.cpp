#include "catalogTree.hpp"

void Catalog::print(int space) const
{
    std::thread::id nullThreadId;
    if(this->threadId == nullThreadId)
    {
        return;
    }
    std::cout << std::string(space, ' ') << this->name << ' ' << this->threadId << std::endl;
    for (auto item : this->content->files) {
        std::cout << std::string(space + 2, ' ') << item->name << std::endl;
    }
    for (auto item : this->content->catalogs) {
        item->print(space + 2);
    }
}

void CatalogTree::print() const
{
	_catalog->print();
}
