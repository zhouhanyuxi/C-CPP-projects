#include"Interface.h"

Interface::Interface()
{}
int Interface::MainMenu()
{
	int option;
	cout<<"***************************************************"<<endl;
	cout<<"*          һ�����õļ��˳��� ��1.0.0��           *"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"*                    ���˵�                       *"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"*                  1.����                         *"<<endl;
	cout<<"*                  2.�鿴��֧���                 *"<<endl;
	cout<<"*                  3.�����ʽ��˻�                 *"<<endl;
	cout<<"*                  0.�˳�                         *"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"*                    ������                       *"<<endl;
	cout<<"*      �ܺ����                  ���麯           *"<<endl;
	cout<<"*      ��152��                 ��152��        *"<<endl;
	cout<<"*      8000115057                8000115056       *"<<endl;
	cout<<"*                                                 *"<<endl;
	cout<<"*                  2016.6.17                      *"<<endl;
	cout<<"***************************************************"<<endl;
	cout<<"����������ѡ��"<<endl;
	cin>>option;
	return option;
}

int Interface::RecordMenu()
{
	int option;
	cout<<"*********************************"<<endl;
	cout<<"*              ����             *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*          1.������֧��¼       *"<<endl;
	cout<<"*          2.ɾ����¼           *"<<endl;
	cout<<"*          3.�޸ļ�¼           *"<<endl;
	cout<<"*          4.����Ԥ��           *"<<endl;
	cout<<"*          0.�˳�               *"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<endl;
	cout<<"����������ѡ��";
	cin>>option;
	return option;
}

int Interface::ConsumeMenu()
{
	int option;
	cout<<"*********************************"<<endl;
	cout<<"*          ��֧�����ѯ         *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*        1.��ѯ����֧���       *"<<endl;
	cout<<"*        2.��ѯ����֧��������   *"<<endl;
	cout<<"*        0.�˳�                 *"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<endl;
	cout<<"����������ѡ��";
	cin>>option;
	return option;

}

int Interface::AccountMenu()
{
	int option;
	cout<<"*********************************"<<endl;
	cout<<"*          �ʽ��˻�����         *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*        1.����ʽ���Դ�˻�     *"<<endl;
	cout<<"*        2.ɾ���ʽ���Դ�˻�     *"<<endl;
	cout<<"*        3.�޸��ʽ���Դ�˻�     *"<<endl;
	cout<<"*        4.�鿴�ʽ���Դ�˻�     *"<<endl;
	cout<<"*        0.�˳�                 *"<<endl;
	cout<<"*                               *"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"����������ѡ��";
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
		cout<<"�ļ���ʧ��!"<<endl;
		return;
	}

	while(!in.eof())
	{
		in>>y>>m>>d>>i_or_o>>type>>mon>>acc;
		R.SetYear(y);
		R.SetMonth(m);
		R.SetDay(d);
		R.SetInOrOut(i_or_o);
		if(i_or_o.compare("����") == 0)
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
		cout<<"�ļ���ʧ��"<<endl;
		return;
	}

	for(int i = 0;i<rec_vec.size();i++)
	{
		if(rec_vec.at(i).GetFlag() == 1)
		{
			out<<rec_vec.at(i).GetYear()<<" "<<rec_vec.at(i).GetMonth()<<" "<<rec_vec.at(i).GetDay();
			out<<" "<<rec_vec.at(i).GetInOrOut()<<" ";

			if((rec_vec.at(i).GetInOrOut().compare("����") == 0))
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
	rec_vec.clear();//�����¼
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
				cout<<"����ϡ㣩�����ʽ��˻�ĿǰΪ��,��Ҫ������ʽ��˻����ܽ��д˲���Ŷ~"<<endl;
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
				cout<<"����ϡ㣩�����ʽ��˻�ĿǰΪ��,��Ҫ������ʽ��˻����ܽ��д˲���Ŷ~"<<endl;
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
				cout<<"����ϡ㣩�����ʽ��˻�ĿǰΪ��,��Ҫ������ʽ��˻����ܽ��д˲���Ŷ~"<<endl;
			}
			system("pause");
			system("cls");

			break;
		case 0:
			system("cls");
			break;
		default:
			cout<<"�������󣬽�������һ��(���n����"<<endl;
			system("pause");
			system("cls");
			break;


		}//switch

	}while(option);
}


void Interface::Browse_Day(vector<Record>& rec_vec)
{
	Day::day.clear();
	IsToday(rec_vec);//��ȡ��ָ�����ڵ����м�¼����day����
	if(!Day::day.empty())
	{
		CountForDay();
		PrintDay();
	}
	else
	{
		cout<<"������һ��"<<endl;
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
			cout<<"�������󣬽�������һ��(���n����"<<endl;
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
			cout<<"�������󣬽�������һ��(���n����"<<endl;
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
		cout << "�ļ���ʧ��!" << endl;
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
		cout << "�Ѷ�����±���" << endl;
		in.close();
	}
}

void Interface::WriteReport()
{
	ofstream out;
	out.open("report.txt",ios::trunc);
	if(!out)
	{
		cout << "�ļ���ʧ��!" << endl;
	}else{
		for(int i=0; i<rep_vec.size(); i++)
		{
			rep_vec.at(i).DisplayThisMonth(out);
		}
		cout << "�±����Ѵ����ļ���" << endl;
		out.close();
		rep_vec.clear();
	}
}


