#include"main.h"
#include"reader.h"
#include"circulation.h"

void MainMenu()
{
	int choice;

	system("cls");
	printf("*******************************************\n");
	printf("*                                         *\n");
	printf("*             图书馆管理系统              *\n");
	printf("*                                         *\n");
	printf("*-----------------------------------------*\n");
	printf("*             1.读者管理                  *\n");
	printf("*             2.图书分类管理(暂未开放)    *\n");
	printf("*             3.图书编目管理(暂未开放)    *\n");
	printf("*             4.图书流通管理              *\n");
	printf("*             0.退出系统                  *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	printf("请输入您的选择(0-4):");
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