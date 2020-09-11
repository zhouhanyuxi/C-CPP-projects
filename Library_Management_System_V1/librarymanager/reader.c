#include"reader.h"
#include"main.h"
#include<malloc.h>

//����������Ϣ����
ReaderLink *CreatReaderLink()
{
	ReaderLink *head,*p,*s;
	int flag;
	FILE *fp = NULL;

	//����ͷ���
	head = (ReaderLink *)malloc(sizeof(ReaderLink));
	head->next = NULL;
	p = head;
	//����β���
	s = (ReaderLink *)malloc(sizeof(ReaderLink));
	p->next = s;
	s->next = NULL;
	p = s;

	fp = fopen("reader.txt","r");
	if(fp == NULL)
	{
		printf("�ļ���ʧ�ܣ��޷���ȡ������Ϣ\n");
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
		printf("���������Ϣ�ɹ�\n");
	}
	return head;
}

//���Ӷ���
void InputReader()
{
	int flag=1;
	char code[20];
	ReaderLink *head,*p,*s;
	FILE *fp = NULL;
	head = CreatReaderLink();//��������Ϣ����������

	fp = fopen("reader.txt","a");
	if(fp == NULL)
	{
		printf("�ļ���ʧ��\n");
		ReaderMenu();
	}else{
		printf("������������ߵ�֤���� ���� �Ա�M/F�� ������λ ��ʧ״̬��0/1����\n");
		printf("���������һ�����ߵĹ�ʧ״̬������ɺ�����#�ż��س�����\n");
		
		//Ѱ��β���
		p = head->next;
		while(p->next != NULL)
		{
			s = p;
			p = s->next;
		}
		//¼����Ϣ
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
				printf("��Ϣ�������\n");
			}
		}
		printf("�����Ѵ����ļ���\n");
		fclose(fp);
	}
}

//��ѯ����
ReaderLink *FindReader_code()
{
	char Code[20];
	int flag = 1;
	ReaderLink *head,*p,*s;
	head = CreatReaderLink();

	
	printf("���������֤֤����:");
	scanf("%s",Code);
	
	p = head->next;
	while(p != NULL)//��������
	{
		if(strcmp(Code,p->code) == 0)//�ҵ���Ӧ֤����
		{
			//�����ѯ��Ϣ
			printf("֤����\t����\t�Ա�(M/F)\t������λ\t֤��״̬(0/1)\n");
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
		printf("δ�ҵ���֤����\n");
		return NULL;
	}else{
		return p;
	}
}


//�޸Ķ�����Ϣ
void AlterReader()
{
	char Code[20];
	int flag = 1;
	ReaderLink *head,*p,*s;
	head = CreatReaderLink();


	printf("��������Ҫ�޸ĵĶ��ߵ�֤����:");
	scanf("%s",Code);
	
	p = head->next;
	while(p != NULL)//��������
	{
		if(strcmp(Code,p->code) == 0)//�ҵ���Ӧ֤����
		{	
			printf("֤����\t����\t�Ա�(m/F)\t������λ\n");
			printf("%s\t%s\t%s\t%s\n",p->code,p->name,p->sex,p->dept);
			printf("����������ö����µ�֤���� ���� �Ա� ������λ:\n");
			//�޸���Ϣ
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
		printf("δ�ҵ���֤����\n");
	}else{
		SaveReader(head);
	}

}

//���ȫ��������Ϣ              ǰһ�������Ϣ��������ͷҲ����->����̨����������������ƣ�
void BrowseReader()
{
	int flag = 1;
	char Code[20],Name[50],Sex[5],Dept[50];
	int Tag;
	FILE *fp = NULL;

	//���ļ�
	fp = fopen("reader.txt","r");
	if(fp == NULL)
	{
		printf("�ļ���ʧ�ܣ��޷����������Ϣ\n");
		ReaderMenu();
	}else{
		printf("--------------------------------------------------------\n");
		printf("֤����\t����\t�Ա�(m/F)\t������λ\t֤��״̬(0/1)\n");
		printf("--------------------------------------------------------\n");
		//���ļ��ж�ȡһλ���ߵ���Ϣ
		fscanf(fp,"%s %s %s %s %1d",Code,Name,Sex,Dept,&Tag);
		while(!feof(fp))
		{
			//����ȡ������Ϣ�������Ļ
			printf("%s\t%s\t%s\t%s\t%1d\n",Code,Name,Sex,Dept,Tag);
			fscanf(fp,"%s %s %s %s %1d",Code,Name,Sex,Dept,&Tag);
		}
		fclose(fp);
	}
}

//֤����ʧ
void LostReader()
{
	char Code[20];
	int flag = 1;
	ReaderLink *head,*p,*s;
	head = CreatReaderLink();


	printf("������Ҫ���й�ʧ��֤����:");
	scanf("%s",Code);

	p = head->next;
	while( p != NULL)//��������
	{
		if(strcmp(Code,p->code) == 0)//�ҵ����ʧ��֤����
		{
			p->tag = 1;//��ʧ����
			printf("��ʧ�ɹ���");
			flag = 0;
			break;
		}else{
			s = p->next;
			p = s;
		}	
	}
	if(flag)
	{
		printf("δ�ҵ������֤����\n");
	}else{
		SaveReader(head);
	}
}

//������Ϣ
void SaveReader(ReaderLink *head)
{
	ReaderLink *p,*s;
	FILE *fp = NULL;
	//���ļ�
	fp = fopen("reader.txt","w");
	if(fp == NULL)
	{
		printf("�ļ���ʧ�ܣ���Ϣδ����\n");
	}else{
		//�����Ϣ���ļ�
		p = head->next;
		while(p != NULL)
		{
			fprintf(fp,"%s\t%s\t%s\t%s\t%1d\n",p->code,p->name,p->sex,p->dept,p->tag);
			s = p->next;
			p = s;
		}
		printf("������Ϣ�ѱ��浽�ļ���\n");
		//�ر��ļ�
		fclose(fp);
	}
}


void ReaderMenu()
{
	int choice;

	printf("\n-----------���س�����������------------\n");
	fflush(stdin);
	getchar();
	system("cls");

	printf("-------------------------------------------\n");
	printf("               ���߹���ϵͳ\n");
	printf("-------------------------------------------\n");
	printf("*       1.������ж���                    *\n");
	printf("*       2.���Ӷ���                        *\n");
	printf("*       3.�޸Ķ�����Ϣ                    *\n");
	printf("*       4.��ѯ������Ϣ��ͨ��֤���ţ�      *\n");
	printf("*       5.֤����ʧ                        *\n");
	printf("*       0.�������˵�                      *\n");
	printf("-------------------------------------------\n");
	printf("��������ѡ������:");
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