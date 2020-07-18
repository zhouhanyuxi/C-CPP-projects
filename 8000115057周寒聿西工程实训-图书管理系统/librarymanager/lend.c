
#include"main.h"
#include"reader.h"
#include"circulation.h"
#include<time.h>
#include<malloc.h>

//借书
void LendBook()
{
	int flag=0;
	int booknum;
	char ISBN[50];
	ReaderLink *p;
	BookList B;
	Book book;
	LendInfo L;
	char LendDate[20];char LastDate[20];
	time_t t;
	
	t = time(NULL);
	strftime(LendDate,sizeof(LendDate),"%Y-%m-%d",localtime(&t));//获取借阅时间
	t = t + MAX_DAY_LEND*24*60*60;
	strftime(LastDate,sizeof(LastDate),"%Y-%m-%d",localtime(&t));//获取应还时间

	p = FindReader_code();//找到该读者

	if(p == NULL)
	{
		flag = 1;
	}else{
		booknum = LendBookNum(p->code);
		if(p->tag == 1)
		{
			printf("该证件已挂失，无法借阅\n");
			flag = 1;
		}else if(booknum > MAX_BOOK_LEND)
		{
			printf("已经借满%d本，无法再借阅\n",MAX_BOOK_LEND);
			flag = 1;
		}else{
			printf("-----------图书借阅，输入#号及回车结束----------\n");
			printf("请输入书籍的ISBN:\n");
			scanf("%s",ISBN);
			while((strcmp(ISBN,"#") != 0) && (booknum < MAX_BOOK_LEND))
			{
				B = CreatBookList();
				B = SelectSort(B);
				book = SearchISBN(B,ISBN);
				if(strcmp(book.ISBN,ISBN) == 0)//找到该书
				{
					strcpy(L.code,p->code);
					strcpy(L.ISBN,ISBN);
					strcpy(L.LendDate,LendDate);
					strcpy(L.LastDate,LastDate);
					strcpy(L.ReturnDate,"NULL");
					L.tag = 0;
					printf("%s\t%s\t%s\t%s\t%1d\n",L.code,L.ISBN,L.LendDate,L.LastDate,L.tag);
					SaveLendInfo(L);//保存借阅信息
					printf("-----------图书借阅，输入#号及回车结束----------\n");
					printf("请输入书籍的ISBN:\n");
					scanf("%s",ISBN);
				}
			}
			flag = 0;
		}
	}
	if(flag)
	{
		CirculationMenu();
	}else{
		printf("借阅完毕\n");
	}
}

//计算已借书本数                          未查
int LendBookNum(char code[20])
{
	LendInfo L;
	int booknum = 0;
	FILE *fp = NULL;
	
	fp = fopen("lends.txt","r");
	if(fp == NULL)
	{
		printf("文件打开错误,无法获取该读者的借阅信息\n");
		CirculationMenu();
	}else{
		while(!feof(fp))
		{
			fscanf(fp,"%s\t%s\t%s\t%s\t%1d\n",L.code,L.ISBN,L.LendDate,L.LastDate,&L.tag);
			if((strcmp(L.code,code) == 0) && L.tag == 0)
			{
				booknum ++;
			}
		}
		fclose(fp);
	}

	return booknum;
}

void SaveLendInfo(LendInfo L)
{
	FILE *fp = NULL;

	fp = fopen("lends.txt","a");
	if(fp == NULL)
	{
		printf("文件打开失败,借阅记录未保存\n");
		LendBook();
	}else{
		fprintf(fp,"%s\t%s\t%s\t%s\t%1d",L.code,L.ISBN,L.LendDate,L.LastDate,L.tag);
		fclose(fp);
		printf("借阅记录已成功保存到文件\n");
	}
}

