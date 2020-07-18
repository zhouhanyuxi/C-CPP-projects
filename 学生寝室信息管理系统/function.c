#include "header.h"

int menu(void)
{
	int ch;
	
	system("cls");
	printf("*-------------------------------------------------------------*\n");
	printf("\n");
	printf("*                  ����ѧ����Ϣ����ϵͳ 1.0                   *\n");
	printf("\n");
	printf("*-------------------------------------------------------------*\n");
	printf("\n");
	printf("*       1.�Ӽ���¼������ѧ����Ϣ                              *\n");
	printf("*       2.���ļ���¼��ѧ��������Ϣ                            *\n");
	printf("*       3.��ѧ����Ϣ�����Ҽ�����˳������                      *\n");
	printf("*       4.��ѧ����Ϣ���༶��ѧ��˳������                      *\n");
	printf("*       5.�����Һ�����ѧ��������Ϣ(���в���3�󷽿�����)       *\n");
	printf("*       6.���༶����ѧ��������Ϣ(���в���4�󷽿�����)         *\n");
	printf("*       7.����������ѧ��������Ϣ                              *\n");
	printf("*       8.��ѧ������ѧ��������Ϣ                              *\n");
	printf("*       0.�˳�                                                *\n");
	printf("*                                                             *\n");
	printf("*                                                             *\n");
	printf("*                            �������152�� �ܺ���� 8000115057*\n");
	printf("*-------------------------------------------------------------*\n");
	printf("����������ѡ��");
	fflush(stdin);
	scanf("%d",&ch);
	getchar();
	system("cls");

	return ch;
}

void ReadInformation(STU stu[],int l)
{
	int i;

	printf("1.�Ӽ���¼������ѧ����Ϣ\n");
	//��ȡ������Ϣ
	printf("����������ѧ�������Һ�(��203)�����ţ��������Ա𣬰༶��ѧ��\n");
	for(i=0;i<l;i++)
	{
		fflush(stdin);
		scanf("%3d%1d",&stu[i].roomNum,&stu[i].bedNum);
		scanf("%10s %c",stu[i].name,&stu[i].sex);
		scanf("%3d%10ld",&stu[i].classNum,&stu[i].studentNum);
	}
	printf("���ݶ���ɹ�\n");
}

//��ѧ����Ϣ�����Һż���������ѡ�����
void ListbyRoomBedNum(STU stu[STU_NUM],STU roombed[STU_NUM],int bednum[ROOM_NUM],int l)
{
	FILE *fp;
	int i,j,k,h,x=0,choice1,choice2;
	
	printf("3.��ѧ����Ϣ�����Ҽ�����˳������\n");
	//����һ��ѧ����Ϣ
	for(i=0;i<l;i++)
	{
		roombed[i]=stu[i];
	}                                                     
	//�����ҺŽ�������                                   
	for(i=0;i<l-1;i++)
	{
		k=i;
		for(j=i+1;j<l;j++)
		{
			if(roombed[j].roomNum<roombed[k].roomNum)
			{
				k=j;
			}
		}
		if(k!=i)
		{
			SwapStruct(&roombed[k],&roombed[i]);
		}
	}
	//����ÿ�����ҵ���Ч��λ��
	for(i=0,j=0;i<l-1;i++)
	{
		if(roombed[i].roomNum==roombed[i+1].roomNum)
		{
			bednum[j]++;
		}else{
			j++;
		}
	}
	//�Դ���Ϊ��׼�������ڲ���������
	for(i=0;i<l;i=i+bednum[x-1])
	{
		for(j=i;j<i+bednum[x]-1;j++)
		{
			k=j;
			for(h=j+1;h<i+bednum[x];h++)
			{
				if(roombed[h].bedNum<roombed[k].bedNum)
				{
					k=h;
				}
			}
			if(k!=j)
			{
				SwapStruct(&roombed[k],&roombed[j]);
			}
		}
		x++;
	}
	choice1=PrintChoice();//ѡ���Ƿ����
	if(choice1)
	{
		//ѡ���Ƿ�������ļ�
		choice2=WritetoFileChoice();
		//�����Ϣ
		if(choice2)
		{
			fp=fopen("List by room and bed number.txt","w");
			WritetoFile(roombed,l,fp);//������ļ�
		}else{
			PrintInformation(roombed,l);//�������Ļ
		}
	}else{
		printf("�������\n");
	}
}

