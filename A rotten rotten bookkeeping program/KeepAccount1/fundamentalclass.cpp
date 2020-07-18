#include "fundamentalclass.h"
//using std::vector<Record>::iterator;

//Date////////////////////////////////////////////////////
Date::Date()
{
	year = 0;
	month = 0;
	day = 0;
}
void Date::GetDate()
{
	time_t t;
	tm * tp;
	t = time(NULL);
	tp = localtime(&t);
	year = tp->tm_year+1900;
	month = tp->tm_mon+1;
	day = tp->tm_mday;
}
void Date::SetDate()
{
	cout<<"请输入该条消费记录所属年："<<endl;
	cin>>year;

	cout<<"请输入该条消费记录所属月："<<endl;
	cin>>month;

	cout<<"请输入该条消费记录所属日："<<endl;
	cin>>day;

}
void Date::SetYear(int y)
{
	year = y;
}
void Date::SetMonth(int m)
{
	month = m;
}
void Date::SetDay(int d)
{
	day = d;
}

int Date::GetYear()
{
	return year;
}
int Date::GetMonth()
{
	return month;
}
int Date::GetDay()
{
	return day;
}
void Date::DisplayDate()
{
	cout<<"公元"<<year<<"-"<<month<<"-"<<day<<endl;
}


string Account::GetName()
{
	return name;
}
double Account::GetNumber()
{
	return number;
}
void Account::SetName(string na)
{
	name = na;
}
void Account::SetNumber(double num)
{
	number = num;
}

void Account::SetName()
{
	cout << "请输入账户名称:";
	cin >> name;
}
void Account::SetNumber()
{
	cout << "请输入此账户中的金额总数:";
	cin >> number;
}
void Account::DeleteName()
{
	name.assign("0");
	number = 0;
}


//Bankroll///////////////////////////////////////////
Bankroll::Bankroll()
{}
void Bankroll::ChangeAccount()
{
	int n;
	for(int i=0;i<acc_vec.size();i++)
	{
		cout<<i<<".";
		cout<<acc_vec.at(i).GetName()<<" "<<acc_vec.at(i).GetNumber()<<endl;
	}

	cout<<endl;
	cout<<"请选择您需要修改的资金账户代号："<<endl;
	cin>>n;
//	cout<<"请输入金额："<<endl;
//	cin>>num;
	acc_vec.at(n).SetNumber();

	cout<<"修改成功，结果如下："<<endl;
	cout<<acc_vec.at(n).GetName()<<" "<<acc_vec.at(n).GetNumber()<<endl;
	CountForAccount();
	
}
void Bankroll::DeleteAccount()
{
	int n;
	for(int i=0;i<acc_vec.size();i++)
	{
		cout<<i<<".";
		cout<<acc_vec.at(i).GetName()<<" "<<acc_vec.at(i).GetNumber()<<endl;
	}

	cout<<endl;
	cout<<"请选择您需要修改的资金账户代号："<<endl;
	cin>>n;

	acc_vec.at(n).DeleteName();
	CountForAccount();
	cout<<"删除成功"<<endl;

}
void Bankroll::AddAccount()
{
	Account a;
	ReadAccount();

	a.SetName();
	a.SetNumber();

	acc_vec.push_back(a);
	CountForAccount();

	cout<<"添加成功"<<endl;
	DisplayAccount();
}
void Bankroll::DisplayAccount()//输出到文件
{
	ofstream out;
	out.open("account.txt");
	if( !out )
	{
		cout<<"文件打开失败"<<endl;
	}

	for(int i = 0;i<acc_vec.size();i++)
	{
		if(acc_vec.at(i).GetName() != "0")
		{
			out<<acc_vec.at(i).GetName()<<" "<<acc_vec.at(i).GetNumber()<<endl;
		}
	}
	out.close();
	acc_vec.clear();
	cout<<"账户资金数据已刷新"<<endl;

}

void Bankroll::ReadAccount()
{
	
	Account a;
	string na;
	double num;
	ifstream in;
	in.open("account.txt");
	if( !in )
	{
		cout<<"文件打开失败"<<endl;
	}

	while( !in.eof() )
	{
		in>>na>>num;
		a.SetName(na);
		a.SetNumber(num);
		acc_vec.push_back(a);
		
	}
	acc_vec.pop_back();


}
void Bankroll::CountForAccount()
{
	total = 0.0;
	for(int i=0;i<acc_vec.size();i++)
	{
		total = total + acc_vec.at(i).GetNumber();
	}

}

