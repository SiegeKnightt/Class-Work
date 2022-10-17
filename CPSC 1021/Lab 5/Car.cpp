#include "Car.h"
#include <iostream>
#include <string>
using namespace std;

//create car object called car
Car car;

//setter functions
void Car::setMake(string ma) {
	make = ma;
}
void Car::setModel(string mo) {
	model = mo;
}
void Car::setYear(int y) {
	year = y;
}
void Car::setGasType(string gt) {
	gasType = gt;
}
void Car::setLPN(string lpn) {
	licensePlateNum = lpn;
}
void Car::setMPG(double MPG) {
	mpg = MPG;
}

//getter functions
string Car::getMake() {
	return make;
}
string Car::getModel() {
	return model;
}
int Car::getYear() {
	return year;
}
string Car::getGasType() {
	return gasType;
}
string Car::getLPN() {
	return licensePlateNum;
}
double Car::getMPG() {
	return mpg;
}