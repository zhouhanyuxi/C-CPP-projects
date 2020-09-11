#ifndef READER_H
#define READER_H

typedef struct ReaderLink
{
	char code[20];
	char name[30];
	char sex[5];
	char dept[50];
	short tag;
	struct ReaderLink *next;
}ReaderLink;

ReaderLink *CreatReaderLink();
void SaveReader(ReaderLink *head);
int GetReader(ReaderLink *head);
void ReaderMenu();
void InputReader();
ReaderLink *FindReader_code();
void AlterReader();
void BrowseReader();
void LostReader();


#endif
