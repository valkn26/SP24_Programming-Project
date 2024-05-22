#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include "Student.h"
#include "Team.h"
using namespace std;

const int ROWS = 10;
const int COLS = 12;

void displaySeating(Student [][COLS], int);
int stringToIndex(string);
string indexToString(int);
void groupMajors (Student [][COLS], int, vector <Student>, int, int);

int main()
{
    Student seatingChart[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            seatingChart[i][j] = Student("--", "", 0.0);
        }
    }

    vector <Student> majorVectorList[3];
    Student clearObject("--", "", 0.0);
    vector <Student * > sPtrVectorList[3];
    Student spStudent("SP", "", 0.0);

    string ID, major;
    double GPA;
    int minCols = 0;
    int maxCols = 3;

    string facultyName;
    string projectID;
    int numofStudents;
    int majorSelection;
    int studentSelection;

    string newFacultyName;
    string newProjectID;
    string removeID;

    int majorTally[3] = {0};

    ifstream infile ("studentData.txt");

    cout << "============================Task 1============================" << endl;
    cout << "The original Random Seating Map: " << endl;

    while (infile >> ID >> major >> GPA)
    {
        Student newStudent(ID, major, GPA);

        unsigned seed = time(0);
        srand(seed);

        int index, randROWS, randCOLS;

        do
        {
            index = (rand() % (ROWS * COLS));
            randROWS = index / 10;
            randCOLS = index % 12;

        } while (seatingChart[randROWS][randCOLS].getID() != "--");

        seatingChart[randROWS][randCOLS] = newStudent;

    }

    displaySeating(seatingChart, ROWS);

    //Task 2
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {

            if (stringToIndex(seatingChart[i][j].getMajor()) == 0)
            {
                majorVectorList[0].push_back(seatingChart[i][j]);
            }
            else if (stringToIndex(seatingChart[i][j].getMajor()) == 1)
            {
                majorVectorList[1].push_back(seatingChart[i][j]);
            }
            else if (stringToIndex(seatingChart[i][j].getMajor()) == 2)
            {
                majorVectorList[2].push_back(seatingChart[i][j]);
            }

        }
    }



    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            seatingChart[i][j] = clearObject;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        groupMajors(seatingChart, ROWS, majorVectorList[i], minCols, maxCols);

        minCols += 4;
        maxCols += 4;
    }

    cout << "============================Task 2============================" << endl;
    cout << "The reconfigured Seating Map: " << endl;

    displaySeating(seatingChart, ROWS);

    //Task 3
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (seatingChart[i][j].getMajor() == "COSC")
            {
                sPtrVectorList[0].push_back(&seatingChart[i][j]);
            }
            else if (seatingChart[i][j].getMajor() == "MATH")
            {
                sPtrVectorList[1].push_back(&seatingChart[i][j]);
            }
            else if (seatingChart[i][j].getMajor() == "BIOL")
            {
                sPtrVectorList[2].push_back(&seatingChart[i][j]);
            }
        }
    }

    //Task 4
    cout << "Registering your project..." << endl;
    cout << endl;
    cout << "Please enter the faculty's full name: ";
    getline(cin, facultyName);

    cout << "Greetings Dr. " << facultyName << endl;

    cout << "Please enter the name/ID of your project: ";
    getline(cin, projectID);

    cout << "How many students are you considering for the " << projectID << "?: ";
    cin >> numofStudents;

    Team sciTeam(projectID, facultyName, numofStudents);

    for (int i = 0; i < sciTeam.getTeamSize(); i++)
    {
        majorSelection = (rand() % (3));
        studentSelection = (rand() % sPtrVectorList[majorSelection].size());

        bool notSPFound = false;

        do {
            studentSelection = (rand() % sPtrVectorList[majorSelection].size());

            if (sPtrVectorList[majorSelection][studentSelection]->getID() != "SP")
            {
                Student * getStudent = sPtrVectorList[majorSelection][studentSelection];

                sciTeam.addMember(*getStudent);

                *getStudent = spStudent;

                notSPFound = true;
            }

        } while (!notSPFound);
    }

    cout << "Initializing your team..." << endl;
    cout << endl;
    cout << "============================Task 4============================" << endl;
    displaySeating(seatingChart, ROWS);

    sciTeam.displayMembersIDs();

    //Task 5
    for (int i = 0; i < sciTeam.getTeamSize(); i++)
    {
        Student * teamMembers = sciTeam.getMembers();

        int majorIndex = stringToIndex(teamMembers[i].getMajor());
        majorTally[majorIndex]++;
    }

    cout << "============================Task 5============================" << endl;
    cout << "The major tally of the team members: " << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << indexToString(i) << setw(5) << ": " << majorTally[i] << endl;
    }

    //Task 6
    Team socialSciTeam(sciTeam);

    cout << "Please enter your full name: ";
    cin.ignore();
    getline(cin, newFacultyName);

    cout << "Please enter the name of your project: ";
    getline(cin, newProjectID);

    socialSciTeam.setFaculty(newFacultyName);
    socialSciTeam.setTeamID(newProjectID);

    cout << "============================Task 6============================" << endl;
    cout << "The information about the new team: " << endl;
    cout << endl;
    socialSciTeam.displayTeamInfo();
    cout << endl;
    socialSciTeam.displayMembersIDs();

    cout << endl;


    //Task 7
    cout << "============================Task 7============================" << endl;
    cout << "We have recieved your request for removing a student from your project team...";
    cout << endl;
    cout << "Please choose the ID of the student to be removed from the following list: " << endl;
    sciTeam.displayMembersIDs();
    cout << endl;
    cout << "Enter the ID: ";
    cin >> removeID;

    Student removeStudent = sciTeam.getTheMember(removeID);
    int majorIndex = stringToIndex(removeStudent.getMajor());

    int removeIndex = 0;

    for (int i = 0; i < majorVectorList[majorIndex].size(); i++)
    {
        if (removeStudent.getID() == majorVectorList[majorIndex][i].getID())
        {
            removeIndex = i;
            break;
        }
    }

    Student * originalSeating = sPtrVectorList[majorIndex][removeIndex];

    *originalSeating = majorVectorList[majorIndex][removeIndex];
    cout << endl;

    displaySeating(seatingChart, ROWS);

    int removedIndex = -1;

    for (int i = 0; i < sciTeam.getTeamSize(); i++)
    {
        if (sciTeam.getMembers()[i].getID() == "--")
        {
            removedIndex = i;
            break;
        }
    }

    sciTeam.removeMember(removeID);

    Student temp;

    for (int i = removedIndex; i < sciTeam.getTeamSize(); i++)
    {
        if (sciTeam.getMembers()[i].getID() == "--")
        {
            temp = sciTeam.getMembers()[i];
            sciTeam.getMembers()[i] = sciTeam.getMembers()[i + 1];
            sciTeam.getMembers()[i + 1] = temp;
        }
    }
    
    sciTeam.displayTeamInfo();
    cout << endl;


    cout << "============================Task 8============================" << endl;
    cout << "The number of Team objects: " << sciTeam.getTeamCount() << endl;


    cout << "============================BONUS TASK============================" << endl;
    cout << "The list of GPAs for members of the Social Science Project: " << endl;

    for (int i = 0; i < socialSciTeam.getCurrentSize(); i++)
    {
        cout << socialSciTeam.getMembers()[i].getGPA() << ", ";
    }
    cout << endl;

    const int NUM_GPA = 80;
    int gpaTally[NUM_GPA] = {0};

    for (int i = 0; i < socialSciTeam.getCurrentSize(); i++)
    {
        double GPA = socialSciTeam.getMembers()[i].getGPA();

        int gpaIndex = static_cast<int>(GPA * 10);

        gpaTally[gpaIndex]++;
    }

    cout << endl;
    cout << "The GPA Tally report: " << endl;

    for (int i = 0; i < NUM_GPA; i++)
    {
        double gpaCount = static_cast<double>(i) / 10;
        if (gpaTally[i] > 0)
        {
            cout << gpaCount << ": " << gpaTally[i] << endl;
        }
    }


    return 0;
}

void displaySeating(Student seatingChart [][COLS], int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << setw(5) << seatingChart[i][j].getID() << setw(5);
        }
        cout << endl;
    }
}

int stringToIndex(string majorsReturn)
{
    int index = -1;

    if (majorsReturn == "COSC")
    {
        index = 0;
    }
    if (majorsReturn == "MATH")
    {
        index = 1;
    }
    if (majorsReturn == "BIOL")
    {
        index = 2;
    }

    return index;
}

string indexToString (int index)
{
    string majorName;

    switch (index) {
        case 0:
            majorName = "COSC";
            break;
        case 1:
            majorName = "MATH";
            break;
        case 2:
            majorName = "BIOL";
            break;
    }
    return majorName;
}

void groupMajors (Student seatingChart[][COLS], int rows, vector <Student> majorVectorList, int minCols, int maxCols)
{
    int vecIndex = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = minCols; j <= maxCols; j++)
        {
            if (vecIndex < majorVectorList.size())
            {
                seatingChart[i][j] = majorVectorList[vecIndex++];
            }
        }
    }
}