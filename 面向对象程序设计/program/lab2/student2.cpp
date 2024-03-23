#include<iostream>      // Include input/output stream library
#include<iomanip>       // Include input/output formatting library
#include<string>        // Include string manipulation library
#include<vector>        // Include vector (dynamic array) library
using namespace std;    // Use the standard namespace

struct Course{
    string coursename;  // Course name
    int coursescore;    // Course score
};

class score {
    private:
        int number;     // Student ID
        string name;    // Student name
        vector<Course> courses;         // Course list       
        double average;                 // Average score

    public:
        void setnum(string s_name, int s_num);      // Set student ID and name
        void setgrade(string c_name, int c_score);  // Set course name and score
        void setaverage(int c_num, int c_sum);      // Calculate average score                
        void printgrade();                          // Print student's grades
        vector<Course> checkgrade();                // Get course list            
};

vector<string> listname;                            // List of all courses

void prints(const vector<score*> records);          // Print maximum, minimum, and average values

int main(){
    string name, course_name;
    int num = 1, i, flag = 0;                       // Flag is used to mark whether the course is newly added
    vector<score*> student;                         // Student list

    while(cin >> name){
        bool enter = false;                         // enter checks if a line (a student) is entered
        int course_num = 0, course_score, course_sum = 0;
        score *record = new score;
        record->setnum(name, num++);                // Set student ID and name
        while(!enter){
            cin >> course_name;
            cin >> course_score;
            if(cin.get()=='\n') enter = true;       // cin.get() checks if a student's grades are entered
            course_num++;
            course_sum += course_score;             // These two lines are used to calculate the student's average score
            record->setgrade(course_name, course_score);     // Record student's course grades
            
            for(i = 0, flag = 0; i < listname.size(); i++){
                if(course_name == listname[i]){
                    flag = 1;                       // The input course is in the total course list, no need to push later
                    break;
                }
            }
            if(!flag) 
                listname.push_back(course_name);    // Push a new course to the total course list
        }
        record->setaverage(course_num, course_sum);
        student.push_back(record);                  // Push a new student to the student list
    }

    // Print table header
    cout << "no\t" << "name\t";
    for(int i = 0; i < listname.size(); i++)
        cout << listname[i] << "\t";
    cout << "average\t" << endl;

    // Print each student's grades
    for(i = 0; i < student.size(); i++){
        student[i]->printgrade();
    }
    
    // Print maximum, minimum, and average values
    prints(student);

    return 0;

}

void score::setnum(string s_name, int s_num){       // Set student ID and name
    name = s_name;
    number = s_num;
}

void score::setgrade(string c_name, int c_score){   // Set course name and score
    Course co;
    co.coursename = c_name;
    co.coursescore = c_score;
    courses.push_back(co);
}

void score::setaverage(int c_num, int c_sum){       // Calculate average score
    if(c_num) average = 1.0 * c_sum / c_num;
    else average = 0;
}

void score::printgrade(){                           // Print student's grades
    int i, j, flag;
    cout << number << "\t" << name << "\t";
    for(i = 0; i < listname.size(); i++){
        for(j = 0, flag = 0; j < courses.size(); j++){  
            if(courses[j].coursename == listname[i]){    // Compare total course list with student's read courses
                cout << courses[j].coursescore << "\t";  
                flag = 1;                            // Student has read this course
                break;
            }
        }
        if(!flag) cout << "\t";                      // Cannot find the next course, i.e., the student's output is complete
    }
    cout << average << endl;
}

vector<Course> score::checkgrade(){                  // Get course list 
    return courses;
}

void prints(const vector<score*> records){
    vector<Course> co;                               // define course lists
    int i, j, k, co_max, co_sum, co_min,co_num;      // define courses'max¡¢min¡¢sum¡¢num
    int max[listname.size()], min[listname.size()];  // define array max and min
    double aver[listname.size()];                    // define array average

    for(i = 0; i < listname.size(); i++){            // Iterate through the total course list
        co_max = 0, co_sum = 0, co_min = 5, co_num = 0;  // Initialize course maximum, sum, minimum, and number

        for(j = 0; j < records.size(); j++){             // Iterate through the student list
            co = records[j]->checkgrade();               // Get the course list of student j
            for(k = 0; k < co.size(); k++){              // Iterate through the course list of student j
                if(listname[i] == co[k].coursename){     // Student j has course i
                    if(co[k].coursescore > co_max) co_max = co[k].coursescore;  // Update course maximum
                    if(co[k].coursescore < co_min) co_min = co[k].coursescore;  // Update course minimum
                    co_sum += co[k].coursescore;         // Update course sum
                    co_num++;                            // Increase course number
                    break;                               // Exit the inner loop and continue with the next student's courses
                }
            }
        }
        max[i] = co_max;                  // Store the course maximum in the maximum value array
        min[i] = co_min;                  // Store the course minimum in the minimum value array
        aver[i] = 1.0 * co_sum / co_num;  // Calculate the average value and store it in the average value array
    }

    // Print averages
    cout << "\t";
    cout << "average\t";
    for(i = 0; i < listname.size(); i++){
        cout << aver[i] << "\t";
    }
    cout << endl;

    // Print minimum values
    cout << "\t";
    cout << "min\t";
    for(i = 0; i < listname.size(); i++){
        cout << min[i] << "\t";
    }
    cout << endl;

    // Print maximum values
    cout << "\t";
    cout << "max\t";
    for(i = 0; i < listname.size(); i++){
        cout << max[i] << "\t";
    }
    cout << endl;
    
}