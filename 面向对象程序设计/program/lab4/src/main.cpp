#include "main.h"

Diary::Diary(string data0)			//construct function
{
	date = data0;
}

string Diary::get_date()
{
	return date;
}

void Diary::add_line(string line)	//Push each line in the journal into the entity
{
	entity.push_back(line);
}

int Diary::get_size()				//Get the number of rows in entity
{
    return entity.size();
}

string Diary::get_line(int index)	//Gets the contents of each row of entity
{
    return entity[index];
}