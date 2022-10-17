// Jordyn Brooks
#ifndef STUDENT_H
#define STUDENT_H
#include <string> //not sure if needed in h file

using namespace std;

//class collects information for customer type Student
class Student{
    private:
        string name;
        string address;
        string email;
        string studentID;
        int classStanding;
    public:
        string getName();
        string getAddress();
        string getEmail();
        string getStudentID();
        int getClassStanding();
        void setName(string n);
        void setAddress(string a);
        void setEmail(string e);
        void setStudentID(string s);
        void setClassStanding(int c);
};
#endif