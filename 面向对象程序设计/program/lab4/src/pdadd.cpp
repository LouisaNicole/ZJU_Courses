#include "main.h"
#include "input.h"
#include "output.h"
vector<Diary*> Diaries;
int main(int argc, char* argv[])
{
    // vector<Diary*> Diaries;
    input();

    string date = argv[1], entity;
    Diary* diary = new Diary(date);
    cout << "Please input your content:" << endl;
    getline(cin, entity);                           //Enter the entity of a journal entry
    while(entity != "."){                           //Enter all the way to the last line
        diary->add_line(entity);
        getline(cin, entity);
    }
    int i=0, j;
    //Go through the sequence to get the position that should be inserted
    while(i<Diaries.size() && Diaries[i]->get_date() < diary->get_date()) 
        i++;
    if(i == Diaries.size())                         //Insert to the end
        Diaries.push_back(diary);
    else if(Diaries[i]->get_date() == diary->get_date()) 
        Diaries[i] = diary;                         //Overwrite existing date
    else  
        Diaries.insert(Diaries.begin()+i, diary);

    output();

    for(i = 0; i < Diaries.size(); i++)
        delete Diaries[i];                          // delete diary;
    return 0;
}