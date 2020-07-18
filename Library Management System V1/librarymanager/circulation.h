#ifndef CIRCULATION_H
#define CIRCULATION_H

#define MAX_BOOK_SIZE 5000
#define MAX_BOOK_LEND 15
#define MAX_DAY_LEND 90

typedef struct Book
{
	char ISBN[50];
	char title[200];
	char author[200];
	char publisher[100];
	char date[20];
	float price;
	char CatalogNum[200];
}Book;
typedef struct BookList
{
	Book *Node;
	int Num;
}BookList;


typedef struct LendInfo
{
	char code[20];
	char ISBN[50];
	char LendDate[20];
	char LastDate[20];
	char ReturnDate[20];
	float fine;
	int tag;
}LendInfo;
typedef struct LendInfoLink
{
	char code[20];
	char ISBN[50];
	char LendDate[20];
	char LastDate[20];
	char ReturnDate[20];
	float fine;
	int tag;
	struct LendInfoLink *next;
}LendInfoLink;


void CirculationMenu();
void BrowseBookCatalog();

BookList CreatBookList();
void FindBook();
void FindISBN();
BookList SelectSort(BookList B);
Book SearchISBN(BookList B,char ISBN[50]);
void FindTitle();
void FindAuthor();
void FindPublisher();

void LendBook();
int LendBookNum(char code[20]);
void SaveLendInfo(LendInfo L);
void ReturnBook();
LendInfoLink *CreatLendInfoLink();

void RenewBook();
void FindLendInfo();


#endif