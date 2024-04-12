#pragma once
#include <vector>

struct Catalog;

struct File
{
public:
	public path;
	public name;
};

struct CatalogContent
{
public:
	std::vector<File*> files;
	std::vector<Catalog*> catalogs;
};

struct Catalog
{
public:
	public path;
	public name;
	CatalogContent* content;
};

class CatalogTree
{
	Catalog* _catalog;

public:
	void print()
	{

	}
};