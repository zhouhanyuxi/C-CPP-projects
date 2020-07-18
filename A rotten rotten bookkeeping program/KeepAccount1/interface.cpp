#include"Interface.h"

Interface::Interface()
{}
int Interface::MainMenu()
{
	int option;
	cout<<"***************************************************"<<endl;
	cout<<"*          一个烂烂的记账程序 （1.0.0）           *"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"*                    主菜单                       *"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"*                  1.记账                         *"<<endl;
	cout<<"*                  2.查看收支情况                 *"<<endl;
	cout<<"*                  3.管理资金账户                 *"<<endl;
	cout<<"*                  0.退出                         *"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"*                    开发者                       *"<<endl;
	cout<<"*      周寒聿西                  赵书函           *"<<endl;
	cout<<"*      软工152班                 软工152班        *"<<endl;
	cout<<"*      8000115057                8000115056       *"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"*                  2016.6.17                      *"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"请输入您的选择："<<endl;
	cin>>option;
	return option;
}

int Interface::RecordMenu()
{
	int option;
	cout<<"*********************************"<<endl;
	cout<<"*              记账             *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*          1.新增收支记录       *"<<endl;
	cout<<"*          2.删除记录           *"<<endl;
	cout<<"*          3.修改记录           *"<<endl;
	cout<<"*          4.设置预算           *"<<endl;
	cout<<"*          0.退出               *"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<endl;
	cout<<"请输入您的选择：";
	cin>>option;
	return option;
}

int Interface::ConsumeMenu()
{
	int option;
	cout<<"*********************************"<<endl;
	cout<<"*          收支情况查询         *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*        1.查询日收支情况       *"<<endl;
	cout<<"*        2.查询月收支分析报表   *"<<endl;
	cout<<"*        0.退出                 *"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<endl;
	cout<<"请输入您的选择：";
	cin>>option;
	return option;

}

int Interface::AccountMenu()
{
	int option;
	cout<<"*********************************"<<endl;
	cout<<"*          资金账户管理         *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*        1.添加资金来源账户     *"<<endl;
	cout<<"*        2.删除资金来源账户     *"<<endl;
	cout<<"*        3.修改资金来源账户     *"<<endl;
	cout<<"*        4.查看资金来源账户     *"<<endl;
	cout<<"*        0.退出                 *"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"请输入您的选择：";
	cin>>option;
	return option;

}



void Interface::ReadFromFile()
{
//	int i = 0;
	int y,m,d;
	double mon;
	string i_or_o,type,acc;
	Record R;

	ifstream in("record.txt",ios::in);
	if( !in )
	{
		cout<<"文件打开失败!"<<endl;
		return;
	}

	while(!in.eof())
	{
		in>>y>>m>>d>>i_or_o>>type>>mon>>acc;
		R.SetYear(y);
		R.SetMonth(m);
		R.SetDay(d);
		R.SetInOrOut(i_or_o);
		if(i_or_o.compare("收入") == 0)
		{
			R.SetTypeIn(type);
		}
		else
		{
			R.SetTypeOut(type);

		}
		R.SetMoney(mon);
		R.SetAccountName(acc);

		rec_vec.push_back(R);

//		i=i+1;
	}
	if(!rec_vec.empty())
	{
		rec_vec.pop_back();
	}
	in.close(); 
	
}
	
void Interface::WriteToFile()
{
	ofstream out;
	out.open("record.txt",ios::out);
	if( !out )
	{
		cout<<"文件打开失败"<<endl;
		return;
	}

	for(int i = 0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetFlag() == 1)
		{
			out<<rec_vec.at(i).GetYear()<<" "<<rec_vec.at(i).GetMonth()<<" "<<rec_vec.at(i).GetDay();
			out<<" "<<rec_vec.at(i).GetInOrOut()<<" ";

			if((rec_vec.at(i).GetInOrOut().compare("收入") == 0))
			{
				out<<rec_vec.at(i).GetTypeIn()<<" ";
			}
			else
			{
				out<<rec_vec.at(i).GetTypeOut()<<" ";
			}

			out<<rec_vec.at(i).GetMoney() << " " <<rec_vec.at(i).GetAccountName()<<endl;
		}
	}
	out.close();
	rec_vec.clear();//清除纪录
}

