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
	cout<<"������������Ѽ�¼�����꣺"<<endl;
	cin>>year;

	cout<<"������������Ѽ�¼�����£�"<<endl;
	cin>>month;

	cout<<"������������Ѽ�¼�����գ�"<<endl;
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
	cout<<"��Ԫ"<<year<<"-"<<month<<"-"<<day<<endl;
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
	cout << "�������˻�����:";
	cin >> name;
}
void Account::SetNumber()
{
	cout << "��������˻��еĽ������:";
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
	cout<<"��ѡ������Ҫ�޸ĵ��ʽ��˻����ţ�"<<endl;
	cin>>n;
//	cout<<"�������"<<endl;
//	cin>>num;
	acc_vec.at(n).SetNumber();

	cout<<"�޸ĳɹ���������£�"<<endl;
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
	cout<<"��ѡ������Ҫ�޸ĵ��ʽ��˻����ţ�"<<endl;
	cin>>n;

	acc_vec.at(n).DeleteName();
	CountForAccount();
	cout<<"ɾ���ɹ�"<<endl;

}
void Bankroll::AddAccount()
{
	Account a;
	ReadAccount();

	a.SetName();
	a.SetNumber();

	acc_vec.push_back(a);
	CountForAccount();

	cout<<"��ӳɹ�"<<endl;
	DisplayAccount();
}
void Bankroll::DisplayAccount()//������ļ�
{
	ofstream out;
	out.open("account.txt");
	if( !out )
	{
		cout<<"�ļ���ʧ��"<<endl;
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
	cout<<"�˻��ʽ�������ˢ��"<<endl;

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
		cout<<"�ļ���ʧ��"<<endl;
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
	cout<<"�ܶ"<<total<<"Ԫ"<<endl;
	for(int i=0;i<acc_vec.size();i++)
	{
		cout<<i<<".";
		cout<<acc_vec.at(i).GetName()<<" ";
		cout<<acc_vec.at(i).GetNumber()<<"Ԫ"<<endl;
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
		cout << "��ѡ����Ŀ����:1.֧��2.����" << endl;
		cin >> choice1;
		
		if(choice1=='1')
		{
			InOrOut.assign("֧��");
			do{
				cout << "��ѡ��֧������:" << "\n" 
					<< "1.���� 2.���� 3.��ͨ 4.��ʳ 5.���� 6.ѧϰ 7.���� 8.Ͷ�� 9.����" << endl;
				cin >> choice2;
				switch(choice2)
				{
				case '1':
					TypeOut.assign("����");
					break;
				case '2':
					TypeOut.assign("����");
					break;
				case '3':
					TypeOut.assign("��ͨ");
					break;
				case '4':
					TypeOut.assign("��ʳ");
					break;
				case '5':
					TypeOut.assign("����");
					break;
				case '6':
					TypeOut.assign("ѧϰ");
					break;
				case '7':
					TypeOut.assign("����");
					break;
				case '8':
					TypeOut.assign("Ͷ��");
					break;
				case '9':
					TypeOut.assign("����");
					break;
				default:
					cout << "�������!" << endl;
				}
			}while(choice2<'1'||choice2>'9');
		}else if(choice1=='2')
		{
			InOrOut.assign("����");
			do{
				cout << "��������������:" << "\n"
					<< "1.���� 2.��� 3.Ͷ�� 4.�������� 5.����" << endl;
				cin >> choice2;
				switch(choice2)
				{
				case '1':
					TypeIn.assign("����");
					break;
				case '2':
					TypeIn.assign("���");
					break;
				case '3':
					TypeIn.assign("Ͷ��");
					break;
				case '4':
					TypeIn.assign("��������");
					break;
				case '5':
					TypeIn.assign("����");
					break;
				default:
					cout << "�������!" << endl;
				}
			}while(choice2<'1'||choice2>'5');
		}else{
			cout << "�������!" << endl;
		}
	}while(choice1<'1'||choice1>'2');
	cout << "��ѡ������ʽ�䶯���˻���:" << endl;
	acc_vec.clear();
	ReadAccount();
	PrintAccount();
	cin >> choice3;
	AccountName = acc_vec.at(choice3).GetName();
	cout << "��������(��λ:Ԫ):";
	cin >> money;
}
void Record::DisplayRecord(ofstream out)
{
	out << GetYear() << " " << GetMonth() << " " << GetDay() << setw(10) << InOrOut;
	if(InOrOut.compare("֧��") == 0)
	{
		out << setw(10) << TypeOut;
	}
	if(InOrOut.compare("����") == 0)
	{
		out << setw(10) << TypeIn;
	}
	out << setw(10) << money << setw(20) << AccountName << endl;
}
void Record::PrintRecord()
{
	cout << GetYear() << "-" << GetMonth() << "-" << GetDay() << setw(10) << InOrOut;
	if(InOrOut.compare("֧��") == 0)
	{
		cout << setw(10) << TypeOut;
	}
	if(InOrOut.compare("����") == 0)
	{
		cout << setw(10) << TypeIn;
	}
	cout << setw(10) << money << "Ԫ" << setw(20) << "�˻�:" << AccountName << endl;
}


//Day/////////////////////////////////////////////////
Day::Day()
{}
double Day::GetSurplusDay()
{
	return SurplusDay;
}
//////////////////////////////////////////////////////////////��////////////////////////////////////////////
void Day::IsToday(vector<Record>& rec_vec)
{
	int y,m,d;
	char today;
	//��ȡ��ǰ����	
	time_t t;
	tm * tp;
	t = time(NULL);
	tp = localtime(&t);
	y = tp->tm_year+1900;
	m = tp->tm_mon+1;
	d = tp->tm_mday;

	cout<<"�Ƿ�鿴���ռ�¼����Y/N��"<<endl;
	cin>>today;


	if(today == 'N')
	{
		cout<<"������Ҫ�鿴�����������꣺"<<endl;
		cin>>y;
		cout<<"������Ҫ�鿴�����������£�"<<endl;
		cin>>m;
		cout<<"������Ҫ�鿴�����������գ�"<<endl;
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
		 cout<<"û�и����ڵ���ؼ�¼"<<endl;
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
	//��ȡ��ǰ����	
	time_t t;
	tm * tp;
	t = time(NULL);
	tp = localtime(&t);
	y = tp->tm_year+1900;
	m = tp->tm_mon+1;
	d = tp->tm_mday;

	cout<<"�Ƿ�鿴���ռ�¼����Y/N��"<<endl;
	cin>>today;

	int find = 1;
	if(today == 'N')
	{
		cout<<"������Ҫ�鿴�����������꣺"<<endl;
		cin>>y;
		cout<<"������Ҫ�鿴�����������£�"<<endl;
		cin>>m;
		cout<<"������Ҫ�鿴�����������գ�"<<endl;
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
		cout << "δ�ҵ������ڵ����ݼ�¼" << endl;
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

		if(day.at(i).GetInOrOut().compare("����") == 0)
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
/////////////////////////////////////////////////////////////�޸�///////////////////////////////////////////////////////
/*void Day::DisplayDay()//������ļ�
{
	ofstream out;	
	out.open("day.txt",ios);
	if( !out )
	{
		cout<<"�ļ���ʧ��"<<endl;
	}

	out<<day.at(0).GetYear()<<" "<<day.at(0).GetMonth()<<" "<<day.at(0).GetDay();
	out<<SurplusDay<<" ";
	out<<day.at(i).GetAccountName()<<endl;

	out.close();

}*/
/////////////////////////////////////////////////////////////��/////////////////////////////////////////////////
void Day::PrintDay()//�������Ļ
{
	day.at(0).GetDate();//�������
	cout<<"��֧������£�"<<endl;
	cout<<endl;
	cout<<"�ս��ࣺ"<<SurplusDay<<endl;
	cout<<endl;

	cout<<"���飺"<<endl;
	for(int i = 0;i<day.size();i++)
	{
		cout << i <<"." ;
		//��������֧�����Լ������������������
		if(day.at(i).GetInOrOut().compare("����") == 0)
		{
			cout<<"���� "<<day.at(i).GetTypeIn();
		}
		else
		{
			cout<<"֧�� "<<day.at(i).GetTypeOut()<<" ";
		}

		cout<<day.at(i).GetMoney() << " ";//������
		cout<<day.at(i).GetAccountName();
		cout<<endl;
	}
		day.clear();
}
/*void Day::PrintDay()//�������Ļ
{
	day.at(0).GetDate();//�������
	cout << day.at(0).GetYear() << "-" << day.at(0).GetMonth() << "-" <<day.at(0).GetDay() << endl;
	cout<<"��֧������£�"<<endl;
	cout<<"�ս��ࣺ"<<SurplusDay<<endl;
	cout<<endl;

	cout<<"���飺"<<endl;
	for(int i = 0;i<day.size();i++)
	{
		cout <<i<<".";
		//��������֧�����Լ������������������
		if(day.at(i).GetInOrOut().compare("����") == 0)
		{
			cout<<"���� "<<day.at(i).GetTypeIn()<<" ";
		}
		else
		{
			cout<<"֧�� "<<day.at(i).GetTypeOut()<<" ";
		}

		cout<<day.at(i).GetMoney()<< " �˻�:" << day.at(i).GetAccountName()<<endl;//������
	}
}
void Day::ReadDay()
{
	ifstream in("day.txt");
	if( !in )
	{
		cout<<"�ļ���ʧ��!"<<endl;
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
		
		if(Month.at(i).GetInOrOut().compare("֧��")==0)
		{
			outcome += Month.at(i).GetMoney();
			if(Month.at(i).GetTypeOut().compare("����")==0)
			{
				EnteAll +=Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("����")==0)
			{
				ShopAll +=Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("��ͨ")==0)
			{
				TrafAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("��ʳ")==0)
			{
				FoodAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("����")==0)
			{
				HealAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("ѧϰ")==0)
			{
				StudAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("����")==0)
			{
				LifeAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("Ͷ��")==0)
			{
				InveAll +=Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeOut().compare("����")==0)
			{
				Else_outAll += Month.at(i).GetMoney();
			}
		}

		if(Month.at(i).GetInOrOut().compare("����")==0)
		{
			income += Month.at(i).GetMoney();
			if(Month.at(i).GetTypeIn().compare("����")==0)
			{
				WorkAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("���")==0)
			{
				GiftAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("Ͷ��")==0)
			{
				FinaAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("��������")==0)
			{
				WelfAll += Month.at(i).GetMoney();
			}
			if(Month.at(i).GetTypeIn().compare("����")==0)
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
///////////////////////////////////////////////////////////��///////////////////////////////////////////////
void Report::IsThisMonth(vector<Record> & All)
{
	char thisMon;
	Date now;

	cout << "�Ƿ�鿴���¼�¼?(Y/N)" << endl;
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
			cout << "������Ҫ�鿴������������:" << endl;
			cin >> TargetYear;
			cout << "������Ҫ�鿴������������:" << endl;
			cin >> TargetMonth;
			break;
		default:
			cout << "�������!" << endl;
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
////////////////////////////////////////////////////////////////��/////////////////////////////////////////////////////////////////
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
	cout << "����ӯ��:" << SurplusMonth << endl;

	cout << "֧��:" << outcome << endl;
	cout << setw(10) << "֧������" << setw(10) << "���" << setw(20) << "��ռ�ٷֱ�" << endl;
	cout << setw(10) << "����" << setw(10) << EnteAll << setw(20) << EntePer << "%" << endl;
	cout << setw(10) << "����" << setw(10) << ShopAll << setw(20) << ShopPer << "%" << endl;
	cout << setw(10) << "��ͨ" << setw(10) << TrafAll << setw(20) << TrafPer << "%" << endl;
	cout << setw(10) << "��ʳ" << setw(10) << FoodAll << setw(20) << FoodPer << "%" << endl;
	cout << setw(10) << "����" << setw(10) << HealAll << setw(20) << HealPer << "%" << endl;
	cout << setw(10) << "ѧϰ" << setw(10) << StudAll << setw(20) << StudPer << "%" << endl;
	cout << setw(10) << "����" << setw(10) << LifeAll << setw(20) << LifePer << "%" << endl;
	cout << setw(10) << "Ͷ��" << setw(10) << InveAll << setw(20) << InvePer << "%" << endl;
	cout << setw(10) << "����" << setw(10) << Else_outAll << setw(20) << Else_outPer << "%" << endl;

	cout << "����:" << income << endl;
	cout << setw(10) << "��������" << setw(10) << "���" << setw(20) << "��ռ�ٷֱ�" << endl;
	cout << setw(10) << "����" << setw(10) << WorkAll << setw(20) << WorkPer << "%" << endl;
	cout << setw(10) << "���" << setw(10) << GiftAll << setw(20) << GiftPer << "%" << endl;
	cout << setw(10) << "Ͷ��" << setw(10) << FinaAll << setw(20) << FinaPer << "%" << endl;
	cout << setw(10) << "��������" << setw(10) << WelfAll << setw(20) << WelfPer << "%" << endl;
	cout << setw(10) << "����" << setw(10) << Else_inAll << setw(20) << Else_inPer << "%" << endl;
}
void Report::ReadThisMonth(ifstream & in)//////////////////////////////////////////////�¼�//////////////////////////////////////////////
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