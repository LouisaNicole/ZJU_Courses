#include "main.h"
#include "input.h"
#include "output.h"
vector<Diary*> Diaries;
int main(int argc, char* argv[])
{
    // vector<Diary*> Diaries;
    input();

    string date;
    if(argc == 2){
        int i, j;
        date = argv[1];                 //The parameter is correct for the date to be deleted
        for(i=0; i<Diaries.size(); i++){
            if(date == Diaries[i]->get_date()) break;
        }
        if(i == Diaries.size()){        //No date found, return -1 failed
            cout << "-1" << endl;
            return 0;
        }
        else{                           //Find and delete
            Diaries.erase(Diaries.begin()+i);
            output();
            cout << "0" << endl;
        }
    }
    else cout << "-1" << endl;
    return 0;
}