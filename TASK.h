#pragma once

#include "stdafx.h"

extern int format;

class TASK
{
public:
	TASK();
	~TASK();

	void set_info(string info) { this->info = info; }
	string get_info() { return info; }
	void set_done(bool done) { this->done = done; }
	bool get_done() { return done; }
	void set_time(int time) { this->time = time; }
	int get_time() { return time; }
	void set_important(int important) { this->important = important; }
	int get_important() { return important; }
	
	TASK *Next = nullptr;
	TASK *Prev = nullptr;

	friend istream &operator>>(istream &in, TASK *&task);
	friend ostream &operator<<(ostream &out, TASK *&task);
	friend ifstream &operator>>(ifstream &fin, TASK *&task);
	friend ofstream &operator<<(ofstream &fout, TASK *&task);

private:
	string info;
	bool done;
	int time, important;
};