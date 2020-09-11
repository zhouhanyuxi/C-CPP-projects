#ifndef CATALOG_H
#define CATALOG_H

#define MAX_TREE_SIZE 100

typedef struct Catalog
{
	char key[20];
	char caption[80];
	char parent[20];
}Catalog;
typedef struct CatalogTree
{
	Catalog Node[MAX_TREE_SIZE];
	int root;
	int num;
}CatalogTree;

CatalogTree CreatCatalogTree();
void PrintCatalogTree(CatalogTree tree);
void PreOrder(CatalogTree tree,int k,int level);

#endif