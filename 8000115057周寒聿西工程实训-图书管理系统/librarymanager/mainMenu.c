#include"main.h"
#include"reader.h"
#include"circulation.h"

void MainMenu()
{
	int choice;

	system("cls");
	printf("*******************************************\n");
	printf("*                                         *\n");
	printf("*             ͼ��ݹ���ϵͳ              *\n");
	printf("*                                         *\n");
	printf("*-----------------------------------------*\n");
	printf("*             1.���߹���                  *\n");
	printf("*             2.ͼ��������(��δ����)    *\n");
	printf("*             3.ͼ���Ŀ����(��δ����)    *\n");
	printf("*             4.ͼ����ͨ����              *\n");
	printf("*             0.�˳�ϵͳ                  *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	printf("����������ѡ��(0-4):");
	scanf("%1d",&choice);
	switch(choice)
	{
		case 1:
			ReaderMenu();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			CirculationMenu();
			break;
		case 0:
			break;
	}
}

int main()
{
	MainMenu();

	return 0;
}