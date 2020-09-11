#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
using namespace std;

//Date////////////////////////////////////////////////////
class Date
{
protected:
	int year;
	int month;
	int day;

public:
	Date();

	void GetDate();//将消费时间设置为系统当前时间
	void SetDate();//用户自主设置消费时间
	void SetYear(int y);
	void SetMonth(int m);
	void SetDay(int d);


	int GetYear();//返回年
	int GetMonth();//返回月
	int GetDay();//返回日

	void DisplayDate();//显示日期
};

//Account/////////////////////////////////////////////////
class Account
{
protected:
	string name;
	double number;
public:
	string GetName();
	double GetNumber();

	void SetName();
	void SetNumber();
	void DeleteName();
	void SetName(string na);
	void SetNumber(double num);
};

//Bankroll//////////////////////////////////////////
class Bankroll
{
protected:
	vector<Account> acc_vec;
	double total;

public:
	Bankroll();

	void ChangeAccount();//修改账户，修改后结果在容器中
	void DeleteAccount();//删除账户，删除后结果在容器中
	void AddAccount();//添加账户，添加后结果在容器中
	void DisplayAccount();//将容器中有效账户存入文件
	void ReadAccount();//融稳健中读取账户信息
	void PrintAccount();//输出资金账户列表
	void CountForAccount();//计算账户资金总额
};

//Record/////////////////////////////////////////////////
class Record:public Date,public Bankroll
{
protected:
	int flag;
	string InOrOut;
	string TypeIn;
	string TypeOut;
	string AccountName;
	double money;
public:
	Record();

	int GetFlag();
	string GetInOrOut();
	double GetMoney();
	string GetAccountName();
	string GetTypeIn();
	string GetTypeOut();

	void SetInOrOut(string ioo);
	void SetTypeIn(string ti);
	void SetTypeOut(string to);
	void SetAccountName(string acc_n);
	void SetMoney(double mon);


	void DeleteRecord();
	void ChangeRecord();
	void DisplayRecord(ofstream out);
	void PrintRecord();
};

class Day
{
protected:
	vector<Record>day;
	double SurplusDay;//日结余
	int TargetD;
	int TargetM;
	int TargetY;

public:
	Day();

	double GetSurplusDay();//返回日结余

	void IsToday(vector<Record>& rec_vec);//提取出指定日期的所有记录存入day容器
	void IsToday(vector<Record>& recvec,int,int,int);
	void CountForDay();//计算日结余
//	void DisplayDay();//保存日结余和日期到文件
	void PrintDay();//输出某天的记录到屏幕
//	void ReadDay();//从day.txt读日消费记录

};

//Report/////////////////////////////////////////////////////////
class Report
{
protected:
	vector<Record> Month;

	int TargetYear;
	int TargetMonth;

	double EntePer;
	double EnteAll;
	double ShopPer;
	double ShopAll;
	double TrafPer;
	double TrafAll;
	double FoodPer;
	double FoodAll;
	double HealPer;
	double HealAll;
	double StudPer;
	double StudAll;
	double LifePer;
	double LifeAll;
	double InvePer;
	double InveAll;
	double Else_outPer;
	double Else_outAll;

	double WorkPer;
	double WorkAll;
	double GiftPer;
	double GiftAll;
	double FinaPer;
	double FinaAll;
	double WelfPer;
	double WelfAll;
	double Else_inPer;
	double Else_inAll;

	double income;
	double outcome;
	double budget;
	double SurplusMonth;
public:
	Report();

	int GetTargetYear(){return TargetYear;}
	int GetTargetMonth(){return TargetMonth;}

	/*double GetEntePer(){return EntePer;}
	double GetEnteAll(){return EnteAll;}
	double GetShopPer(){return ShopPer;}
	double GetShopAll(){return ShopAll;}
	double GetTrafPer(){return TrafPer;}
	double GetTrafAll(){return TrafAll;}
	double GetFoodPer(){return FoodPer;}
	double GetFoodAll(){return FoodAll;}
	double GetHealPer(){return HealPer;}
	double GetHealAll(){return HealAll;}
	double GetStudPer(){return StudPer;}
	double GetStudAll(){return StudAll;}
	double GetLifePer(){return LifePer;}
	double GetLifeAll(){return LifeAll;}
	double GetInvePer(){return InvePer;}
	double GetInveAll(){return InveAll;}
	double GetElse_outPer(){return Else_outPer;}
	double GetElse_outAll(){return Else_outAll;}

	double GetWorkPer(){return WorkPer;}
	double GetWorkAll(){return WorkPer;}
	double GetGiftPer(){return GiftPer;}
	double GetGiftAll(){return GiftAll;}
	double GetFinaPer(){return FinaPer;}
	double GetFinaAll(){return FinaAll;}
	double GetWelfPer(){return WelfPer;}
	double GetWelfAll(){return WelfAll;}
	double GetElse_inPer(){return Else_inPer;}
	double GetElse_inAll(){return Else_inAll;}

	double Getincome(){return income;}
	double Getoutcome(){return outcome;}
	double Getbudget(){return budget;}
	double GetSurplusMonth(){return SurplusMonth;}
*/
	void CountForMonth();
	void IsThisMonth(vector<Record> &);
	void IsThisMonth(vector<Record> &,int ,int);
	void DisplayThisMonth(ofstream & out);
	void PrintThisMonth();
	void ReadThisMonth(ifstream & in);
};