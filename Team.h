#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

class Team
{
private:
    string teamID;
    string faculty;
    Student * members = nullptr;
    int currentSize = 0;  //Keeps track of current size of the team as students are added
    int teamSize;         //The ultimate size of the team determined by the user/faculty
    static int teamCount;

    Student * findMember(string ID)
    {
        Student * studentPtr = nullptr;

        for (int i = 0; i < teamSize; i++)
        {
            if (members[i].getID() == ID)
            {
                studentPtr = &members[i];
            }
        }

        return studentPtr;
    }//A private function to be called internally by removeMember function

public:
    Team (string teamID, string faculty, int teamSize)
    {
        this->teamID = teamID; //Shadowing Problem, fixed by this point
        this->faculty = faculty;
        this->teamSize = teamSize;

        members = new Student[teamSize];

        teamCount++;
    } //Updates the count of Team objects

    Team(const Team & anotherTeam)
    {
        teamID = anotherTeam.teamID;
        faculty = anotherTeam.faculty;
        teamSize = anotherTeam.teamSize;

        members = new Student[teamSize];

        for (int i = 0; i < teamSize; i++)
        {
            members[i] = anotherTeam.members[i];
            currentSize++;
        }

        teamCount++;
    }   //Define the copy constructor here to take into account the dynamic memory allocation and the update of the object count

    static int getTeamCount()
    {
        return teamCount;
    }

    void setTeamID (string teamID)
    {
        this->teamID = teamID;
    }

    string getTeamID ()
    { return teamID; }

    void setFaculty (string faculty)
    {
        this->faculty = faculty;
    }

    string getFaculty()
    { return faculty; }

    int getTeamSize()
    { return teamSize; }

    int getCurrentSize()
    { return currentSize; }

    bool isTeamFull()
    {
        bool teamFull = false;

        if (currentSize == teamSize)
        {
            teamFull = true;
        }

        return teamFull;
    }

    Student * const getMembers()
    {
        return members;
    }

    void addMember(Student newStudent)
    {
        if (!isTeamFull())
        {
            members[currentSize] = newStudent;
            currentSize++;
        }
    }//Uses and updates the currentSize and adds new students conditionally

    Student getTheMember(string ID)
    {
        Student * studentPtr = nullptr;
        studentPtr = findMember(ID);

        return *studentPtr;
    }//Returns the member Student object with the matching ID but MUST call findMember

    void removeMember(string ID)
    {
        Student * studentPtr = nullptr;
        studentPtr = findMember(ID);

        for (int i = 0; i < teamSize; i++)
        {
            if (&members[i] == studentPtr)
            {
                members[i] = Student("--", " ", 0.0);
                teamSize--;
            }
        }
    }//Receives the ID of the student to be removed, calls the findMember function, uses the pointer it returns to remove the Student object, assumed to be called ONLY after the team is fully populated


    void displayTeamInfo()
    {
        cout << left << setw(20) << "Team: " << teamID << endl;
        cout << left << setw(20) << "Team Advisor: " << faculty << endl;
        cout << left << setw(20) << "The Number of Members: " << teamSize << endl;
        displayMembersIDs();
        cout << endl;
    }

    void displayMembersIDs()
    {
        cout << "Members of the team " << teamID << ": \n";
        for ( int i = 0; i < teamSize; i++ )
            members[i].displayID();
        cout << endl;
    }


    // Define the destructor here to free the dynamic memory and what else??
    ~Team()
    {
        delete [] members;
        teamCount--;
    }

};
#endif

int Team::teamCount = 0;
// Complete the code for the static attribute