/*
void Interface::ReadFromFileDay()
{
	int y,m,d;
	double sur;

	ifstream in;
	in.open("day.txt");

	in>>y>>m>>d>>sur;
	TargetY = y;
	TargetM = m;
	TargetD = d;
	SurplusDay = sur;
}
*/

void Interface::Run()
{
	int option;
	
	do
	{
		option =  MainMenu();
		switch( option )
		{
		case 1:
			system("cls");
			RecordAll();
			break;
		case 2:
			system("cls");
			ConsumeAll();
			break;
		case 3:
			system("cls");
			AccountAll();
			break;
		case 0:
			break;

		}
	}while(option);
	
}

void Interface::AccountAll()
{
	int option;
	
	do
	{
		option = AccountMenu();
		switch(option)
		{
		case 1:
			system("cls");
			acc_vec.clear();
			AddAccount();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			acc_vec.clear();
			ReadAccount();
			if(!acc_vec.empty())
			{
				DeleteAccount();
				DisplayAccount();
			}
			else
			{
				cout<<"（°ο°）您的资金账户目前为空,需要先添加资金账户才能进行此操作哦~"<<endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			acc_vec.clear();
			ReadAccount();
			if(!acc_vec.empty())
			{
				ChangeAccount();
				DisplayAccount();
			}
			else
			{
				cout<<"（°ο°）您的资金账户目前为空,需要先添加资金账户才能进行此操作哦~"<<endl;
			}
			system("pause");
			system("cls");

			break;
		case 4:
			system("cls");
			acc_vec.clear();
			ReadAccount();
			if(!acc_vec.empty())
			{
				PrintAccount();
			}
			else
			{
				cout<<"（°ο°）您的资金账户目前为空,需要先添加资金账户才能进行此操作哦~"<<endl;
			}
			system("pause");
			system("cls");

			break;
		case 0:
			system("cls");
			break;
		default:
			cout<<"输入有误，将返回上一级(＞﹏＜）"<<endl;
			system("pause");
			system("cls");
			break;


		}//switch

	}while(option);
}


void Interface::Browse_Day(vector<Record>& rec_vec)
{
	Day::day.clear();
	IsToday(rec_vec);//提取出指定日期的所有记录存入day容器
	if(!Day::day.empty())
	{
		CountForDay();
		PrintDay();
	}
	else
	{
		cout<<"返回上一级"<<endl;
	}
}

void Interface::ConsumeAll()
{
	int option;
	do
	{
		option = ConsumeMenu();
		switch(option)
		{
		case 1:
			system("cls");
			rec_vec.clear();
			ReadFromFile();
			Browse_Day(rec_vec);
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			Browse_Report();
			system("pause");
			system("cls");
			break;
		case 0:
			system("cls");
			break;
		default:
			cout<<"输入有误，将返回上一级(＞﹏＜）"<<endl;
			system("pause");
			system("cls");
			break;


		}

	}while(option);

}

void Interface::RecordAll()
{
	int option;
	do
	{
		option = RecordMenu();
		switch(option)
		{
		case 1:
			system("cls");
			AddRecord();
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			Record_Delete();
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			Record_Change();
			system("pause");
			system("cls");
			break;
		case 4:
			SetBudget();
			system("pause");
			system("cls");
			break;
		case 0:
			system("cls");
			break;
		default:
			cout<<"输入有误，将返回上一级(＞﹏＜）"<<endl;
			system("pause");
			system("cls");
			break;
		}
	}while(option);
}

void Interface::ReadReport()
{
	ifstream in;
	in.open("Report.txt",ios::in);
	if(!in)
	{
		cout << "文件打开失败!" << endl;
	}else{
		Report temp;
		while(!in.eof())
		{
			temp.ReadThisMonth(in);
			rep_vec.push_back(temp);
		}
		if(!rep_vec.empty())
		{
			rep_vec.pop_back();
		}
		cout << "已读入各月报表" << endl;
		in.close();
	}
}

void Interface::WriteReport()
{
	ofstream out;
	out.open("report.txt",ios::trunc);
	if(!out)
	{
		cout << "文件打开失败!" << endl;
	}else{
		for(int i=0; i<rep_vec.size(); i++)
		{
			rep_vec.at(i).DisplayThisMonth(out);
		}
		cout << "月报表已存入文件中" << endl;
		out.close();
		rep_vec.clear();
	}
}


void Interface::AddRecord()
{
	Record temp1;
	char today;

	//新增一条记录
	cout << "是否将该项收支记录的日期设为今天?(Y/N)" << endl;
	cin >> today;
	if(today=='y' || today=='Y')
	{
		temp1.GetDate();
	}else if(today=='n' || today=='N')
	{
		temp1.SetDate();
	}

	temp1.ChangeRecord();
	ReadFromFile();
	
	rec_vec.push_back(temp1);
	

	//刷新或生成月报表
	ReadReport();
	int y = temp1.GetYear();
	int m = temp1.GetMonth();
	int find=1;
	
	for(int i=0; i<rep_vec.size(); i++)
	{	
		if(rep_vec.at(i).GetTargetYear() == y && rep_vec.at(i).GetTargetMonth() == m)
		{
			find = 0;
			rep_vec.at(i).IsThisMonth(rec_vec,y,m);
			rep_vec.at(i).CountForMonth();
		}
	}
	if(find)
	{
		Report temp2;
		temp2.IsThisMonth(rec_vec,y,m);
		temp2.CountForMonth();
		rep_vec.push_back(temp2);
	}
	cout << "月报表已更新" << endl;
	WriteReport();

	//刷新资金账户数据
	ReadAccount();
	for(i=0; i<acc_vec.size(); i++)
	{
		if(temp1.GetAccountName().compare(acc_vec.at(i).GetName()) == 0)
		{
			if(temp1.GetInOrOut().compare("支出") == 0)
			{
				acc_vec.at(i).SetNumber(acc_vec.at(i).GetNumber()-temp1.GetMoney());
			}
			if(temp1.GetInOrOut().compare("收入") == 0)
			{
				acc_vec.at(i).SetNumber(acc_vec.at(i).GetNumber()+temp1.GetMoney());
			}
		}
	}
	cout << "资金账户数据已更新" << endl;
	DisplayAccount();

	WriteToFile();
}


void Interface::Record_Delete()
{
	int y,m,d,num,k;
	int find=1;

	ReadFromFile();

	cout << "请输入记录所属日期:" << endl;
	cout << "年:";
	cin >> y;
	cout << "月:";
	cin >> m;
	cout << "日:";
	cin >> d;

	int count=0;
	for(int i=0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			find = 0;
			Day::day.push_back(rec_vec.at(i));
			count++;
		}
	}
	if(find)
	{
		cout << "未找到该日期对应的数据记录" << endl;
		rec_vec.clear();
		return;
	}

	CountForDay();
	PrintDay();
	do{
		cout << "请输入该条要删除的记录的序号:" ;
		cin >> num;
	}while(num<0||num>=count);
	count=0;
	for(i=0; i<rec_vec.size(); i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			count++;
			if(count == (num+1))
			{
				k = i;
			}
		}
	}

	//还原资金账户数据
	ReadAccount();
	for(int j=0; j<acc_vec.size(); j++)
	{
		if(rec_vec.at(k).GetAccountName().compare(acc_vec.at(j).GetName()) == 0)
		{
			if(rec_vec.at(k).GetInOrOut().compare("支出") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()+rec_vec.at(k).GetMoney());
			}
			if(rec_vec.at(k).GetInOrOut().compare("收入") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()-rec_vec.at(k).GetMoney());
			}
		}
	}
	DisplayAccount();

	//标记删除
	rec_vec.at(k).DeleteRecord();

	WriteToFile();
	cout << "记录删除成功" << endl;

	//更新月报表
	ReadFromFile();
	ReadReport();
	for(i=0; i<rep_vec.size(); i++)
	{
		if(rep_vec.at(i).GetTargetYear() == y && rep_vec.at(i).GetTargetMonth() == m)
		{
			rep_vec.at(i).IsThisMonth(rec_vec,y,m);
			rep_vec.at(i).CountForMonth();
		}
	}
	cout << "月报表已更新" << endl;
	Day::day.clear();
	WriteReport();
	WriteToFile();
}