//��ѧ����Ϣ���༶��ѧ������ѡ�����
void ListbyClassStudentNum(STU stu[STU_NUM],STU classstu[STU_NUM],int studentnum[CLASS_NUM],int l)
{
	FILE *fp;
	int i,j,k,h,x=0,choice1,choice2;
	
	printf("4.��ѧ����Ϣ���༶��ѧ��˳������\n");
	//����һ��ѧ����Ϣ
	for(i=0;i<l;i++)
	{
		classstu[i]=stu[i];
	}
	//�԰༶��������
	for(i=0;i<l-1;i++)
	{
		k=i;
		for(j=i+1;j<l;j++)
		{
			if(classstu[j].classNum<classstu[k].classNum)
			{
				k=j;
			}
		}
		if(k!=i)
		{
			SwapStruct(&classstu[k],&classstu[i]);
		}
	}
	//����ÿ���༶��ѧ������
	for(i=0,j=0;i<l-1;i++)
	{
		if(classstu[i].classNum==classstu[i+1].classNum)
		{
			studentnum[j]++;
		}
		if(classstu[i].classNum!=classstu[i+1].classNum)
		{
			j++;
		}
	}
	//��ѧ��Ϊ��׼��ÿ�����е�ѧ����������
	for(i=0;i<l;i=i+studentnum[x-1])
	{
		for(j=i;j<i+studentnum[x]-1;j++)
		{
			k=j;
			for(h=j+1;h<i+studentnum[x];h++)
			{
				if(classstu[h].studentNum<classstu[k].studentNum)
				{
					k=h;
				}
			}
			if(k!=j)
			{
				SwapStruct(&classstu[k],&classstu[j]);
			}
		}
		x++;
	}
	choice1=PrintChoice();//ѡ���Ƿ����
	if(choice1)
	{
		//ѡ���Ƿ�������ļ�
		choice2=WritetoFileChoice();
		//�����Ϣ
		if(choice2)
		{
			fp=fopen("List by class and student number.txt","w");
			WritetoFile(classstu,l,fp);
		}else{
			PrintInformation(classstu,l);
		}
	}else{
		printf("�������\n");
	}
}

//ͨ�����ҺŲ���ѧ����Ϣ
void SearchbyRoomNum(STU roombed[STU_NUM],int bednum[ROOM_NUM],int l)
{
	int roomnum,i=0,j,x=0,flag=1;

	printf("5.�����Һ�����ѧ��������Ϣ\n");
	//����Ҫ���ҵ����Һ�
	printf("������Ҫ���ҵ����Һ�:\n");
	fflush(stdin);
	scanf("%d",&roomnum);
	//�������Һ�
	while((roombed[i].roomNum!=roomnum)&&(flag==1))
	{
		i=i+bednum[x];
		if(i>=l)
		{
			printf("δ�ҵ������Һţ����ز˵�\n");
			flag=0;
		}
		x++;
	}
	//�����Ϣ
	if(flag)
	{
		printf("���Һ�\t����\t����\t�Ա�\t�༶\tѧ��\n");
		for(j=0;j<bednum[x];j++,i++)
		{
			printf("%3d\t%1d",roombed[i].roomNum,roombed[i].bedNum);
			printf("%10s\t%c\t",roombed[i].name,roombed[i].sex);
			printf("%3d\t%10ld\n",roombed[i].classNum,roombed[i].studentNum);
		}
	}
}

void SearchbyClassNum(STU classstu[STU_NUM],int studentnum[CLASS_NUM],int l)
{
	int classnum,i=0,j,k,x=0,flag=1;

	printf("6.���༶����ѧ��������Ϣ\n");
	//����Ҫ���ҵİ༶���
	printf("������Ҫ���ҵİ༶���:\n");
	fflush(stdin);
	scanf("%d",&classnum);
	//����
	while((classstu[i].classNum!=classnum)&&(flag==1))
	{
		i=i+studentnum[x];
		if(i>=l)
		{
			printf("δ�ҵ��ð༶");
			flag=0;
		}
		x++;
	}
	if(flag)
	{
		k=i;
		printf("���Һ�\t����\t����\t�Ա�\t�༶\tѧ��\n");
		for(j=0;j<studentnum[x];j++,i++)
		{
			printf("%3d\t%1d",classstu[i].roomNum,classstu[i].bedNum);
			printf("%10s\t%c\t",classstu[i].name,classstu[i].sex);
			printf("%3d\t%10ld\n",classstu[i].classNum,classstu[i].studentNum);
		}
	}
}
//ͨ����������ѧ����Ϣ
void SearchbyName(STU stu[STU_NUM],int l)
{
	int i=0,flag=1;
	char name[10];

	printf("7.����������ѧ��������Ϣ\n");
	//����Ҫ���ҵ�ѧ������
	printf("������Ҫ���ҵ�ѧ������:\n");
	fflush(stdin);
	scanf("%s",name);
	//���Ҹ�����
	while((strcmp(name,stu[i].name)!=0)&&(flag==1))
	{
		i++;
		if(i>=l)
		{
			printf("δ�ҵ�������\n");
			flag=0;
		}
	}
	//�����ѧ����Ϣ
	if(flag)
	{
		printf("���Һ�\t����\t����\t�Ա�\t�༶\tѧ��\n");
		printf("%3d\t%1d",stu[i].roomNum,stu[i].bedNum);
		printf("%10s\t%c\t",stu[i].name,stu[i].sex);
		printf("%3d\t%10ld\n",stu[i].classNum,stu[i].studentNum);
	}
}

