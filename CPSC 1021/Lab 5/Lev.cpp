#include <iostream>
#include <string>
#include "Lev.h"

string LEV::getMake(){
    return make;
}
string LEV::getModel(){
    return model;
}
int LEV::getYear(){
    return year;
}
string LEV::getLicensePlate(){
    return licensePlate;
}
double LEV::chargeTime(){
    return charge;
}
double LEV::getGallons(){
    return gallons;
}
void LEV::setMake(string a){
    make = a;
}
void LEV::setModel(string o){
    model = o;
}
void LEV::setYear(int y){
    year = y;
}
void LEV::setLicensePlate(string l){
    licensePlate = l;
}
void LEV::setChargeTime(double c){
    charge = c;
}
void LEV::setGallons(double g){
    gallons = g;
}