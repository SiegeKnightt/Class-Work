// Jordyn Brooks
#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

//member function definitions for Student class
string Student::getName(){
    return name;
}
string Student::getAddress(){
    return address;
}
string Student::getEmail(){
    return email;
}
string Student::getStudentID(){
    return studentID;
}
int Student::getClassStanding(){
    return classStanding;
}
void Student::setName(string n){
    name = n;
}
void Student::setAddress(string a){
    address = a;
}
void Student::setEmail(string e){
    email = e;
}
void Student::setStudentID(string s){
    studentID = s;
}
void Student::setClassStanding(int c){
    classStanding = c;
}