void Interface::AddRecord()
{
	Record temp1;
	char today;

	//����һ����¼
	cout << "�Ƿ񽫸�����֧��¼��������Ϊ����?(Y/N)" << endl;
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
	

	//ˢ�»������±���
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
	cout << "�±����Ѹ���" << endl;
	WriteReport();

	//ˢ���ʽ��˻�����
	ReadAccount();
	for(i=0; i<acc_vec.size(); i++)
	{
		if(temp1.GetAccountName().compare(acc_vec.at(i).GetName()) == 0)
		{
			if(temp1.GetInOrOut().compare("֧��") == 0)
			{
				acc_vec.at(i).SetNumber(acc_vec.at(i).GetNumber()-temp1.GetMoney());
			}
			if(temp1.GetInOrOut().compare("����") == 0)
			{
				acc_vec.at(i).SetNumber(acc_vec.at(i).GetNumber()+temp1.GetMoney());
			}
		}
	}
	cout << "�ʽ��˻������Ѹ���" << endl;
	DisplayAccount();

	WriteToFile();
}


void Interface::Record_Delete()
{
	int y,m,d,num,k;
	int find=1;

	ReadFromFile();

	cout << "�������¼��������:" << endl;
	cout << "��:";
	cin >> y;
	cout << "��:";
	cin >> m;
	cout << "��:";
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
		cout << "δ�ҵ������ڶ�Ӧ�����ݼ�¼" << endl;
		rec_vec.clear();
		return;
	}

	CountForDay();
	PrintDay();
	do{
		cout << "���������Ҫɾ���ļ�¼�����:" ;
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

	//��ԭ�ʽ��˻�����
	ReadAccount();
	for(int j=0; j<acc_vec.size(); j++)
	{
		if(rec_vec.at(k).GetAccountName().compare(acc_vec.at(j).GetName()) == 0)
		{
			if(rec_vec.at(k).GetInOrOut().compare("֧��") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()+rec_vec.at(k).GetMoney());
			}
			if(rec_vec.at(k).GetInOrOut().compare("����") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()-rec_vec.at(k).GetMoney());
			}
		}
	}
	DisplayAccount();

	//���ɾ��
	rec_vec.at(k).DeleteRecord();

	WriteToFile();
	cout << "��¼ɾ���ɹ�" << endl;

	//�����±���
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
	cout << "�±����Ѹ���" << endl;
	Day::day.clear();
	WriteReport();
	WriteToFile();
}


void Interface::Record_Change()
{
	int y,m,d,num,k;

	ReadFromFile();
	cout << "�������¼��������:" << endl;
	cout << "��:";
	cin >> y;
	cout << "��:";
	cin >> m;
	cout << "��:";
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
		cout << "δ�ҵ������ڶ�Ӧ�����ݼ�¼" << endl;
		rec_vec.clear();
		return;
	}

	CountForDay();
	PrintDay();
	do{
		cout << "���������Ҫ�޸ĵļ�¼�����:" ;
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

	//��ԭ�ʽ��˻�����
	ReadAccount();
	for(int j=0; j<acc_vec.size(); j++)
	{
		if(rec_vec.at(k).GetAccountName().compare(acc_vec.at(j).GetName()) == 0)
		{
			if(rec_vec.at(k).GetInOrOut().compare("֧��") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()+rec_vec.at(k).GetMoney());
			}
			if(rec_vec.at(k).GetInOrOut().compare("����") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()-rec_vec.at(k).GetMoney());
			}
		}
	}
	DisplayAccount();

	//�޸ļ�¼
	rec_vec.at(k).ChangeRecord();

	//ˢ���ʽ��˻�����
	ReadAccount();
	for(j=0; j<acc_vec.size(); j++)
	{
		if(rec_vec.at(k).GetAccountName().compare(acc_vec.at(j).GetName()) == 0)
		{
			if(rec_vec.at(k).GetInOrOut().compare("֧��") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()-rec_vec.at(k).GetMoney());
			}
			if(rec_vec.at(k).GetInOrOut().compare("����") == 0)
			{
				acc_vec.at(j).SetNumber(acc_vec.at(j).GetNumber()+rec_vec.at(k).GetMoney());
			}
		}
	}

	cout << "�ʽ��˻������Ѹ���" << endl;
	DisplayAccount();

	//�����±���
	ReadReport();
	for(i=0; i<rep_vec.size(); i++)
	{
		if(rep_vec.at(i).GetTargetYear() == y && rep_vec.at(i).GetTargetMonth() == m)
		{
			rep_vec.at(i).IsThisMonth(rec_vec,y,m);
			rep_vec.at(i).CountForMonth();
		}
	}
	cout << "�±����Ѹ���" << endl;
	Day::day.clear();
	WriteReport();

	cout << "��¼�޸ĳɹ�" << endl;
	WriteToFile();

}


double Interface::SetBudget()
{
	ifstream in;
	in.open("budget.txt",ios::in);
	if(!in)
	{
		cout << "�ļ���ʧ��" << endl;
	}
	else{
		in >> budget;
		in.close();
		cout << "ԭԤ����Ϊ:" << budget << "Ԫ" << endl;
		cout << "�������µ�Ԥ����(Ԫ):" << endl;
		cin >> budget;

		ofstream out;
		out.open("budget.txt",ios::out);
		if(!out)
		{
			cout << "�ļ���ʧ��" << endl;
		}else{
			out << budget;
			out.close();
			cout << "Ԥ�����óɹ�" << endl;
		}
	}
	return budget;
}
void Interface::Browse_Report()
{
	int y,m,find=1;

	ReadReport();

	cout << "��������Ҫ��ѯ�ı�����������:" << endl;
	cout << "��:" ;
	cin >> y;
	cout << "��:";
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
		cout << "δ�ҵ��������ڵı����¼" << endl;
	}
}