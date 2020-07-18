#include"reader.h"
#include"main.h"
#include<malloc.h>

//建立读者信息链表
ReaderLink *CreatReaderLink()
{
	ReaderLink *head,*p,*s;
	int flag;
	FILE *fp = NULL;

	//建立头结点
	head = (ReaderLink *)malloc(sizeof(ReaderLink));
	head->next = NULL;
	p = head;
	//建立尾结点
	s = (ReaderLink *)malloc(sizeof(ReaderLink));
	p->next = s;
	s->next = NULL;
	p = s;

	fp = fopen("reader.txt","r");
	if(fp == NULL)
	{
		printf("文件打开失败，无法获取读者信息\n");
		ReaderMenu();
	}else{
		p = head;
		while(!feof(fp))
		{
			s = (ReaderLink *)malloc(sizeof(ReaderLink));
			p->next = s;
			p = s;
			p->next = NULL;
			fscanf(fp,"%s\t%s\t%s\t%s\t%1d\n",p->code,p->name,p->sex,p->dept,&p->tag);
		}
		flag = 0;
		fclose(fp);
		printf("导入读者信息成功\n");
	}
	return head;
}

//增加读者
void InputReader()
{
	int flag=1;
	char code[20];
	ReaderLink *head,*p,*s;
	FILE *fp = NULL;
	head = CreatReaderLink();//将读者信息导入链表中

	fp = fopen("reader.txt","a");
	if(fp == NULL)
	{
		printf("文件打开失败\n");
		ReaderMenu();
	}else{
		printf("请依次输入读者的证件号 姓名 性别（M/F） 工作单位 挂失状态（0/1）：\n");
		printf("（请在最后一名读者的挂失状态输入完成后换行输#号及回车键）\n");
		
		//寻找尾结点
		p = head->next;
		while(p->next != NULL)
		{
			s = p;
			p = s->next;
		}
		//录入信息
		while(flag)
		{
			scanf("%s",code);
			if(strcmp(code,"#") != 0)
			{
				s = (ReaderLink *)malloc(sizeof(ReaderLink));
				p->next = s;
				p = s;
				p->next = NULL;
				strcpy(p->code,code);
				scanf("%s %s %s %1d",p->name,p->sex,p->dept,&p->tag);
				fprintf(fp,"%s\t%s\t%s\t%s\t%1d\n",p->code,p->name,p->sex,p->dept,p->tag);	
			}else{
				flag = 0;
				printf("信息输入结束\n");
			}
		}
		printf("数据已存入文件中\n");
		fclose(fp);
	}
}

//查询读者
ReaderLink *FindReader_code()
{
	char Code[20];
	int flag = 1;
	ReaderLink *head,*p,*s;
	head = CreatReaderLink();

	
	printf("请输入读者证证件号:");
	scanf("%s",Code);
	
	p = head->next;
	while(p != NULL)//遍历链表
	{
		if(strcmp(Code,p->code) == 0)//找到相应证件号
		{
			//输出查询信息
			printf("证件号\t姓名\t性别(M/F)\t工作单位\t证件状态(0/1)\n");
			printf("%s\t%s\t%s\t%s\t%1d\n",p->code,p->name,p->sex,p->dept,p->tag);
			flag = 0;
			break;
		}else{
			s = p;
			p = s->next;
		}
	}
	if(flag)
	{
		printf("未找到该证件号\n");
		return NULL;
	}else{
		return p;
	}
}


//修改读者信息
void AlterReader()
{
	char Code[20];
	int flag = 1;
	ReaderLink *head,*p,*s;
	head = CreatReaderLink();


	printf("请输入需要修改的读者的证件号:");
	scanf("%s",Code);
	
	p = head->next;
	while(p != NULL)//遍历链表
	{
		if(strcmp(Code,p->code) == 0)//找到相应证件号
		{	
			printf("证件号\t姓名\t性别(m/F)\t工作单位\n");
			printf("%s\t%s\t%s\t%s\n",p->code,p->name,p->sex,p->dept);
			printf("请依次输入该读者新的证件号 姓名 性别 工作单位:\n");
			//修改信息
			scanf("%s %s %s %s",p->code,p->name,p->sex,p->dept);
			flag = 0;
			break;
		}else{
			s = p;
			p = s->next;
		}
	
	}
	if(flag)
	{
		printf("未找到该证件号\n");
	}else{
		SaveReader(head);
	}

}

