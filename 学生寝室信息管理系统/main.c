#include "header.h"

int main()
{
	int i,l,m,n,ch;
	int studentnum[CLASS_NUM],bednum[ROOM_NUM];

	STU stu[STU_NUM];
	STU roombed[STU_NUM];
	STU classstu[STU_NUM];

	for(i=0;i<CLASS_NUM;i++)
	{
		studentnum[i]=1;
	}
	for(i=0;i<ROOM_NUM;i++)
	{
		bednum[i]=1;
	}
	printf("*-------------------------------------------------------*\n");
	printf("\n");
	printf("*               ����ѧ����Ϣ����ϵͳ 1.0                *\n");
	printf("\n");
	printf("*-------------------------------------------------------*\n");
	printf("\n");
	printf("*                   �������ܺ����                      *\n");
	printf("*                                                       *\n");
	printf("*                 �༶���������152��                   *\n");
	printf("*                                                       *\n");
	printf("*                  ѧ�ţ�8000115057                     *\n");
	printf("\n");
	printf("*-------------------------------------------------------*\n");
	printf("��Enter������ϵͳ��ʼ������...");
	getchar();
	system("cls");
	printf("*-------------------------------------------------------*\n");
	printf("\n");
	printf("*               ����ѧ����Ϣ����ϵͳ 1.0                *\n");
	printf("\n");
	printf("*-------------------------------------------------------*\n");
	printf("������ѧ��������l:(l<=%d)\n",STU_NUM);
	fflush(stdin);
	scanf("%d",&l);
	printf("������༶����m:(m<=%d)\n",CLASS_NUM);
	fflush(stdin);
	scanf("%d",&m);
	printf("��������������n:(n<=%d)\n",ROOM_NUM);
	fflush(stdin);
	scanf("%d",&n);
	printf("��Enter������˵�...");
	fflush(stdin);
	getchar();

	ch=menu();
	while(1)
	{
		switch(ch)
		{
			case 1:
				ReadInformation(stu,l);
				break;
			case 2:
				ReadfromFile(stu,&l,&m,&n);
				break;
			case 3:
				ListbyRoomBedNum(stu,roombed,bednum,l);
				break;
			case 4:
				ListbyClassStudentNum(stu,classstu,studentnum,l);
				break;
			case 5:
				SearchbyRoomNum(roombed,bednum,l);
				break;
			case 6:
				SearchbyClassNum(classstu,studentnum,l);
				break;
			case 7:
				SearchbyName(stu,l);
				break;
			case 8:
				SearchbyStudentNum(stu,l);
				break;
			case 0:
				printf("���˳�����...\n");
				exit(0);
				break;
			default:
				printf("�������!\n");
				break;
		}
		if(ch<9&&ch>0)
		{
			printf("��Enter�����ز˵�...");
			fflush(stdin);
			getchar();
		}
		ch=menu();
	}

	return 0;
}