#ifndef _MAIN_H_
#define _MAIN_H_
#define FILE_PATH "Diary.txt"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Diary{
private:
    string date;
    vector<string> entity;

public:
    Diary(string data0);
    string get_date();
	void add_line(string line);
	int get_size();
	string get_line(int index);
};

#endif