void Interface::Record_Change()
{
	int y,m,d,num,k;

	ReadFromFile();
	cout << "请输入记录所属日期:" << endl;
	cout << "年:";
	cin >> y;
	cout << "月:";
	cin >> m;
	cout << "日:";
	cin >> d;
	
	int find=1;
	int count=0;
	for(int i=0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			find = 0;
			Day::day.push_back(rec_vec.at(i));
			count++;
		}
	}
	if(find)
	{
		cout << "未找到该日期对应的数据记录" << endl;
		rec_vec.clear();
		return;
	}

	CountForDay();
	PrintDay();
	do{
		cout << "请输入该条要修改的记录的序号:" ;
		cin >> num;
	}while(num<0||num>=count);
	count=0;
	for(i=0; i<rec_vec.size(); i++)
	{
		if(rec_vec.at(i).GetDay()==d && rec_vec.at(i).GetMonth()==m && rec_vec.at(i).GetYear()==y)
		{
			count++;
			if(count == (num+1))
			{
				k = i;
			}
		}
	}

	//还原资金账户数据
	ReadAccount();
	for(int j=0; j<acc_vec.size(); j++)
	{
		if(rec_vec.at(k).GetAccountName().compare(acc_vec.at(j).GetName()) == 0)
		{
			if(rec_vec.at(k).GetInOrOut().compare("支出") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()+rec_vec.at(k).GetMoney());
			}
			if(rec_vec.at(k).GetInOrOut().compare("收入") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()-rec_vec.at(k).GetMoney());
			}
		}
	}
	DisplayAccount();

	//修改记录
	rec_vec.at(k).ChangeRecord();

	//刷新资金账户数据
	ReadAccount();
	for(j=0; j<acc_vec.size(); j++)
	{
		if(rec_vec.at(k).GetAccountName().compare(acc_vec.at(j).GetName()) == 0)
		{
			if(rec_vec.at(k).GetInOrOut().compare("支出") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()-rec_vec.at(k).GetMoney());
			}
			if(rec_vec.at(k).GetInOrOut().compare("收入") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()+rec_vec.at(k).GetMoney());
			}
		}
	}

	cout << "资金账户数据已更新" << endl;
	DisplayAccount();

	//更新月报表
	ReadReport();
	for(i=0; i<rep_vec.size(); i++)
	{
		if(rep_vec.at(i).GetTargetYear() == y && rep_vec.at(i).GetTargetMonth() == m)
		{
			rep_vec.at(i).IsThisMonth(rec_vec,y,m);
			rep_vec.at(i).CountForMonth();
		}
	}
	cout << "月报表已更新" << endl;
	Day::day.clear();
	WriteReport();

	cout << "记录修改成功" << endl;
	WriteToFile();

}


double Interface::SetBudget()
{
	ifstream in;
	in.open("budget.txt",ios::in);
	if(!in)
	{
		cout << "文件打开失败" << endl;
	}
	else{
		in >> budget;
		in.close();
		cout << "原预算金额为:" << budget << "元" << endl;
		cout << "请输入新的预算金额(元):" << endl;
		cin >> budget;

		ofstream out;
		out.open("budget.txt",ios::out);
		if(!out)
		{
			cout << "文件打开失败" << endl;
		}else{
			out << budget;
			out.close();
			cout << "预算设置成功" << endl;
		}
	}
	return budget;
}
void Interface::Browse_Report()
{
	int y,m,find=1;

	ReadReport();

	cout << "请输入您要查询的报表所属日期:" << endl;
	cout << "年:" ;
	cin >> y;
	cout << "月:";
	cin >> m;

	for(int i=0; i<rep_vec.size(); i++)
	{
		if(rep_vec.at(i).GetTargetYear() == y && rep_vec.at(i).GetTargetMonth() == m)
		{
			find = 0;
			rep_vec.at(i).PrintThisMonth();
		}
	}
	if(find)
	{
		cout << "未找到所输日期的报表记录" << endl;
	}
}