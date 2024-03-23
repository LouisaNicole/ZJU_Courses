#include<iostream>   // Include the input/output stream library
#include<iomanip>    // Include the input/output manipulation library
#include<string>     // Include the string library
using namespace std; // Use the standard namespace

#define student 10   
#define course 3     

// Structure to store student scores
struct score {
    int number; 
    string name; 
    int scores[course];             // Array to store scores for each course
    double average;                 // Average score
};

typedef struct score* gradescore;   // Define a pointer type to the score structure as "gradescore"
gradescore readgrade();             // Function to read student grades

void dograde(gradescore grade, double gradeaverage[], int grademin[], int grademax[]);
                                    // Function to calculate statistics
void printgrade(gradescore grade, double gradeaverage[], int grademin[], int grademax[]);
                                    // Function to print student grades
int main() {
    double gradeaverage[course];    // Array to store average scores
    int grademin[course];           // Array to store minimum scores
    int grademax[course];           // Array to store maximum scores
    gradescore grade = readgrade(); // Read the student grades and assign the result to "grade"
    dograde(grade, gradeaverage, grademin, grademax); 
    printgrade(grade, gradeaverage, grademin, grademax); 
}


gradescore readgrade() {
    int i, j, sum = 0; 
    gradescore grade = new score[student]; // Allocate memory for "student" number of score structures
    for (i = 0; i < student; i++) { 
        cin >> grade[i].name; 
        grade[i].number = i + 1;           // Assign the student's number
        for (j = 0; j < course; j++) { 
            cin >> grade[i].scores[j];     // Read the student's score for the current course
            sum += grade[i].scores[j]; 
        }
        grade[i].average = (double)sum / course;    // Calculate the average score for the student
        sum = 0;                                    // Reset the sum for the next student
    }
    return grade;                          // Return the pointer to the array of score structures
}

void dograde(gradescore grade, double gradeaverage[], int grademin[], int grademax[]) {
    int i, j, sum = 0; 
    int min = 5, max = 0; 
    for (i = 0; i < course; i++) { 
        for (j = 0; j < student; j++) { 
            sum += grade[j].scores[i];                              // Add the score to the sum
            if (grade[j].scores[i] > max) max = grade[j].scores[i]; // Update the maximum score if necessary
            if (grade[j].scores[i] < min) min = grade[j].scores[i]; // Update the minimum score if necessary
        }
        gradeaverage[i] = (double)sum / student;    // Calculate the average score for each course
        grademin[i] = min;                          // Assign the minimum score for the course
        grademax[i] = max;                          // Assign the maximum score for the course
        max = sum = 0;                              // Reset the maximum and sum for the next course
        min = 5;                                    // Reset the minimum for the next course
    }
}

void printgrade(gradescore grade, double gradeaverage[], int grademin[], int grademax[]) {
    int i, j; 
    cout << "no\t" << "name\t" << "score1\t" << "score2\t" << "score3\t" << "average\t" << endl; // Print the column headers
    for (i = 0; i < student; i++) { 	// Loop through each student
        cout << grade[i].number << "\t"; 	// Print the student's number
        cout << grade[i].name << "\t"; 		// Print the student's name
        for (j = 0; j < course; j++) { 		// Loop through each course
            cout << grade[i].scores[j] << "\t"; 	// Print the student's score for the current course
        }
        cout << grade[i].average << "\t"; 	// Print the student's average score
        cout << endl; 		// Move to the next line
    }
    // Print average
    cout << "\t";
    cout << "average\t";
    for (j = 0; j < course; j++) { 		// Loop through each course
        cout << gradeaverage[j] << "\t"; 	// Print the average score for the current course
    }
    cout << endl; 	// Move to the next line

    // Print min
    cout << "\t";
    cout << "min\t";
    for (j = 0; j < course; j++) { 		// Loop through each course
        cout << grademin[j] << "\t"; 	// Print the minimum score for the current course
    }
    cout << endl; 	// Move to the next line

    // Print max
    cout << "\t";
    cout << "max\t";
    for (j = 0; j < course; j++) { 		// Loop through each course
        cout << grademax[j] << "\t"; 	// Print the maximum score for the current course
    }
    cout << endl; 	// Move to the next line
}
