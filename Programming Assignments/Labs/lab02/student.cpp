/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Liam Brew
 * Version : 1.0
 * Date    : January 31, 2020
 * Description : Class that handles basic operations relating to a typical student.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {
   public:
    // Constructor
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}

    // Accessor for student's name.
    string full_name() const {
        return first_ + " "  + last_;
    }

    // Accessor for student's id.
    int id() const {
        return id_;
    }

    // Accessor for student's GPA.
    float gpa() const {
        return gpa_;
    }

    // Prints the student's full name, GPA and ID in the required format.
    void print_info() const {
        cout << full_name() << ", GPA: " << fixed << setprecision(2) << gpa() << ", ID: " << id() << endl;
    }

   private:
    string first_, last_;
    float gpa_;
    int id_;
};

/**
* Takes a vector of Student objects, and returns a new vector
* with all Students whose GPA is < 1.0.
*/
vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;

    // Iterates through the students vector, appending each student whose gpa is
    for (auto st = students.cbegin(); st != students.cend(); ++st) {
        // less than 1.0 to the failing_students vector.
        if (st->gpa() < 1.0) {
            failing_students.push_back(*st);
        }
    }

    return failing_students;
}

/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
    // Iterates through the students vector, calling print_info() for each student.
    for (auto st = students.cbegin(); st != students.cend(); ++st) {
        st->print_info();
    }
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen.
*/
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    cout << endl
         << "All students:" << endl;

    print_students(students);

    vector<Student> failingStudents = find_failing_students(students);
    cout << endl
         << "Failing students:";
        if(failingStudents.empty()){
            cout << " None";
        }
        else{
            cout << endl;
            print_students(failingStudents);
        }

    return 0;
}