//浏览全部读者信息              前一半读者信息不见，表头也不见->控制台程序输出有字数限制？
void BrowseReader()
{
	int flag = 1;
	char Code[20],Name[50],Sex[5],Dept[50];
	int Tag;
	FILE *fp = NULL;

	//打开文件
	fp = fopen("reader.txt","r");
	if(fp == NULL)
	{
		printf("文件打开失败，无法浏览读者信息\n");
		ReaderMenu();
	}else{
		printf("--------------------------------------------------------\n");
		printf("证件号\t姓名\t性别(m/F)\t工作单位\t证件状态(0/1)\n");
		printf("--------------------------------------------------------\n");
		//从文件中读取一位读者的信息
		fscanf(fp,"%s %s %s %s %1d",Code,Name,Sex,Dept,&Tag);
		while(!feof(fp))
		{
			//将读取到得信息输出到屏幕
			printf("%s\t%s\t%s\t%s\t%1d\n",Code,Name,Sex,Dept,Tag);
			fscanf(fp,"%s %s %s %s %1d",Code,Name,Sex,Dept,&Tag);
		}
		fclose(fp);
	}
}

//证件挂失
void LostReader()
{
	char Code[20];
	int flag = 1;
	ReaderLink *head,*p,*s;
	head = CreatReaderLink();


	printf("请输入要进行挂失的证件号:");
	scanf("%s",Code);

	p = head->next;
	while( p != NULL)//遍历链表
	{
		if(strcmp(Code,p->code) == 0)//找到需挂失的证件号
		{
			p->tag = 1;//挂失操作
			printf("挂失成功！");
			flag = 0;
			break;
		}else{
			s = p->next;
			p = s;
		}	
	}
	if(flag)
	{
		printf("未找到输入的证件号\n");
	}else{
		SaveReader(head);
	}
}

//保存信息
void SaveReader(ReaderLink *head)
{
	ReaderLink *p,*s;
	FILE *fp = NULL;
	//打开文件
	fp = fopen("reader.txt","w");
	if(fp == NULL)
	{
		printf("文件打开失败，信息未保存\n");
	}else{
		//输出信息到文件
		p = head->next;
		while(p != NULL)
		{
			fprintf(fp,"%s\t%s\t%s\t%s\t%1d\n",p->code,p->name,p->sex,p->dept,p->tag);
			s = p->next;
			p = s;
		}
		printf("读者信息已保存到文件中\n");
		//关闭文件
		fclose(fp);
	}
}


void ReaderMenu()
{
	int choice;

	printf("\n-----------按回车键继续操作------------\n");
	fflush(stdin);
	getchar();
	system("cls");

	printf("-------------------------------------------\n");
	printf("               读者管理系统\n");
	printf("-------------------------------------------\n");
	printf("*       1.浏览所有读者                    *\n");
	printf("*       2.增加读者                        *\n");
	printf("*       3.修改读者信息                    *\n");
	printf("*       4.查询读者信息（通过证件号）      *\n");
	printf("*       5.证件挂失                        *\n");
	printf("*       0.返回主菜单                      *\n");
	printf("-------------------------------------------\n");
	printf("请输入您选择的序号:");
	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
			BrowseReader();
			ReaderMenu();
			break;
		case 2:
			InputReader();
			ReaderMenu();
			break;
		case 3:
			AlterReader();
			ReaderMenu();
			break;
		case 4:
			FindReader_code();
			ReaderMenu();
			break;
		case 5:
			LostReader();
			ReaderMenu();
			break;
		case 0:
			MainMenu();
			break;
	}
}