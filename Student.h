#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


class Student
{
private:
    string ID = "--";
    string major = "";
    double gpa;

public:
    Student() { }
    Student(string s, string m, double g )
    {
        setID(s);
        setMajor(m);
        setGPA(g);
    }
    string getID () { return ID; }
    void setID( string ID ) { this->ID = ID; }

    string getMajor() { return major; }
    void setMajor ( string major ) { this->major = major; }

    double getGPA() { return gpa; }
    void setGPA ( double gpa ) { this->gpa = gpa; }

    void displayID()
    {
        cout << left << setw(5) << ID;
    }

};

#endif

