#include "stdafx.h"
#include "DATE.h"
#include "TASK.h"
#include "LIST.h"
#include "CHECK.h"

void AddDate(map<string, DATE*> &days)
{
	DATE *date = new DATE;
	cin >> date;
	if (days.count(date->get_ymd()) == 0)
		days.insert(pair<string, DATE*>(date->get_ymd(), date));
	else
	{
		cout << "День уже существует, задачи добавятся в этот день" << endl;
		TASK *Cur = new TASK;
		Cur = date->tasks->Head;
		while (Cur != nullptr)
		{
			date->tasks->Head = date->tasks->Head->Next;
			days[date->get_ymd()]->AddTskInD(Cur);
			Cur = date->tasks->Head;
		}
	}
}

void OutAllDays(map<string, DATE*> &days)
{
	for (auto it : days)
		cout << it.second;
}

void FindTask(map<string, DATE*> &days, vector <TASK*> &vtask)
{
	string name;
	cout << "Введите имя" << endl;
	cin >> name;
	cerr << name << endl;
	int i = 0;
	for (auto it : days)
	{
		i = vtask.size();
		it.second->Srch(name, vtask);
		for (int j = i; j < vtask.size(); j++)
		{
			cout << "----------\n";
			cout << "Дата: " << it.first << endl;
			cout << "----------\n";
			cout << vtask[j];
		}
	}
}

void ChangeDone(map<string, DATE*> &days)
{
	string date, info;
	int num, i;
	bool choose, change;
	cout << "Изменить статус через: указание даты и имени задачи - 1, поиск задачи - 0:\n";
	Check<bool>(choose, 0, 1);
	if (choose)
	{
		cout << "Введите дату (ГГГГ.ММ.ДД):\n";
		cin >> date;
		cerr << date << endl;
		if (days.count(date))
		{
			cout << "Введите имя" << endl;
			cin >> info;
			cerr << info << endl;
			if (days[date]->ChckNm(info))
			{
				cout << "Задача выполнена - 1, не выполнена - 0:\n";
				Check<bool>(change, 0, 1);
				days[date]->ListChange(info, change);
				cout << "Статус задачи изменён!\n";
			}
			else
				cout << "Такое название задачи не найдено в этом дне!!!";
		}
		else
			cout << "Такой день не найден в ежедневнике!!!";
	}
	else
	{
		vector <TASK*> vtask;
		FindTask(days, vtask);
		cout << "Изменить статус: одной или нескольких задач - 1, всех задач - 0:\n" ;
		Check<bool>(choose, 0, 1);
		if (choose)
			while (choose)
			{
				cout << "Введите номер задачи\n";
				Check(num, 1, (int)vtask.size());
				cout << "Задача выполнена - 1, не выполнена - 0:\n";
				Check<bool>(change, 0, 1);
				vtask[num - 1]->set_done(change);
				cout << "Статус задачи изменён!\n";
				cout << "Дальше - 1, выйти - 0:\n";
				Check<bool>(choose, 0, 1);
			}
		else
			for (i = 0; i < vtask.size(); i++)
			{
				cout << "Задача выполнена - 1, не выполнена - 0:\n";
				Check<bool>(change, 0, 1);
				vtask[i]->set_done(change);
				cout << "Статус задачи изменён!\n";
			}
		vtask.clear();
	}
}

void FileIn(map <string, DATE*> &days)
{
	ifstream fin;
	string file_name;
	int daysnum;
	cout << "Введите имя файла: ";
	cin.get();
	getline(cin, file_name);
	cerr << file_name << endl;
	fin.open(file_name);
	if (!fin.is_open())
		cout << "Ошибка, не могу загрузить!!!\n";
	else
	{
		fin >> daysnum;
		for (int i = 0; i < daysnum; i++)
		{
			DATE *date = new DATE;
			fin >> date;
			if (days.count(date->get_ymd()) == 0)
				days.insert(pair<string, DATE*>(date->get_ymd(), date));
		}
		cout << "Ежедневник успешно загружен!\n";
		fin.close();
	}
}

void FileOut(map <string, DATE*> &days)
{
	ofstream fout;
	string file_name;
	cout << "Введите имя файла: ";
	cin.get();
	getline(cin, file_name);
	cerr << file_name << endl;
	fout.open(file_name);
	if (!fout.is_open())
		cout << "Ошибка, не могу сохранить!!!\n\n";
	else
	{
		fout << days.size() << endl;
		for (auto it : days)
			fout << it.second;
		cout << "Ежедневник успешно сохранён!\n";
		fout.close();
	}
}

void DeleteDoneTasks(map <string, DATE*> &days)
{
	for (auto it : days)
		it.second->DelReady();
	cout << "Все выполненные задачи удалены" << endl;
}

void DeleteDay(map <string, DATE*> &days)
{
	string date;
	cout << "Введите дату" << endl;
	cin >> date;
	delete days[date];
	days.erase(date);
	cout << "День удалён\n";
}

void DeleteAll(map <string, DATE*> &days)
{
	for (auto it : days)
		delete it.second;
	days.clear();
}

void Error()
{
	cout << "Нет данных. Сначала надо считать их из файла или создать новый день!!!\n";
}

void Menu()
{
	cout << "\n--------------------------\n";
	cout << "1: Добавить день\n";
	cout << "2: Вывести задачи по дням\n";
	cout << "3: Поиск задачи\n";
	cout << "4: Изменить состояние задачи (выполнена/не выполнена)\n";
	cout << "5: Загрузить ежедневник\n";
	cout << "6: Сохранить ежедневник\n";
	cout << "7: Удалить выполненные задачи\n";
	cout << "8: Удалить день\n";
	cout << "9: Удалить ежедневник\n";
	cout << "0: Выйти из ежедневника\n";
	cout << "Сделайте выбор:\n";
	cout << "--------------------------\n\n";
}

int main()
{
	map <string, DATE*> days;
	setlocale(LC_ALL, "Russian");
	bool process = true;
	cout << "\n----- МОЙ ЕЖЕДНЕВНИК -----\n";
	while (process)
	{
		Menu();
		int action;
		cin >> action;
		switch (action)
		{
		case 1:
			AddDate(days);
			break;
		case 2:
			if (days.size())
				OutAllDays(days);
			else
				Error();
			break;
		case 3:
			if (days.size())
			{
				vector <TASK*> vtask;
				FindTask(days, vtask);
			}
			else
				Error();
			break;
		case 4:
			if (days.size())
				ChangeDone(days);
			else
				Error();
			break;
		case 5:
		{
			if (days.size())
				DeleteAll(days);
			FileIn(days);
		}
		break;
		case 6:
			if (days.size())
				FileOut(days);
			else
				Error();
			break;
		case 7:
			if (days.size())
				DeleteDoneTasks(days);
			else
				Error();
			break;
		case 8:
			if (days.size())
				DeleteDay(days);
			else
				Error();
			break;
		case 9:
			if (days.size())
			{
				DeleteAll(days);
				cout << "Ежедневник удалён\n";
			}
			else
				Error();
			break;
		case 0:
		{
			if (days.size())
				days.clear();
			return(0);
		}
		break;
		default:
			cout << "Нет такого пункта\n";
			break;
		}
	}
}