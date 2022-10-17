// Reeves Farrell
#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include <string>

using namespace std;

class Motorcycle {
    
    private:
        string make;
        string model;
        int year;
        string licensePlate;
        int wheels;
        bool sideCar;
    public:
        string getMake();
        string getModel();
        int getYear();
        string getLicensePlate();
        int getWheels();
        bool getSideCar();
        void setMake(string a);
        void setModel(string o);
        void setYear(int y);
        void setLicensePlate(string l);
        void setWheels(int w);
        void setSideCar(bool sc);
};  
#endif