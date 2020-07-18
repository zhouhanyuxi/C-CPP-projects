#include"circulation.h"
#include"catalog.h"
#include"main.h"

void CirculationMenu()
{
	int choice;
	printf("\n-----------���س�����������------------\n");
	fflush(stdin);
	getchar();
	system("cls");

	printf("-------------------------------------------\n");
	printf("               ͼ����ͨ����\n");
	printf("-------------------------------------------\n");
	printf("*             1.ͼ��������              *\n");
	printf("*             2.ͼ�����                  *\n");
	printf("*             3.����                      *\n");
	printf("*             4.����                      *\n");
	printf("*             5.����(��δ����)            *\n");
	printf("*             6.��ѯ���ļ�¼              *\n");
	printf("*             0.�������˵�                *\n");
	printf("-------------------------------------------\n");
	printf("��������ѡ������:");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
			BrowseBookCatalog();
			CirculationMenu();
			break;
		case 2:
			FindBook();
			CirculationMenu();
			break;
		case 3:
			LendBook();
			CirculationMenu();
			break;
		case 4:
			ReturnBook();
			CirculationMenu();
			break;
		case 5:
			RenewBook();
			CirculationMenu();
			break;
		case 6:
			FindLendInfo();
			CirculationMenu();
			break;
		case 0:
			MainMenu();
			break;
	}
}

//ͼ��������                                      δ����
void BrowseBookCatalog()
{
	BookList B;
	char key[20];
	int i,flag = 1;

	CreatCatalogTree();
	B = CreatBookList();
	printf("������Ҫ�����ͼ������:");
	scanf("%s",key);
	for(i=0; i<B.Num; i++)
	{
		if(memcmp(B.Node[i].CatalogNum,key,strlen(key)) == 0)
		{
			printf("\n%s\t%s\t%s\t%s\t%s\t%f\t%s\n",B.Node[i].ISBN,B.Node[i].title,B.Node[i].author,B.Node[i].publisher,B.Node[i].date,B.Node[i].price,B.Node[i].CatalogNum);
			flag = 0;
		}
	}
	if(flag)
	{
		printf("δ�ҵ����ַ����ͼ��\n");
	}
}

//��ȡ�鱾��Ϣ
BookList CreatBookList(  ) 
{
	BookList B;
	FILE *fp = NULL;
	int i=0;   //ͼ���¼������
	char ISBN[50];        //ISBN��
	char Title[200];      //����
	char Author[200];      //����
	char Publisher[100];   //������
	char Date[20];       //��������
	float Price;         //�۸�
	char CatalogNum[200];//������

	B.Node=(Book *)malloc(sizeof(Book)*MAX_BOOK_SIZE);

	if((fp=fopen("books.txt","r"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fscanf(fp,"%[^\t]",ISBN);  //�ȶ������ж�feof(fp)����ֹ�ļ�β���һ������
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Title);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Author);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Publisher);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",Date);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%f",&Price);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\n]",CatalogNum);
		fscanf(fp,"%*c");	


		while(!feof(fp))   
		{

			i++;                       //��B.Node[1]��ʼ���
			strcpy(B.Node[i].ISBN,ISBN);
			strcpy(B.Node[i].title,Title);
			strcpy(B.Node[i].author,Author);
			strcpy(B.Node[i].publisher,Publisher);	
			strcpy(B.Node[i].date,Date);
			B.Node[i].price=Price;
			strcpy(B.Node[i].CatalogNum,CatalogNum);	


			fscanf(fp,"%[^\t]",ISBN);
			fscanf(fp,"%*[\t]");

			fscanf(fp,"%[^\t]",Title);
			fscanf(fp,"%*[\t]");

			fscanf(fp,"%[^\t]",Author);
			fscanf(fp,"%*[\t]");

			fscanf(fp,"%[^\t]",Publisher);
			fscanf(fp,"%*[\t]");

			fscanf(fp,"%[^\t]",Date);
			fscanf(fp,"%*[\t]");

			fscanf(fp,"%f",&Price);
			fscanf(fp,"%*[\t]");

			fscanf(fp,"%[^\n]",CatalogNum);
			fscanf(fp,"%*c");

		}
		B.Num=i; //ͼ�����

		fclose(fp);

		return (B);

	}


}

