#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STU_NUM 200
#define ROOM_NUM 25
#define BED_NUM 8
#define CLASS_NUM 4
#define CLASS_STU_NUM 50

typedef struct STUDENT
{
	int roomNum;
	int bedNum;
	char name[10];
	char sex;
	int classNum;
	long studentNum;
}STU;

int menu(void);
void ReadInformation(STU stu[],int l);
void ListbyRoomBedNum(STU stu[STU_NUM],STU roombed[STU_NUM],int bednum[ROOM_NUM],int l);
void ListbyClassStudentNum(STU stu[STU_NUM],STU classstu[CLASS_STU_NUM],int studentnum[CLASS_NUM],int l);
void SearchbyRoomNum(STU roombed[STU_NUM],int bednum[ROOM_NUM],int l);
void SearchbyClassNum(STU classstu[STU_NUM],int studentnum[CLASS_NUM],int l);
void SearchbyName(STU stu[STU_NUM],int l);
void SearchbyStudentNum(STU stu[STU_NUM],int l);
void ReadfromFile(STU stu[STU_NUM],int *l,int *m,int *n);
void WritetoFile(STU stu[STU_NUM],int l,FILE *fp);
int PrintChoice();
int WritetoFileChoice();
void SwapStruct(STU *a,STU *b);
void PrintInformation(STU print[STU_NUM],int num);

//Í·ÎÄ¼þ