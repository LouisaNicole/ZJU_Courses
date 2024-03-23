#include "main.h"
#include "input.h"
vector<Diary*> Diaries;
int main(int argc, char* argv[])
{
    input();

    int i, j;
    string date = argv[1];
    while(date != Diaries[i]->get_date()){      //Find the correct date to show
        i++;
    }
    for(j=0; j<Diaries[i]->get_size(); j++){    //Show all lines
        cout << Diaries[i]->get_line(j) << endl;
    }
    return 0;
}