void Bankroll::PrintAccount()
{
	CountForAccount();
	cout<<"总额："<<total<<"元"<<endl;
	for(int i=0;i<acc_vec.size();i++)
	{
		cout<<i<<".";
		cout<<acc_vec.at(i).GetName()<<" ";
		cout<<acc_vec.at(i).GetNumber()<<"元"<<endl;
	}
}


Record::Record()
{
	flag = 1;
}
int Record::GetFlag()
{
	return flag;
}
string Record::GetInOrOut()
{
	return InOrOut;
}
double Record::GetMoney()
{
	return money;
}
string Record::GetAccountName()
{
	return AccountName;
}
string Record::GetTypeIn()
{
	return TypeIn;
}
string Record::GetTypeOut()
{
	return TypeOut;
}
void Record::SetInOrOut(string ioo)
{
	InOrOut = ioo;
}
void Record::SetTypeIn(string ti)
{
	TypeIn = ti;
}
void Record::SetTypeOut(string to)
{
	TypeOut = to;
}
void Record::SetAccountName(string acc_n)
{
	AccountName = acc_n;
}
void Record::SetMoney(double mon)
{
	money = mon;
}
void Record::DeleteRecord()
{
	flag = 0;
}
void Record::ChangeRecord()
{
	char choice1,choice2;
	int choice3;
	do{
		cout << "请选择账目类型:1.支出2.收入" << endl;
		cin >> choice1;
		
		if(choice1=='1')
		{
			InOrOut.assign("支出");
			do{
				cout << "请选择支出类型:" << "\n" 
					<< "1.娱乐 2.购物 3.交通 4.饮食 5.健康 6.学习 7.生活 8.投资 9.其他" << endl;
				cin >> choice2;
				switch(choice2)
				{
				case '1':
					TypeOut.assign("娱乐");
					break;
				case '2':
					TypeOut.assign("购物");
					break;
				case '3':
					TypeOut.assign("交通");
					break;
				case '4':
					TypeOut.assign("饮食");
					break;
				case '5':
					TypeOut.assign("健康");
					break;
				case '6':
					TypeOut.assign("学习");
					break;
				case '7':
					TypeOut.assign("生活");
					break;
				case '8':
					TypeOut.assign("投资");
					break;
				case '9':
					TypeOut.assign("其他");
					break;
				default:
					cout << "输入错误!" << endl;
				}
			}while(choice2<'1'||choice2>'9');
		}else if(choice1=='2')
		{
			InOrOut.assign("收入");
			do{
				cout << "请输入收入类型:" << "\n"
					<< "1.工作 2.礼金 3.投资 4.福利保险 5.其他" << endl;
				cin >> choice2;
				switch(choice2)
				{
				case '1':
					TypeIn.assign("工作");
					break;
				case '2':
					TypeIn.assign("礼金");
					break;
				case '3':
					TypeIn.assign("投资");
					break;
				case '4':
					TypeIn.assign("福利保险");
					break;
				case '5':
					TypeIn.assign("其他");
					break;
				default:
					cout << "输入错误!" << endl;
				}
			}while(choice2<'1'||choice2>'5');
		}else{
			cout << "输入错误!" << endl;
		}
	}while(choice1<'1'||choice1>'2');
	cout << "请选择该项资金变动的账户名:" << endl;
	acc_vec.clear();
	ReadAccount();
	PrintAccount();
	cin >> choice3;
	AccountName = acc_vec.at(choice3).GetName();
	cout << "请输入金额(单位:元):";
	cin >> money;
}
void Record::DisplayRecord(ofstream out)
{
	out << GetYear() << " " << GetMonth() << " " << GetDay() << setw(10) << InOrOut;
	if(InOrOut.compare("支出") == 0)
	{
		out << setw(10) << TypeOut;
	}
	if(InOrOut.compare("收入") == 0)
	{
		out << setw(10) << TypeIn;
	}
	out << setw(10) << money << setw(20) << AccountName << endl;
}
void Record::PrintRecord()
{
	cout << GetYear() << "-" << GetMonth() << "-" << GetDay() << setw(10) << InOrOut;
	if(InOrOut.compare("支出") == 0)
	{
		cout << setw(10) << TypeOut;
	}
	if(InOrOut.compare("收入") == 0)
	{
		cout << setw(10) << TypeIn;
	}
	cout << setw(10) << money << "元" << setw(20) << "账户:" << AccountName << endl;
}


