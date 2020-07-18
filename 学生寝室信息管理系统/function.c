#include "header.h"

int menu(void)
{
	int ch;
	
	system("cls");
	printf("*-------------------------------------------------------------*\n");
	printf("\n");
	printf("*                  寝室学生信息管理系统 1.0                   *\n");
	printf("\n");
	printf("*-------------------------------------------------------------*\n");
	printf("\n");
	printf("*       1.从键盘录入寝室学生信息                              *\n");
	printf("*       2.从文件中录入学生寝室信息                            *\n");
	printf("*       3.将学生信息按寝室及床号顺序排序                      *\n");
	printf("*       4.将学生信息按班级及学号顺序排序                      *\n");
	printf("*       5.按寝室号搜索学生寝室信息(进行操作3后方可搜索)       *\n");
	printf("*       6.按班级搜索学生寝室信息(进行操作4后方可搜索)         *\n");
	printf("*       7.按姓名搜索学生寝室信息                              *\n");
	printf("*       8.按学号搜索学生寝室信息                              *\n");
	printf("*       0.退出                                                *\n");
	printf("*                                                             *\n");
	printf("*                                                             *\n");
	printf("*                            软件工程152班 周寒聿西 8000115057*\n");
	printf("*-------------------------------------------------------------*\n");
	printf("请输入您的选择：");
	fflush(stdin);
	scanf("%d",&ch);
	getchar();
	system("cls");

	return ch;
}

void ReadInformation(STU stu[],int l)
{
	int i;

	printf("1.从键盘录入寝室学生信息\n");
	//读取数据信息
	printf("请依次输入学生的寝室号(如203)，床号，姓名，性别，班级，学号\n");
	for(i=0;i<l;i++)
	{
		fflush(stdin);
		scanf("%3d%1d",&stu[i].roomNum,&stu[i].bedNum);
		scanf("%10s %c",stu[i].name,&stu[i].sex);
		scanf("%3d%10ld",&stu[i].classNum,&stu[i].studentNum);
	}
	printf("数据读入成功\n");
}

//将学生信息按寝室号及床号排序并选择输出
void ListbyRoomBedNum(STU stu[STU_NUM],STU roombed[STU_NUM],int bednum[ROOM_NUM],int l)
{
	FILE *fp;
	int i,j,k,h,x=0,choice1,choice2;
	
	printf("3.将学生信息按寝室及床号顺序排序\n");
	//复制一份学生信息
	for(i=0;i<l;i++)
	{
		roombed[i]=stu[i];
	}                                                     
	//对寝室号进行排序                                   
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
	//记下每个寝室的有效床位数
	for(i=0,j=0;i<l-1;i++)
	{
		if(roombed[i].roomNum==roombed[i+1].roomNum)
		{
			bednum[j]++;
		}else{
			j++;
		}
	}
	//以床号为标准对寝室内部进行排序
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
	choice1=PrintChoice();//选择是否输出
	if(choice1)
	{
		//选择是否输出到文件
		choice2=WritetoFileChoice();
		//输出信息
		if(choice2)
		{
			fp=fopen("List by room and bed number.txt","w");
			WritetoFile(roombed,l,fp);//输出到文件
		}else{
			PrintInformation(roombed,l);//输出到屏幕
		}
	}else{
		printf("排序完成\n");
	}
}

//将学生信息按班级及学号排序并选择输出
void ListbyClassStudentNum(STU stu[STU_NUM],STU classstu[STU_NUM],int studentnum[CLASS_NUM],int l)
{
	FILE *fp;
	int i,j,k,h,x=0,choice1,choice2;
	
	printf("4.将学生信息按班级及学号顺序排序\n");
	//复制一份学生信息
	for(i=0;i<l;i++)
	{
		classstu[i]=stu[i];
	}
	//对班级进行排序
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
	//记下每个班级的学生人数
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
	//以学号为标准对每个班中的学生进行排序
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
	choice1=PrintChoice();//选择是否输出
	if(choice1)
	{
		//选择是否输出到文件
		choice2=WritetoFileChoice();
		//输出信息
		if(choice2)
		{
			fp=fopen("List by class and student number.txt","w");
			WritetoFile(classstu,l,fp);
		}else{
			PrintInformation(classstu,l);
		}
	}else{
		printf("排序完成\n");
	}
}

