#include "main.h"
#include "output.h"
using namespace std;

extern vector<Diary*> Diaries;
void output(){
    int i, j;
    ofstream out_file(FILE_PATH);                       //Write file contents
    for(i=0; i<Diaries.size()-1; i++){
        out_file << Diaries[i]->get_date() << endl;     //Write diary date
        for(j=0; j<Diaries[i]->get_size(); j++){        //Write diary entity
            out_file << Diaries[i]->get_line(j) << endl;
        }
        out_file << "." << endl;
    }
    //Used to distinguish the contents of the diary without a return key in the last
    out_file << Diaries[i]->get_date() << endl;
    for(j=0; j<Diaries[i]->get_size(); j++){
        out_file << Diaries[i]->get_line(j) << endl;
    }
    out_file << ".";

    out_file.close();
}