//Day/////////////////////////////////////////////////
Day::Day()
{}
double Day::GetSurplusDay()
{
	return SurplusDay;
}
//////////////////////////////////////////////////////////////改////////////////////////////////////////////
void Day::IsToday(vector<Record>& rec_vec)
{
	int y,m,d;
	char today;
	//获取当前日期	
	time_t t;
	tm * tp;
	t = time(NULL);
	tp = localtime(&t);
	y = tp->tm_year+1900;
	m = tp->tm_mon+1;
	d = tp->tm_mday;

	cout<<"是否查看今日记录？（Y/N）"<<endl;
	cin>>today;


	if(today == 'N')
	{
		cout<<"请输入要查看的日期所属年："<<endl;
		cin>>y;
		cout<<"请输入要查看的日期所属月："<<endl;
		cin>>m;
		cout<<"请输入要查看的日期所属日："<<endl;
		cin>>d;
	}

	for(int i=0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			day.push_back(rec_vec.at(i));
		}
	}
	 if(day.empty())
	 {
		 cout<<"没有该日期的相关记录"<<endl;
	 }
}
void Day::IsToday(vector<Record>& rec_vec,int y,int m,int d)
{
	for(int i=0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			day.push_back(rec_vec.at(i));
		}
	}
}
/*void Day::IsToday(vector<Record>& rec_vec)
{
	int y,m,d;
	char today;
	//获取当前日期	
	time_t t;
	tm * tp;
	t = time(NULL);
	tp = localtime(&t);
	y = tp->tm_year+1900;
	m = tp->tm_mon+1;
	d = tp->tm_mday;

	cout<<"是否查看今日记录？（Y/N）"<<endl;
	cin>>today;

	int find = 1;
	if(today == 'N')
	{
		cout<<"请输入要查看的日期所属年："<<endl;
		cin>>y;
		cout<<"请输入要查看的日期所属月："<<endl;
		cin>>m;
		cout<<"请输入要查看的日期所属日："<<endl;
		cin>>d;
	}
	for(int i=0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			find = 0;
			day.push_back(rec_vec.at(i));
		}
	}
	if(find)
	{
		cout << "未找到该日期的数据记录" << endl;
	}
}*/
/*int Day::IsToday(vector<Record> & rec_vec,int y,int m,int d)
{
	for(int i=0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			day.push_back(rec_vec.at(i));
		}
	}
	return i;
}*/
void Day::CountForDay()
{
	double a=0.0,b=0.0;
	for(int i=0;i<day.size();i++)
	{

		if(day.at(i).GetInOrOut().compare("收入") == 0)
		{
			a = a+day.at(i).GetMoney();
		}
		else
		{
			b = b+day.at(i).GetMoney();
		}
	}
		SurplusDay = a-b;

	
}
/////////////////////////////////////////////////////////////修改///////////////////////////////////////////////////////
/*void Day::DisplayDay()//输出到文件
{
	ofstream out;	
	out.open("day.txt",ios);
	if( !out )
	{
		cout<<"文件打开失败"<<endl;
	}

	out<<day.at(0).GetYear()<<" "<<day.at(0).GetMonth()<<" "<<day.at(0).GetDay();
	out<<SurplusDay<<" ";
	out<<day.at(i).GetAccountName()<<endl;

	out.close();

}*/
/////////////////////////////////////////////////////////////改/////////////////////////////////////////////////
void Day::PrintDay()//输出到屏幕
{
	day.at(0).GetDate();//输出日期
	cout<<"收支情况如下："<<endl;
	cout<<endl;
	cout<<"日结余："<<SurplusDay<<endl;
	cout<<endl;

	cout<<"详情："<<endl;
	for(int i = 0;i<day.size();i++)
	{
		cout << i <<"." ;
		//输出收入或支出，以及具体收入或消费类型
		if(day.at(i).GetInOrOut().compare("收入") == 0)
		{
			cout<<"收入 "<<day.at(i).GetTypeIn();
		}
		else
		{
			cout<<"支出 "<<day.at(i).GetTypeOut()<<" ";
		}

		cout<<day.at(i).GetMoney() << " ";//输出金额
		cout<<day.at(i).GetAccountName();
		cout<<endl;
	}
		day.clear();
}
/*void Day::PrintDay()//输出到屏幕
{
	day.at(0).GetDate();//输出日期
	cout << day.at(0).GetYear() << "-" << day.at(0).GetMonth() << "-" <<day.at(0).GetDay() << endl;
	cout<<"收支情况如下："<<endl;
	cout<<"日结余："<<SurplusDay<<endl;
	cout<<endl;

	cout<<"详情："<<endl;
	for(int i = 0;i<day.size();i++)
	{
		cout <<i<<".";
		//输出收入或支出，以及具体收入或消费类型
		if(day.at(i).GetInOrOut().compare("收入") == 0)
		{
			cout<<"收入 "<<day.at(i).GetTypeIn()<<" ";
		}
		else
		{
			cout<<"支出 "<<day.at(i).GetTypeOut()<<" ";
		}

		cout<<day.at(i).GetMoney()<< " 账户:" << day.at(i).GetAccountName()<<endl;//输出金额
	}
}
void Day::ReadDay()
{
	ifstream in("day.txt");
	if( !in )
	{
		cout<<"文件打开失败!"<<endl;
		return;
	}

	in>>TargetY>>TargetM>>TargetD>>SurplusDay>>SurplusDay;
	in.close(); 
	
}
*/

