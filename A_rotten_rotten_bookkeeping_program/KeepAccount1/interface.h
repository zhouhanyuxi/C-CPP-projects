#include "fundamentalclass.h"

class Interface:public Record,public Report,public Day
{
protected:
	vector<Record> rec_vec;
	vector<Report> rep_vec;
public:
	Interface();
	

	int MainMenu();
	int RecordMenu();
	int ConsumeMenu();
	int AccountMenu();
	void AccountAll();
	void ConsumeAll();
	void RecordAll();

	void ReadFromFile();
	void WriteToFile();
//	void ReadFromFileDay();
	void ReadReport();
	void WriteReport();

	void AddRecord();
	void Record_Delete();
	void Record_Change();
	double SetBudget();

	void Browse_Day(vector<Record>& rec_vec);
	void Browse_Report();

	

	void Run();
};