#include "main.h"
#include "catalog.h"

CatalogTree CreatCatalogTree()
{
	int i = 0;
	FILE *fp;
	CatalogTree C;

	if((fp = fopen("catalog.dat","rb")) == NULL)
	{
		printf("�ļ���ʧ�ܣ��޷����������Ϣ\n");
	}else{
		fread(&C.Node[i],sizeof(Catalog),1,fp);//��ȡ����Ŀ¼��Ϣ
		while(!feof(fp))
		{
			i++;
			fread(&C.Node[i],sizeof(Catalog),1,fp);
		}
		C.num = i;
		C.root = 0;
		printf("������Ϣ����ɹ�\n");
		fclose(fp);
		PrintCatalogTree(C);//�������Ŀ¼��
		return C;
	}
}
void PrintCatalogTree(CatalogTree tree)
{
	int level = 1;

	PreOrder(tree,0,level);
}
//�ȸ�����
void PreOrder(CatalogTree tree,int k,int level)
{
	int i,j,m = 0;

	for(i=1; i<level; i++)
	{
		printf("   ");
	}
	printf("|---%s %s\n",tree.Node[k].caption,tree.Node[k].key);//������ڵ�
	for(j=k+1; j<tree.num; j++)
	{
		if((strcmp(tree.Node[j].parent,tree.Node[k].key)) == 0)
		{
			if(m == 0)
			{
				PreOrder(tree,j,++level);//�����һ�����ӽڵ�
				m ++;
			}else{
				PreOrder(tree,j,level);//����������ӽڵ�
			}
		}
	}
}