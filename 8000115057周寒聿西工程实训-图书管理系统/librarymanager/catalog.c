#include "main.h"
#include "catalog.h"

CatalogTree CreatCatalogTree()
{
	int i = 0;
	FILE *fp;
	CatalogTree C;

	if((fp = fopen("catalog.dat","rb")) == NULL)
	{
		printf("文件打开失败，无法导入分类信息\n");
	}else{
		fread(&C.Node[i],sizeof(Catalog),1,fp);//读取分类目录信息
		while(!feof(fp))
		{
			i++;
			fread(&C.Node[i],sizeof(Catalog),1,fp);
		}
		C.num = i;
		C.root = 0;
		printf("分类信息导入成功\n");
		fclose(fp);
		PrintCatalogTree(C);//输出分类目录树
		return C;
	}
}
void PrintCatalogTree(CatalogTree tree)
{
	int level = 1;

	PreOrder(tree,0,level);
}
//先根遍历
void PreOrder(CatalogTree tree,int k,int level)
{
	int i,j,m = 0;

	for(i=1; i<level; i++)
	{
		printf("   ");
	}
	printf("|---%s %s\n",tree.Node[k].caption,tree.Node[k].key);//输出父节点
	for(j=k+1; j<tree.num; j++)
	{
		if((strcmp(tree.Node[j].parent,tree.Node[k].key)) == 0)
		{
			if(m == 0)
			{
				PreOrder(tree,j,++level);//输出第一个孩子节点
				m ++;
			}else{
				PreOrder(tree,j,level);//输出其他孩子节点
			}
		}
	}
}