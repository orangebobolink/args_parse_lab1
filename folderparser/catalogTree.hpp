#pragma once
#include <vector>
#include <iostream>
#include <thread>

struct Catalog;

struct File
{
public:
	std::string path;
	std::string name;
};

struct CatalogContent
{
public:
	std::vector<File*> files;
	std::vector<Catalog*> catalogs;
	CatalogContent() = default;
};

struct Catalog
{
public:
	std::thread::id threadId;
	std::string path;
	std::string name;
	CatalogContent* content;
	void print(int space = 0) const;

	Catalog(std::string path, std::string name, CatalogContent* content = nullptr)
		: path(std::move(path)), name(std::move(name)), content(content ? content : new CatalogContent()) {}
	Catalog(std::string path, CatalogContent* content = nullptr)
		: path(std::move(path)), content(content ? content : new CatalogContent())
	{
		name = this->path.substr(this->path.find_last_of('\\') + 1);
	}
};

class CatalogTree
{
	Catalog* _catalog;
public:
	CatalogTree(Catalog* catalog)
		:_catalog(catalog) {}

	Catalog* getCatalog() const { return _catalog; }
	void print() const;
};