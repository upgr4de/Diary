#include "stdafx.h"
#include "LIST.h"
#include "CHECK.h"
#include "TASK.h"

LIST::LIST()
{

}

LIST::~LIST()
{
	
}

void LIST::AddTaskInDay(TASK *task)
{
	if (Head == nullptr)
	{
		Head = Tail = task;
		return;
	}

	if (task->get_time() < Head->get_time())
	{
		task->Next = Head;
		Head->Prev = task;
		Head = task;
		return;
	}

	if (task->get_time() > Tail->get_time()) 
	{
		task->Prev = Tail;
		Tail->Next = task;
		Tail = task;
		return;
	}

	TASK *Cur = Head;
	while (task->get_time() > Cur->get_time())
		Cur = Cur->Next;

	task->Next = Cur;
	task->Prev = Cur->Prev;
	Cur->Prev->Next = task;
	Cur->Prev = task;
}

void LIST::PrintTasksInDays(int k)
{
	TASK *Cur = Head;
	while (Cur != nullptr)
	{
		if ((k == 1) || (Cur->get_done() == (k == 2)))
			cout << Cur;
		Cur = Cur->Next;
	}
}

void LIST::Search(string taskinfo, vector <TASK*> &vtask) 
{
	TASK *Cur = Head;
	while (Cur != nullptr)
	{
		if (Cur->get_info() == taskinfo)
			vtask.push_back(Cur);
		Cur = Cur->Next;
	}
}

bool LIST::CheckName(string taskinfo)
{
	TASK *Cur = Head;
	while (Cur != nullptr)
	{
		if (Cur->get_info() == taskinfo)
			return 1;
		Cur = Cur->Next;
	}
	return 0;
}

void LIST::ListChangeDone(string taskinfo, bool taskchange)
{
	TASK *Cur = Head;
	while (Cur != nullptr)
	{
		if (Cur->get_info() == taskinfo)
			Cur->set_done(taskchange);
		Cur = Cur->Next;
	}
}

void LIST::PrintInFile(ofstream &fout)
{
	TASK *Cur = Head;
	while (Cur != nullptr)
	{
		fout << Cur;
		Cur = Cur->Next;
	}
}

void LIST::Delete(TASK *task) 
{
	if ((task == Head) && (task == Tail))
	{
		Head = nullptr;
		Tail = nullptr;
		delete task;
		return;
	}

	if (task == Tail)
	{
		Tail = task->Prev;
		Tail->Next = nullptr;
		delete task;
		return;
	}

	if (task == Head)
	{
		Head = task->Next;
		Head->Prev = nullptr;
		delete task;
		return;
	}

	task->Next->Prev = task->Prev;
	task->Prev->Next = task->Next;
	delete task;
}

void LIST::DeleteReady()
{
	TASK *Cur = Head;
	while (Cur != nullptr)
	{
		if (Cur->get_done())
		{
			Cur = Cur->Next;
			Delete(Cur->Prev);
		}
		else
			Cur = Cur->Next;
	}
}