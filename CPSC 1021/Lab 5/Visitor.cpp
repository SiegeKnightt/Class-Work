// Reeves Farrell
#include <string>
#include "Visitor.h"

using namespace std;

//member function definitions for Student class
string Visitor::getName() {
    
    return name;
}
string Visitor::getAddress() {
    
    return address;
}
string Visitor::getEmail() {
    
    return email;
}
string Visitor::getDuration() {
    
    return duration;
}
bool Visitor::getParent() {
    
    return parent;
}
void Visitor::setName(string n) {
    
    name = n;
}
void Visitor::setAddress(string a) {
    
    address = a;
}
void Visitor::setEmail(string e) {
    
    email = e;
}
void Visitor::setDuration(string d) {
    
    duration = d;
}
void Visitor::setParent(bool p) {
    
    parent = p;
}