void FindBook()
{
	int choice;

	printf("��ѡ���ѯ��ʽ:1.ISBN�� 2.���� 3.���� 4.������ 0.����\n");
	scanf("%1d",&choice);
	switch(choice)
	{
		case 1:
			FindISBN();
			break;
		case 2:
			FindTitle();
			break;
		case 3:
			FindAuthor();
			break;
		case 4:
			FindPublisher();
			break;
		case 0:
			CirculationMenu();
			break;
	}
}

//ͨ��ISBN�����鼮
void FindISBN()
{
	BookList B;
	char ISBN[50];

	B = CreatBookList();
	printf("�������鼮��ISBN��:\n");
	scanf("%s",ISBN);
	B = SelectSort(B);
	SearchISBN(B,ISBN);
}

//ѡ�������鼮��ISBN����
BookList SelectSort(BookList B)
{
	Book temp;
	int i,j,k;

	//����
	for(i=1; i<=(B.Num-1); i++)
	{
		k = i;
		for(j=i+1; j<=B.Num; j++)
		{
			if(strcmp(B.Node[k].ISBN,B.Node[j].ISBN) > 0)
			{
				k = j;
			}
		}
		if(k != i)
		{
			temp = B.Node[k];
			B.Node[k] = B.Node[i];
			B.Node[i] = temp;
		}
	}

	return B;
}

//���������ISBN���в���
Book SearchISBN(BookList B,char ISBN[50])
{
	int mid,low = 1,high = B.Num;

	//����
	while(low < high)
	{
		mid = (low + high)/2;
		if(strcmp(B.Node[mid].ISBN,ISBN) > 0)
		{
			high = mid - 1;
		}
		if(strcmp(B.Node[mid].ISBN,ISBN) < 0)
		{
			low = mid + 1;
		}
		if(strcmp(B.Node[mid].ISBN,ISBN) == 0)
			break;
	}
	if(strcmp(B.Node[mid].ISBN,ISBN) == 0)
	{
		printf("\n%s\t%s\t%s\t%s\t%s\t%f\t%s\n",B.Node[mid].ISBN,B.Node[mid].title,B.Node[mid].author,B.Node[mid].publisher,B.Node[mid].date,B.Node[mid].price,B.Node[mid].CatalogNum);
		return B.Node[mid];
	}else{
		printf("\nδ�ҵ����鼮\n");
	}
}

//ͨ�����������鼮
void FindTitle()
{
	BookList B;
	char title[200];
	int i,flag=1;

	B = CreatBookList();
	printf("�������鼮������:\n");
	fflush(stdin);
	gets(title);
	for(i=1; i<=B.Num; i++)
	{
		if(strstr(B.Node[i].title,title) != NULL)
		{
			printf("\n%s\t%s\t%s\t%s\t%s\t%f\t%s\n",B.Node[i].ISBN,B.Node[i].title,B.Node[i].author,B.Node[i].publisher,B.Node[i].date,B.Node[i].price,B.Node[i].CatalogNum);
			flag = 0;
		}
	}
	if(flag)
	{
		printf("\nδ�ҵ����鼮\n");
	}
}

//ͨ�����߲����鼮
void FindAuthor()
{
	BookList B;
	char author[200];
	int i,flag=1;

	B = CreatBookList();
	printf("������������:\n");
	fflush(stdin);
	gets(author);
	for(i=1; i<=B.Num; i++)
	{
		if(strstr(B.Node[i].author,author) != NULL)
		{
			printf("\n%s\t%s\t%s\t%s\t%s\t%f\t%s\n",B.Node[i].ISBN,B.Node[i].title,B.Node[i].author,B.Node[i].publisher,B.Node[i].date,B.Node[i].price,B.Node[i].CatalogNum);
			flag = 0;
		}
	}
	if(flag)
	{
		printf("\nδ�ҵ�������\n");
	}
}

//ͨ������������鼮
void FindPublisher()
{
	BookList B;
	char publisher[200];
	int i,flag=1;

	B = CreatBookList();
	printf("���������������:\n");
	fflush(stdin);
	gets(publisher);
	for(i=1; i<=B.Num; i++)
	{
		if(strstr(B.Node[i].publisher,publisher) != NULL)
		{
			printf("\n%s\t%s\t%s\t%s\t%s\t%f\t%s\n",B.Node[i].ISBN,B.Node[i].title,B.Node[i].author,B.Node[i].publisher,B.Node[i].date,B.Node[i].price,B.Node[i].CatalogNum);
			flag = 0;
		}
	}
	if(flag)
	{
		printf("\nδ�ҵ��ó�����\n");
	}
}