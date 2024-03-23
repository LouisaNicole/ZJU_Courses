#include "main.h"
#include "input.h"
vector<Diary*> Diaries;
int main(int argc, char* argv[])
{
    input();

    int i, j;
    string begin, end;
    if(argc == 1){                                      //Only one parameter, all output
        for(i=0; i<Diaries.size(); i++){
            cout << Diaries[i]->get_date() << endl;     //Output diary date
            for(j=0; j<Diaries[i]->get_size(); j++){    //Output diary entity
                cout << Diaries[i]->get_line(j) << endl;
            }
        }
    }
    else if(argc == 3){                                 //Three parameters, choose to output
        begin = argv[1];
        end = argv[2];
        for(i=0; i<Diaries.size(); i++){                
            if(Diaries[i]->get_date() < begin) continue;
            if(Diaries[i]->get_date() > end) break;
            cout << Diaries[i]->get_date() << endl;     //Find the correct output date
            for(j=0; j<Diaries[i]->get_size(); j++){
                cout << Diaries[i]->get_line(j) << endl;
            }
        }
    }
    for(i=0; i<Diaries.size(); i++)
        delete Diaries[i];
    return 0;
}