void SearchbyStudentNum(STU stu[STU_NUM],int l)
{
	int i=0,flag=1;
	long stunum;

	printf("8.��ѧ������ѧ��������Ϣ\n");
	printf("������Ҫ���ҵ�ѧ��ѧ��:\n");
	fflush(stdin);
	scanf("%ld",&stunum);
	while((stu[i].studentNum!=stunum)&&(flag==1))
	{
		i++;
		if(i>=l)
		{
			printf("δ�ҵ���ѧ��\n");
			flag=0;
		}
	}
	if(flag)
	{
		printf("���Һ�\t����\t����\t�Ա�\t�༶\tѧ��\n");
		printf("%3d\t%1d",stu[i].roomNum,stu[i].bedNum);
		printf("%10s\t%c\t",stu[i].name,stu[i].sex);
		printf("%3d\t%10ld\n",stu[i].classNum,stu[i].studentNum);
	}
}

void ReadfromFile(STU stu[],int *l,int *m,int *n)
{
	FILE *fp;
	int i;

	if((fp=fopen("Read from file.txt","r"))==NULL)
	{
		printf("�ļ���ʧ��!���ز˵�\n");
		exit(0);
	}
	for(i=0;i<*l;i++)
	{
		fscanf(fp,"%3d%1d",&stu[i].roomNum,&stu[i].bedNum);
		fscanf(fp,"%10s %c",stu[i].name,&stu[i].sex);
		fscanf(fp,"%3d%10ld",&stu[i].classNum,&stu[i].studentNum);
	}
	fclose(fp);
	printf("�ļ���ȡ�ɹ�!\n");
}

void WritetoFile(STU write[STU_NUM],int num,FILE *fp)
{
	int i;

	if(fp==NULL)
	{
		printf("�ļ���ʧ��!�Զ�תΪ�������Ļ\n");
		PrintInformation(write,num);
	}else{
		fprintf(fp,"���Һ�\t����\t����\t�Ա�\t�༶\tѧ��\n");
		for(i=0;i<num;i++)
		{
			fprintf(fp,"%3d\t%1d",write[i].roomNum,write[i].bedNum);
			fprintf(fp,"%10s\t%c\t",write[i].name,write[i].sex);
			fprintf(fp,"%3d\t%10ld\n",write[i].classNum,write[i].studentNum);
		}
	}
	fclose(fp);
	printf("��Ϣ��������ļ�...\n");
}

void PrintInformation(STU print[STU_NUM],int num)
{
	int i;

	printf("���Һ�\t����\t����\t�Ա�\t�༶\tѧ��\n");
	for(i=0;i<num;i++)
	{
		printf("%3d\t%1d",print[i].roomNum,print[i].bedNum);
		printf("%10s\t%c\t",print[i].name,print[i].sex);
		printf("%3d\t%10ld\n",print[i].classNum,print[i].studentNum);
	}
}

int PrintChoice()
{
	int choice=-1;
	char ch;

	printf("�Ƿ������������Ϣ?\n");
	while(choice==-1)
	{
		printf("��������y��Y,��������n��N\n");
		fflush(stdin);
		ch=getchar();
		switch(ch)
		{
			case 'y':
			case 'Y':
				choice=1;
				break;
			case 'n':
			case 'N':
				choice=0;
				break;
			default:
				printf("�������!\n");
				break;
		}
	}

	return choice;
}
//ѡ���Ƿ���Ϣ������ļ���
int WritetoFileChoice()
{
	int choice=-1;
	char ch;
	 
	printf("�Ƿ���Ϣ������ļ��У�\n");
	while(choice==-1)
	{
		printf("��������y��Y,��������n��N\n");
		fflush(stdin);
		ch=getchar();
		switch(ch)
		{
			case 'y':
			case 'Y':
				choice=1;
				break;
			case 'n':
			case 'N':
				choice=0;
				break;
			default:
				printf("�������!\n");
				break;
		}
	}

	return choice;
}

void SwapStruct(STU *a,STU *b)
{
	STU c;

	c=*a;
	*a=*b;
	*b=c;
}
