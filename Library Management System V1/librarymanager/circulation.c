#include"circulation.h"
#include"catalog.h"
#include"main.h"

void CirculationMenu()
{
	int choice;
	printf("\n-----------按回车键继续操作------------\n");
	fflush(stdin);
	getchar();
	system("cls");

	printf("-------------------------------------------\n");
	printf("               图书流通管理\n");
	printf("-------------------------------------------\n");
	printf("*             1.图书分类浏览              *\n");
	printf("*             2.图书检索                  *\n");
	printf("*             3.借书                      *\n");
	printf("*             4.还书                      *\n");
	printf("*             5.续借(暂未开放)            *\n");
	printf("*             6.查询借阅记录              *\n");
	printf("*             0.返回主菜单                *\n");
	printf("-------------------------------------------\n");
	printf("请输入您选择的序号:");
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

//图书分类浏览                                      未查完
void BrowseBookCatalog()
{
	BookList B;
	char key[20];
	int i,flag = 1;

	CreatCatalogTree();
	B = CreatBookList();
	printf("请输入要浏览的图书分类号:");
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
		printf("未找到该种分类的图书\n");
	}
}

//读取书本信息
BookList CreatBookList(  ) 
{
	BookList B;
	FILE *fp = NULL;
	int i=0;   //图书记录个数；
	char ISBN[50];        //ISBN号
	char Title[200];      //书名
	char Author[200];      //作者
	char Publisher[100];   //出版社
	char Date[20];       //出版日期
	float Price;         //价格
	char CatalogNum[200];//分类编号

	B.Node=(Book *)malloc(sizeof(Book)*MAX_BOOK_SIZE);

	if((fp=fopen("books.txt","r"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	else
	{
		fscanf(fp,"%[^\t]",ISBN);  //先读，再判断feof(fp)，防止文件尾多读一次数据
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

			i++;                       //从B.Node[1]开始存放
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
		B.Num=i; //图书个数

		fclose(fp);

		return (B);

	}


}

void FindBook()
{
	int choice;

	printf("请选择查询方式:1.ISBN号 2.书名 3.作者 4.出版社 0.返回\n");
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

//通过ISBN查找书籍
void FindISBN()
{
	BookList B;
	char ISBN[50];

	B = CreatBookList();
	printf("请输入书籍的ISBN号:\n");
	scanf("%s",ISBN);
	B = SelectSort(B);
	SearchISBN(B,ISBN);
}

//选择排序将书籍按ISBN排序
BookList SelectSort(BookList B)
{
	Book temp;
	int i,j,k;

	//排序
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

//从已排序的ISBN号中查找
Book SearchISBN(BookList B,char ISBN[50])
{
	int mid,low = 1,high = B.Num;

	//查找
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
		printf("\n未找到该书籍\n");
	}
}

//通过书名查找书籍
void FindTitle()
{
	BookList B;
	char title[200];
	int i,flag=1;

	B = CreatBookList();
	printf("请输入书籍的名称:\n");
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
		printf("\n未找到该书籍\n");
	}
}

//通过作者查找书籍
void FindAuthor()
{
	BookList B;
	char author[200];
	int i,flag=1;

	B = CreatBookList();
	printf("请输入作者名:\n");
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
		printf("\n未找到该作者\n");
	}
}

//通过出版社查找书籍
void FindPublisher()
{
	BookList B;
	char publisher[200];
	int i,flag=1;

	B = CreatBookList();
	printf("请输入出版社名称:\n");
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
		printf("\n未找到该出版社\n");
	}
}