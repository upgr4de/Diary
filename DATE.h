#pragma once

#include"LIST.h"
#include "stdafx.h"

class DATE
{
public:
	DATE();
	~DATE();

	void DelReady();
	void ListChange(string info, bool change);
	bool ChckNm(string info);
	void Srch(string name, vector<TASK*>& vtask);
	void AddTskInD(TASK *Cur);

	void set_tasksnum(int tasksnum) { this->tasksnum = tasksnum; }
	int get_tasksnum() { return tasksnum; }
	void set_ymd(string ymd) { this->ymd = ymd; }
	string get_ymd() { return ymd; }

	LIST *tasks = new LIST;

	friend istream &operator>>(istream &in, DATE *&date);
	friend ostream &operator<<(ostream &out, DATE *&date);
	friend ifstream &operator>>(ifstream &fin, DATE *&date);
	friend ofstream &operator<<(ofstream &fout, DATE *&date);

private:
	int tasksnum;
	string ymd;
};