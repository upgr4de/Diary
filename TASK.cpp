#include "stdafx.h"
#include "TASK.h"
#include "CHECK.h"

TASK::TASK()
{

}

TASK::~TASK()
{

}

string FormatTime1(int time)
{
	ostringstream ost;
	ost << time / 100 << "-" << time % 100 << endl;
	return ost.str();
}

string FormatTime2(int time)
{
	ostringstream ost;
	ost << time / 100 << "� " << time % 100 << "�" << endl;
	return ost.str();
}

string FormatTime3(int time)
{
	ostringstream ost;
	ost << time / 100 << ":" << time % 100 << endl;
	return ost.str();
}

istream &operator>>(istream &in, TASK *&task)
{
	ostringstream oss;
	int hour, min;
	string stime;
	cout << "������� ��������: ";
	cin.get();
	getline(cin, task->info);
	cerr << task->info << endl;
	cout << "������� ����: ";
	Check(hour, 0, 23);
	cout << "������� ������: ";
	Check(min, 0, 59);
	oss << hour << min;
	stime = oss.str();
	task->time = atoi(stime.c_str());
	cout << "�������� ��������� (�� 1 �� 3): ";
	Check(task->important, 1, 3);
	task->done = false;
	return in;
}

ostream &operator<<(ostream &out, TASK *&task)
{
	typedef string(*DoFormat)(int);
	DoFormat FormatsTime[3] = { FormatTime1, FormatTime2, FormatTime3 };
	cout << "----------\n";
	cout << "��������: " << task->info << endl;
	cout << "����� ������: " << FormatsTime[format - 1](task->time);
	cout << "���������: " << task->important << endl;
	cout << "������: ";
	if (!task->done)
		cout << "������ �� ���������\n";
	else
		cout << "������ ���������\n";
	cout << "----------\n";
	return out;
}

ifstream &operator>>(ifstream &fin, TASK *&task)
{
	fin >> task->info;
	fin >> task->time;
	fin >> task->done;
	fin >> task->important;
	return fin;
}

ofstream &operator<<(ofstream &fout, TASK *&task)
{
	fout << task->info << endl;
	fout << task->time << endl;
	fout << task->done << endl;
	fout << task->important << endl;
	return fout;
}