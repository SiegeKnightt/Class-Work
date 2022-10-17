// Ben Curry
#include <iostream>
#include "Employee.h"
using namespace std;

//create employee object called employee
Employee employee;

//setter functions
void Employee::setName(string n) {
	name = n;
}
void Employee::setAddress(string a) {
	address = a;
}
void Employee::setEmail(string e) {
	email = e;
}
void Employee::setEmployeeID(int ei) {
	employeeID = ei;
}
void Employee::setEmployeeJob(string ej) {
	employeeJob = ej;
}

//getter functions
string Employee::getName() {
	return name; 
}
string Employee::getAddress() {
	return address;
}
string Employee::getEmail() {
	return email;
}
int Employee::getEmployeeID() {
	return employeeID;
}
string Employee::getEmployeeJob() {
	return employeeJob;
}