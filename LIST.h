#pragma once

#include"TASK.h"
#include "stdafx.h"

class LIST
{
public:
	LIST();
	~LIST();

	TASK *Head = nullptr;
	TASK *Tail = nullptr;

	void AddTaskInDay(TASK *task);
	void PrintTasksInDays(int k);
	void Search(string taskinfo, vector<TASK*> &vtask);
	bool CheckName(string taskinfo);
	void ListChangeDone(string taskinfo, bool taskchange);
	void PrintInFile(ofstream &fout);
	void DeleteReady();
	void Delete(TASK *task);
};