//还书
void ReturnBook()
{
	char ISBN[50];
	char Code[20];
	char ReturnDate[20];
	int flag = 0;
	time_t t;
	LendInfoLink *head,*p,*s;
	FILE *fp = NULL;
	
	head = CreatLendInfoLink();//将借阅信息导入到链表
	t = time(NULL);
	strftime(ReturnDate,sizeof(ReturnDate),"%Y-%m-%d",localtime(&t));//生成还书时间
	
	printf("请输入证件号:\n");
	scanf("%s",Code);
	printf("-----------图书归还，输入#号及回车结束----------\n");
	printf("请输入书籍的ISBN:\n");
	scanf("%s",ISBN);
	if(strcmp(ISBN,"#") != 0)
	{
		while(strcmp(ISBN,"#") != 0)
		{
			p = head->next;
			while(p != NULL)
			{
				if(strcmp(p->code,Code) == 0)//找到该读者
				{
					if(strcmp(p->ISBN,ISBN) == 0)//找到该书
					{
						strcpy(p->ReturnDate,ReturnDate);
						p->tag = 1;
						printf("证件号\tISBN\t借书日期\t应还日期\t归还日期\t借阅状态\n");
						printf("%s\t%s\t%s\t%s\t%1d\n",p->code,p->ISBN,p->LendDate,p->LastDate,p->tag);
						flag = 1;
						break;
					}
				}
				s = p;
				p = s->next;
			}
			if(flag == 0)
			{
				printf("证件号与书籍不匹配!\n");
			}
			flag = 0;
			printf("-----------图书归还，输入#号及回车结束----------\n");
			printf("请输入书籍的ISBN:\n");
			scanf("%s",ISBN);
		}

		fp = fopen("lends.txt","w");
		if(fp == NULL)
		{
			printf("文件打开失败,无法保存归还记录\n");
			fclose(fp);
			CirculationMenu();
		}else{
			//保存还书记录
			for( p=head->next; p!=NULL; p=p->next )    
				fprintf(fp,"%s\t%s\t%s\t%s\t%d\n",p->code,p->ISBN,p->LendDate,p->LastDate,p->tag);
			fclose(fp);
			printf("借阅记录已成功保存到文件\n");
		}
	}
	printf("还书结束\n");
}


LendInfoLink* CreatLendInfoLink()
{
	FILE *fp = NULL;
	char Code[20];  //证件号
	char ISBN[50];
	char LendDate[20] ;  //借书日期
	char LastDate[20];  //应还日期
//	char ReturnDate[20];  //归还日期

	int Tag;    //状态0;借出，1：归还

	LendInfoLink* head,*p,*q;
	if((fp=fopen("lends.txt","r"))==NULL) 
	{
		printf("File open error!\n");
		CirculationMenu();
	}

	head=(LendInfoLink *)malloc(sizeof(LendInfoLink));
	q=head;	

	fscanf(fp,"%[^\t]",Code);  //先读，再判断feof(fp)，防止文件尾多读一次数据
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",ISBN);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",LendDate);
	fscanf(fp,"%*[\t]");

	fscanf(fp,"%[^\t]",LastDate);
	fscanf(fp,"%*[\t]");

//	fscanf(fp,"%[^\t]",ReturnDate);
//	fscanf(fp,"%*[\t]");

	fscanf(fp,"%d",&Tag);   //int
	fscanf(fp,"%*c"); 

	//fscanf(fp,"%[^\n]",CatalogNum);


	while(!feof(fp))   
	{

		p=(LendInfoLink *)malloc(sizeof(LendInfoLink));
		strcpy(p->code,Code);
		strcpy(p->ISBN,ISBN);

		strcpy(p->LendDate,LendDate);
		strcpy(p->LastDate,LastDate);	
	//	strcpy(p->ReturnDate,ReturnDate);
		p->tag=Tag;


		q->next=p;
		q=p;

		fscanf(fp,"%[^\t]",Code);  //先读，再判断feof(fp)，防止文件尾多读一次数据
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",ISBN);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",LendDate);
		fscanf(fp,"%*[\t]");

		fscanf(fp,"%[^\t]",LastDate);
		fscanf(fp,"%*[\t]");

	//	fscanf(fp,"%[^\t]",ReturnDate);
	//	fscanf(fp,"%*[\t]");

		fscanf(fp,"%d",&Tag);   //int
		fscanf(fp,"%*c"); 


	}
	p->next=NULL;

	fclose(fp);

	return head;

}

void FindLendInfo()
{
	char code[20];
	int flag = 1;
	LendInfoLink *head,*p,*s;

	head = CreatLendInfoLink();

	printf("请输入读者证件号\n");
	scanf("%s",code);
	p = head->next;
	printf("证件号\tISBN\t借阅日期\t应还日期\t借阅状态\n\n");
	while(p != NULL)
	{
		if(strcmp(code,p->code) == 0)
		{
			flag = 0;
			printf("%s\t%s\t%s\t%s\t%1d\n",p->code,p->ISBN,p->LendDate,p->LastDate,p->tag);
		}
		s = p->next;
		p = s;
	}
	if(flag)
	{
		printf("无借阅记录\n");
	}

}

void RenewBook()
{

}