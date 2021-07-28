#include "stdafx.h"
#include "DATE.h"
#include "TASK.h"
#include "CHECK.h"
#include "LIST.h"

int format;

DATE::DATE()
{

}

DATE::~DATE()
{

}

istream &operator>>(istream &in, DATE *&date)
{
	ostringstream ost;
	int year, month, day;
	cout << "����: " << endl;
	cout << "������� ��� (2018-2030): ";
	Check(year, 2000, 2030);
	cout << "������� �����: ";
	Check(month, 1, 12);
	cout << "������� ����: ";
	Check(day, 1, 31);
	ost << year << "." << month << "." << day;
	date->ymd = ost.str();
	cout << "������� �������� �����?: ";
	Check(date->tasksnum, 1, 15);
	for (int i = 0; i < date->tasksnum; i++)
	{
		TASK *task = new TASK;
		cout << "������ � " << i + 1 << endl;
		cin >> task;
		date->tasks->AddTaskInDay(task);
	}
	return in;
}

ostream &operator<<(ostream &out, DATE *&date)
{
	int k;
	TASK *task = new TASK;
	cout << "1: ������� ��� ������\n";
	cout << "2: ������ �����������\n";
	cout << "3: ������ �������������\n";
	Check(k, 1, 3);
	cout << "�������� ������ �������: " << endl;
	cout << "1: 00-00" << endl;
	cout << "2: 00� 00�" << endl;
	cout << "3: 00:00" << endl;
	Check(format, 1, 3);
	cout << "----------\n";
	cout << "����: " << date->ymd << endl;
	cout << "----------\n";
	date->tasks->PrintTasksInDays(k);
	return out;
}

ifstream &operator>>(ifstream &fin, DATE *&date)
{
	fin >> date->tasksnum;
	fin >> date->ymd;
	for (int i = 0; i < date->tasksnum; i++)
	{
		TASK *task = new TASK;
		fin >> task;
		date->tasks->AddTaskInDay(task);
	}
	return fin;
}

ofstream &operator<<(ofstream &fout, DATE *&date)
{
	fout << date->tasksnum << endl;
	fout << date->ymd << endl;
	date->tasks->PrintInFile(fout);
	return fout;
}

void DATE::DelReady()
{
	tasks->DeleteReady();
}

void DATE::ListChange(string info, bool change)
{
	tasks->ListChangeDone(info, change);
}

bool DATE::ChckNm(string info)
{
	return tasks->CheckName(info);
}

void DATE::Srch(string name, vector <TASK*> &vtask)
{
	tasks->Search(name, vtask);
}

void DATE::AddTskInD(TASK *Cur)
{
	tasks->AddTaskInDay(Cur);
}