//通过寝室号查找学生信息
void SearchbyRoomNum(STU roombed[STU_NUM],int bednum[ROOM_NUM],int l)
{
	int roomnum,i=0,j,x=0,flag=1;

	printf("5.按寝室号搜索学生寝室信息\n");
	//输入要查找的寝室号
	printf("请输入要查找的寝室号:\n");
	fflush(stdin);
	scanf("%d",&roomnum);
	//查找寝室号
	while((roombed[i].roomNum!=roomnum)&&(flag==1))
	{
		i=i+bednum[x];
		if(i>=l)
		{
			printf("未找到该寝室号，返回菜单\n");
			flag=0;
		}
		x++;
	}
	//输出信息
	if(flag)
	{
		printf("寝室号\t床号\t姓名\t性别\t班级\t学号\n");
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

	printf("6.按班级搜索学生寝室信息\n");
	//输入要查找的班级序号
	printf("请输入要查找的班级序号:\n");
	fflush(stdin);
	scanf("%d",&classnum);
	//查找
	while((classstu[i].classNum!=classnum)&&(flag==1))
	{
		i=i+studentnum[x];
		if(i>=l)
		{
			printf("未找到该班级");
			flag=0;
		}
		x++;
	}
	if(flag)
	{
		k=i;
		printf("寝室号\t床号\t姓名\t性别\t班级\t学号\n");
		for(j=0;j<studentnum[x];j++,i++)
		{
			printf("%3d\t%1d",classstu[i].roomNum,classstu[i].bedNum);
			printf("%10s\t%c\t",classstu[i].name,classstu[i].sex);
			printf("%3d\t%10ld\n",classstu[i].classNum,classstu[i].studentNum);
		}
	}
}
//通过姓名查找学生信息
void SearchbyName(STU stu[STU_NUM],int l)
{
	int i=0,flag=1;
	char name[10];

	printf("7.按姓名搜索学生寝室信息\n");
	//输入要查找的学生姓名
	printf("请输入要查找的学生姓名:\n");
	fflush(stdin);
	scanf("%s",name);
	//查找该姓名
	while((strcmp(name,stu[i].name)!=0)&&(flag==1))
	{
		i++;
		if(i>=l)
		{
			printf("未找到该姓名\n");
			flag=0;
		}
	}
	//输出该学生信息
	if(flag)
	{
		printf("寝室号\t床号\t姓名\t性别\t班级\t学号\n");
		printf("%3d\t%1d",stu[i].roomNum,stu[i].bedNum);
		printf("%10s\t%c\t",stu[i].name,stu[i].sex);
		printf("%3d\t%10ld\n",stu[i].classNum,stu[i].studentNum);
	}
}

void SearchbyStudentNum(STU stu[STU_NUM],int l)
{
	int i=0,flag=1;
	long stunum;

	printf("8.按学号搜索学生寝室信息\n");
	printf("请输入要查找的学生学号:\n");
	fflush(stdin);
	scanf("%ld",&stunum);
	while((stu[i].studentNum!=stunum)&&(flag==1))
	{
		i++;
		if(i>=l)
		{
			printf("未找到该学号\n");
			flag=0;
		}
	}
	if(flag)
	{
		printf("寝室号\t床号\t姓名\t性别\t班级\t学号\n");
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
		printf("文件打开失败!返回菜单\n");
		exit(0);
	}
	for(i=0;i<*l;i++)
	{
		fscanf(fp,"%3d%1d",&stu[i].roomNum,&stu[i].bedNum);
		fscanf(fp,"%10s %c",stu[i].name,&stu[i].sex);
		fscanf(fp,"%3d%10ld",&stu[i].classNum,&stu[i].studentNum);
	}
	fclose(fp);
	printf("文件读取成功!\n");
}

void WritetoFile(STU write[STU_NUM],int num,FILE *fp)
{
	int i;

	if(fp==NULL)
	{
		printf("文件打开失败!自动转为输出到屏幕\n");
		PrintInformation(write,num);
	}else{
		fprintf(fp,"寝室号\t床号\t姓名\t性别\t班级\t学号\n");
		for(i=0;i<num;i++)
		{
			fprintf(fp,"%3d\t%1d",write[i].roomNum,write[i].bedNum);
			fprintf(fp,"%10s\t%c\t",write[i].name,write[i].sex);
			fprintf(fp,"%3d\t%10ld\n",write[i].classNum,write[i].studentNum);
		}
	}
	fclose(fp);
	printf("信息已输出到文件...\n");
}

void PrintInformation(STU print[STU_NUM],int num)
{
	int i;

	printf("寝室号\t床号\t姓名\t性别\t班级\t学号\n");
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

	printf("是否输出排序后的信息?\n");
	while(choice==-1)
	{
		printf("是请输入y或Y,否请输入n或N\n");
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
				printf("输入错误!\n");
				break;
		}
	}

	return choice;
}
//选择是否将信息输出到文件中
int WritetoFileChoice()
{
	int choice=-1;
	char ch;
	 
	printf("是否将信息输出到文件中？\n");
	while(choice==-1)
	{
		printf("是请输入y或Y,否请输入n或N\n");
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
				printf("输入错误!\n");
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