Report::Report()
{
	EntePer = 0;
	EnteAll = 0;
	ShopPer = 0;
	ShopAll = 0;
	TrafPer = 0;
	TrafAll = 0;
	FoodPer = 0;
	FoodAll = 0;
	HealPer = 0;
	HealAll = 0;
	StudPer = 0;
	StudAll = 0;
	LifePer = 0;
	LifeAll = 0;
	InvePer = 0;
	InveAll = 0;
	Else_outPer = 0;
	Else_outAll = 0;

	WorkPer = 0;
	WorkAll = 0;
	GiftPer = 0;
	GiftAll = 0;
	FinaPer = 0;
	FinaAll = 0;
	WelfPer = 0;
	WelfAll = 0;
	Else_inPer = 0;
	Else_inAll = 0;

	income = 0;
	outcome = 0;
	budget = 0;
	SurplusMonth = 0;
}
void Report::CountForMonth()
{
	TargetYear = Month.at(0).GetYear();
	TargetMonth = Month.at(0).GetMonth();

	for(int i=0; i<Month.size(); i++)
	{
		
		if(Month.at(i).GetInOrOut().compare("支出")==0)
		{
			outcome += Month.at(i).GetMoney();
			if(Month.at(i).GetTypeOut().compare("娱乐")==0)
			{
				EnteAll +=Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("购物")==0)
			{
				ShopAll +=Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("交通")==0)
			{
				TrafAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("饮食")==0)
			{
				FoodAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("健康")==0)
			{
				HealAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("学习")==0)
			{
				StudAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("生活")==0)
			{
				LifeAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("投资")==0)
			{
				InveAll +=Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("其他")==0)
			{
				Else_outAll += Month.at(i).GetMoney();
			}
		}

		if(Month.at(i).GetInOrOut().compare("收入")==0)
		{
			income += Month.at(i).GetMoney();
			if(Month.at(i).GetTypeIn().compare("工作")==0)
			{
				WorkAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("礼金")==0)
			{
				GiftAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("投资")==0)
			{
				FinaAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("福利保险")==0)
			{
				WelfAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("其他")==0)
			{
				Else_inAll += Month.at(i).GetMoney();
			}
		}
	}
	if(outcome!=0)
	{
		EntePer = EnteAll/outcome*100;
		ShopPer = ShopAll/outcome*100;
		TrafPer = TrafAll/outcome*100;
		FoodPer = FoodAll/outcome*100;
		HealPer = HealAll/outcome*100;
		StudPer = StudAll/outcome*100;
		LifePer = LifeAll/outcome*100;
		InvePer = InveAll/outcome*100;
		Else_outPer = Else_outAll/outcome*100;
	}
	if(income!=0)
	{
		WorkPer = WorkAll/income*100;
		GiftPer = GiftAll/income*100;
		FinaPer = FinaAll/income*100;
		WelfPer = WelfAll/income*100;
		Else_inPer = Else_inAll/income*100;
	}

	SurplusMonth = income - outcome;
}
///////////////////////////////////////////////////////////改///////////////////////////////////////////////
void Report::IsThisMonth(vector<Record> & All)
{
	char thisMon;
	Date now;

	cout << "是否查看本月记录?(Y/N)" << endl;
	cin >> thisMon;
	do{
		switch(thisMon)
		{
		case 'Y':
		case 'y':
			now.GetDate();
			TargetYear = now.GetYear();
			TargetMonth = now.GetMonth();
			break;
		case 'N':
		case 'n':
			cout << "请输入要查看的日期所属年:" << endl;
			cin >> TargetYear;
			cout << "请输入要查看的日期所属月:" << endl;
			cin >> TargetMonth;
			break;
		default:
			cout << "输入错误!" << endl;
		}
	}while(thisMon!='Y' && thisMon!='y' && thisMon!='n' && thisMon!='N');

	vector<Record>::iterator p;
	for(p = All.begin(); p!=All.end(); p++)
	{
		if(p->GetYear()==TargetYear && p->GetMonth()==TargetMonth)
		{
			Month.push_back(*p);
		}
	}
}
////////////////////////////////////////////////////////////////增/////////////////////////////////////////////////////////////////
void Report::IsThisMonth(vector<Record> & All,int y,int m)
{
	for(int i=0; i<All.size(); i++)
	{
		if(All.at(i).GetYear()==y && All.at(i).GetMonth()==m)
		{
			Month.push_back(All.at(i));
		}
	}
}
void Report::DisplayThisMonth(ofstream & out)
{
/*	out << TargetYear << " " << TargetMonth << endl;
	out << SurplusMonth << " " << income << " " << outcome << endl;

	out << EnteAll << " " << EntePer << endl;
	out << ShopAll << " " << ShopPer << endl;
	out << TrafAll << " " << TrafPer << endl;
	out << FoodAll << " " << FoodPer << endl;
	out << HealAll << " " << HealPer << endl;
	out << StudAll << " " << StudPer << endl;
	out << LifeAll << " " << LifePer << endl;
	out << InveAll << " " << InvePer << endl;
	out << Else_outAll << " " << Else_outPer << endl;

	out << WorkAll << " " << WorkPer << endl;
	out << GiftAll << " " << GiftPer << endl;
	out << FinaAll << " " << FinaPer << endl;
	out << WelfAll << " " << WelfPer << endl;
	out << Else_inAll << " " << Else_inPer << endl;
	*/
	/*out << setw(10) << TargetYear << setw(10) << TargetMonth << endl
		<< SurplusMonth << " " << income << " " << outcome << endl

		<< EnteAll << " " << EntePer << endl
		<< ShopAll << " " << ShopPer << endl
		<< TrafAll << " " << TrafPer << endl
		<< FoodAll << " " << FoodPer << endl
		<< HealAll << " " << HealPer << endl
		<< StudAll << " " << StudPer << endl
		<< LifeAll << " " << LifePer << endl
		<< InveAll << " " << InvePer << endl
		<< Else_outAll << " " << Else_outPer << endl

		<< WorkAll << " " << WorkPer << endl
		<< GiftAll << " " << GiftPer << endl
		<< FinaAll << " " << FinaPer << endl
		<< WelfAll << " " << WelfPer << endl
		<< Else_inAll << " " << Else_inPer << endl;
		*/
	out << setw(10) << TargetYear << setw(10) << TargetMonth 
		<< setw(10) << SurplusMonth << setw(10) << income << setw(10) << outcome

		<< setw(10) << EnteAll << setw(10) << EntePer 
		<< setw(10) << ShopAll << setw(10) << ShopPer 
		<< setw(10) << TrafAll << setw(10) << TrafPer 
		<< setw(10) << FoodAll << setw(10) << FoodPer 
		<< setw(10) << HealAll << setw(10) << HealPer 
		<< setw(10) << StudAll << setw(10) << StudPer 
		<< setw(10) << LifeAll << setw(10) << LifePer 
		<< setw(10) << InveAll << setw(10) << InvePer 
		<< setw(10) << Else_outAll << setw(10) << Else_outPer 

		<< setw(10) << WorkAll << setw(10) << WorkPer 
		<< setw(10) << GiftAll << setw(10) << GiftPer 
		<< setw(10) << FinaAll << setw(10) << FinaPer 
		<< setw(10) << WelfAll << setw(10) << WelfPer 
		<< setw(10) << Else_inAll << setw(10) << Else_inPer << endl;
}
void Report::PrintThisMonth()
{
	cout << TargetYear << "-" << TargetMonth << endl;
	cout << "当月盈余:" << SurplusMonth << endl;

	cout << "支出:" << outcome << endl;
	cout << setw(10) << "支出类型" << setw(10) << "金额" << setw(20) << "所占百分比" << endl;
	cout << setw(10) << "娱乐" << setw(10) << EnteAll << setw(20) << EntePer << "%" << endl;
	cout << setw(10) << "购物" << setw(10) << ShopAll << setw(20) << ShopPer << "%" << endl;
	cout << setw(10) << "交通" << setw(10) << TrafAll << setw(20) << TrafPer << "%" << endl;
	cout << setw(10) << "饮食" << setw(10) << FoodAll << setw(20) << FoodPer << "%" << endl;
	cout << setw(10) << "健康" << setw(10) << HealAll << setw(20) << HealPer << "%" << endl;
	cout << setw(10) << "学习" << setw(10) << StudAll << setw(20) << StudPer << "%" << endl;
	cout << setw(10) << "生活" << setw(10) << LifeAll << setw(20) << LifePer << "%" << endl;
	cout << setw(10) << "投资" << setw(10) << InveAll << setw(20) << InvePer << "%" << endl;
	cout << setw(10) << "其他" << setw(10) << Else_outAll << setw(20) << Else_outPer << "%" << endl;

	cout << "收入:" << income << endl;
	cout << setw(10) << "收入类型" << setw(10) << "金额" << setw(20) << "所占百分比" << endl;
	cout << setw(10) << "工作" << setw(10) << WorkAll << setw(20) << WorkPer << "%" << endl;
	cout << setw(10) << "礼金" << setw(10) << GiftAll << setw(20) << GiftPer << "%" << endl;
	cout << setw(10) << "投资" << setw(10) << FinaAll << setw(20) << FinaPer << "%" << endl;
	cout << setw(10) << "福利保险" << setw(10) << WelfAll << setw(20) << WelfPer << "%" << endl;
	cout << setw(10) << "其他" << setw(10) << Else_inAll << setw(20) << Else_inPer << "%" << endl;
}
void Report::ReadThisMonth(ifstream & in)//////////////////////////////////////////////新加//////////////////////////////////////////////
{
/*	in >> TargetYear >> TargetMonth
		>> SurplusMonth >> income >> outcome

		>> EnteAll >> EntePer
		>> ShopAll >> ShopPer
		>> TrafAll >> TrafPer
		>> FoodAll >> FoodPer
		>> HealAll >> HealPer
		>> StudAll >> StudPer
	in >> LifeAll >> LifePer
	in >> InveAll >> InvePer
	in >> Else_outAll >> Else_outPer

	in >> WorkAll >> WorkPer
	in >> GiftAll >> GiftPer
	in >> FinaAll >> FinaPer
	in >> WelfAll >> WelfPer
	in >> Else_inAll >> Else_inPer
	*/
	in >> TargetYear >> TargetMonth
		>> SurplusMonth >> income >> outcome

		>> EnteAll >> EntePer
		>> ShopAll >> ShopPer
		>> TrafAll >> TrafPer
		>> FoodAll >> FoodPer
		>> HealAll >> HealPer
		>> StudAll >> StudPer
		>> LifeAll >> LifePer
		>> InveAll >> InvePer
		>> Else_outAll >> Else_outPer

		>> WorkAll >> WorkPer
		>> GiftAll >> GiftPer
		>> FinaAll >> FinaPer
		>> WelfAll >> WelfPer
		>> Else_inAll >> Else_inPer;
}