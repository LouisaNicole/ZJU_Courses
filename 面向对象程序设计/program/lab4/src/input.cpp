#include "main.h"
#include "input.h"
using namespace std;

extern vector<Diary*> Diaries;
void input(){
    ifstream in_file(FILE_PATH);            //Read file contents
    string date, entity;

    while(!in_file.eof()){
        getline(in_file, date);             //Read diary date
        getline(in_file, entity);           //Read diary entity
        Diary* diary = new Diary(date);
        while(entity != "."){               //Read the last line of a journal entry
            diary->add_line(entity);
            getline(in_file, entity);
        }
        Diaries.push_back(diary);           //Push this diary entry into a vector
    }
    in_file.close();
}