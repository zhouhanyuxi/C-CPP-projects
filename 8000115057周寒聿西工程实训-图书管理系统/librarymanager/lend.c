
#include"main.h"
#include"reader.h"
#include"circulation.h"
#include<time.h>
#include<malloc.h>

//����
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
	strftime(LendDate,sizeof(LendDate),"%Y-%m-%d",localtime(&t));//��ȡ����ʱ��
	t = t + MAX_DAY_LEND*24*60*60;
	strftime(LastDate,sizeof(LastDate),"%Y-%m-%d",localtime(&t));//��ȡӦ��ʱ��

	p = FindReader_code();//�ҵ��ö���

	if(p == NULL)
	{
		flag = 1;
	}else{
		booknum = LendBookNum(p->code);
		if(p->tag == 1)
		{
			printf("��֤���ѹ�ʧ���޷�����\n");
			flag = 1;
		}else if(booknum > MAX_BOOK_LEND)
		{
			printf("�Ѿ�����%d�����޷��ٽ���\n",MAX_BOOK_LEND);
			flag = 1;
		}else{
			printf("-----------ͼ����ģ�����#�ż��س�����----------\n");
			printf("�������鼮��ISBN:\n");
			scanf("%s",ISBN);
			while((strcmp(ISBN,"#") != 0) && (booknum < MAX_BOOK_LEND))
			{
				B = CreatBookList();
				B = SelectSort(B);
				book = SearchISBN(B,ISBN);
				if(strcmp(book.ISBN,ISBN) == 0)//�ҵ�����
				{
					strcpy(L.code,p->code);
					strcpy(L.ISBN,ISBN);
					strcpy(L.LendDate,LendDate);
					strcpy(L.LastDate,LastDate);
					strcpy(L.ReturnDate,"NULL");
					L.tag = 0;
					printf("%s\t%s\t%s\t%s\t%1d\n",L.code,L.ISBN,L.LendDate,L.LastDate,L.tag);
					SaveLendInfo(L);//���������Ϣ
					printf("-----------ͼ����ģ�����#�ż��س�����----------\n");
					printf("�������鼮��ISBN:\n");
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
		printf("�������\n");
	}
}

//�����ѽ��鱾��                          δ��
int LendBookNum(char code[20])
{
	LendInfo L;
	int booknum = 0;
	FILE *fp = NULL;
	
	fp = fopen("lends.txt","r");
	if(fp == NULL)
	{
		printf("�ļ��򿪴���,�޷���ȡ�ö��ߵĽ�����Ϣ\n");
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
		printf("�ļ���ʧ��,���ļ�¼δ����\n");
		LendBook();
	}else{
		fprintf(fp,"%s\t%s\t%s\t%s\t%1d",L.code,L.ISBN,L.LendDate,L.LastDate,L.tag);
		fclose(fp);
		printf("���ļ�¼�ѳɹ����浽�ļ�\n");
	}
}

//����
void ReturnBook()
{
	char ISBN[50];
	char Code[20];
	char ReturnDate[20];
	int flag = 0;
	time_t t;
	LendInfoLink *head,*p,*s;
	FILE *fp = NULL;
	
	head = CreatLendInfoLink();//��������Ϣ���뵽����
	t = time(NULL);
	strftime(ReturnDate,sizeof(ReturnDate),"%Y-%m-%d",localtime(&t));//���ɻ���ʱ��
	
	printf("������֤����:\n");
	scanf("%s",Code);
	printf("-----------ͼ��黹������#�ż��س�����----------\n");
	printf("�������鼮��ISBN:\n");
	scanf("%s",ISBN);
	if(strcmp(ISBN,"#") != 0)
	{
		while(strcmp(ISBN,"#") != 0)
		{
			p = head->next;
			while(p != NULL)
			{
				if(strcmp(p->code,Code) == 0)//�ҵ��ö���
				{
					if(strcmp(p->ISBN,ISBN) == 0)//�ҵ�����
					{
						strcpy(p->ReturnDate,ReturnDate);
						p->tag = 1;
						printf("֤����\tISBN\t��������\tӦ������\t�黹����\t����״̬\n");
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
				printf("֤�������鼮��ƥ��!\n");
			}
			flag = 0;
			printf("-----------ͼ��黹������#�ż��س�����----------\n");
			printf("�������鼮��ISBN:\n");
			scanf("%s",ISBN);
		}

		fp = fopen("lends.txt","w");
		if(fp == NULL)
		{
			printf("�ļ���ʧ��,�޷�����黹��¼\n");
			fclose(fp);
			CirculationMenu();
		}else{
			//���滹���¼
			for( p=head->next; p!=NULL; p=p->next )    
				fprintf(fp,"%s\t%s\t%s\t%s\t%d\n",p->code,p->ISBN,p->LendDate,p->LastDate,p->tag);
			fclose(fp);
			printf("���ļ�¼�ѳɹ����浽�ļ�\n");
		}
	}
	printf("�������\n");
}


LendInfoLink* CreatLendInfoLink()
{
	FILE *fp = NULL;
	char Code[20];  //֤����
	char ISBN[50];
	char LendDate[20] ;  //��������
	char LastDate[20];  //Ӧ������
//	char ReturnDate[20];  //�黹����

	int Tag;    //״̬0;�����1���黹

	LendInfoLink* head,*p,*q;
	if((fp=fopen("lends.txt","r"))==NULL) 
	{
		printf("File open error!\n");
		CirculationMenu();
	}

	head=(LendInfoLink *)malloc(sizeof(LendInfoLink));
	q=head;	

	fscanf(fp,"%[^\t]",Code);  //�ȶ������ж�feof(fp)����ֹ�ļ�β���һ������
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

		fscanf(fp,"%[^\t]",Code);  //�ȶ������ж�feof(fp)����ֹ�ļ�β���һ������
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

	printf("���������֤����\n");
	scanf("%s",code);
	p = head->next;
	printf("֤����\tISBN\t��������\tӦ������\t����״̬\n\n");
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
		printf("�޽��ļ�¼\n");
	}

}

void RenewBook()
{

}