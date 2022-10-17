// Reeves Farrell
#include <string>
#include "Motorcycle.h"

string Motorcycle::getMake() {
    
    return make;
}
string Motorcycle::getModel() {
    
    return model;
}
int Motorcycle::getYear() {
    
    return year;
}
string Motorcycle::getLicensePlate() {
    
    return licensePlate;
}
int Motorcycle::getWheels() {
    
    return wheels;
}
bool Motorcycle::getSideCar() {
    
    return sideCar;
}
void Motorcycle::setMake(string a) {
    
    a = make;
}
void Motorcycle::setModel(string o) {
    
    o = model;
}
void Motorcycle::setYear(int y) {
    
    y = year;
}
void Motorcycle::setLicensePlate(string l) {
    
    l = licensePlate;
}
void Motorcycle::setWheels(int w) {
    
    w = wheels;
}
void Motorcycle::setSideCar(bool sc) {
    
    sc = sideCar;
}