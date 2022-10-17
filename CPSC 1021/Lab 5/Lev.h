#ifndef LEV_H
#define LEV_H
#include <string>

using namespace std;

class LEV{
    private:
        string make;
        string model;
        int year;
        string licensePlate;
        double charge;
        double gallons;
    public:
        string getMake();
        string getModel();
        int getYear();
        string getLicensePlate();
        double chargeTime();
        double getGallons();
        void setMake(string a);
        void setModel(string o);
        void setYear(int y);
        void setLicensePlate(string l);
        void setChargeTime(double c);
        void setGallons(double g);
};  
#endif