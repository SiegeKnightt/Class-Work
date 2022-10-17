#ifndef INVOICE_H
#define INVOICE_H
#include <string>

using namespace std;

class Invoice { 

    private:
        string permit;
        string vehicleType;
        double price;
        double discount;
        double serviceCharge = 50.0;
    public:
        string getPermit();
        string getVehicleType();
        double getPrice();
        int getDiscount();
        double getServiceCharge();
        void setPermit(string pe);
        void setVehicleType(string vt);
        void setPrice(double pr);
        void setDiscount(double d);
        void setServiceCharge(double sc);
        double calcTotal();
        void printInvoice(Student st, Employee e, Visitor v, Service se, Car car, LEV lev, Moped mop, Motorcycle motor);
};

#endif