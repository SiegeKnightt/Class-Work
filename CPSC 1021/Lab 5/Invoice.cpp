#include <string>
#include <iostream>
#include <iomanip>
#include "Student.h"
#include "Employee.h"
#include "Visitor.h"
#include "Service.h"
#include "Car.h"
#include "Lev.h"
#include "Moped.h"
#include "Motorcycle.h"
#include "Invoice.h"

using namespace std;

string Invoice::getPermit() {

    return permit;
}
string Invoice::getVehicleType() {

    return vehicleType;
}
double Invoice::getPrice() {

    return price;
}
int Invoice::getDiscount() {

    return discount;
}
double Invoice::getServiceCharge() {

    return serviceCharge;
}
void Invoice::setPermit(string pe) {

    permit = pe;
}
void Invoice::setVehicleType(string vt) {

    vehicleType = vt;
}
void Invoice ::setPrice(double pr) {

    price = pr;
}
void Invoice::setDiscount(double d) {

    discount = d;
}
void Invoice::setServiceCharge(double sc) {

    serviceCharge = sc;
}
double Invoice::calcTotal() {

    double total;

    total = (price * discount) + serviceCharge;

    return total;
}
void Invoice::printInvoice(Student st, Employee e, Visitor v, Service se, Car car, LEV lev, Moped mop, Motorcycle motor) {

    if (permit == "Student") {

        cout << "Pass Purchased: " << getPermit() << endl;
        cout << "Name: " << st.getName() << endl;
        cout << "Address: " << st.getAddress() << endl;
        cout << "Email: " << st.getEmail() << endl;
        cout << "Student ID: " << st.getStudentID() << endl;
        cout << "Class Standing: " << st.getClassStanding() << endl;
    }
    else if (permit == "Employee") {

        cout << "Pass Purchased: " << getPermit() << endl;
        cout << "Name: " << e.getName() << endl;
        cout << "Address: " << e.getAddress() << endl;
        cout << "Email: " << e.getEmail() << endl;
        cout << "Employee ID: " << e.getEmployeeID() << endl;
        cout << "Employee Job: " << e.getEmployeeJob() << endl;
    }
    else if (permit == "Visitor") {

        cout << "Pass Purchased: " << getPermit() << endl;
        cout << "Name: " << v.getName() << endl;
        cout << "Address: " << v.getAddress() << endl;
        cout << "Email: " << v.getEmail() << endl;
        cout << "Duration: " << v.getDuration() << endl;
        cout << "Parent: " << v.getParent() << endl;
    }
    else if (permit == "Service") {

        cout << "Pass Purchased: " << getPermit() << endl;
        cout << "Name: " << se.getName() << endl;
        cout << "Address: " << se.getAddress() << endl;
        cout << "Email: " << se.getEmail() << endl;
        cout << "Department: " << se.getDepartment() << endl;
        cout << "Years Service: " << se.getYearsService() << endl;
    }


    if (vehicleType == "Car") {

        cout << "Vehicle Type: " << getVehicleType() << endl;
        cout << "Make: " << car.getMake() << endl;
        cout << "Model: " << car.getModel() << endl;
        cout << "Year: " << car.getYear() << endl;
        cout << "Lisence Plate: " << car.getLPN() << endl;
        cout << "Gas Type: " << car.getGasType() << endl;
        cout << "MPG: " << car.getMPG() << endl;
    }
    else if (vehicleType == "LEV") {

        cout << "Vehicle Type: " << getVehicleType() << endl;
        cout << "Make: " << lev.getMake() << endl;
        cout << "Model: " << lev.getModel() << endl;
        cout << "Year: " << lev.getYear() << endl;
        cout << "Lisence Plate: " << lev.getLicensePlate() << endl;
        cout << "Charge Time: " << lev.chargeTime() << endl;
        cout << "Gallons: " << lev.getGallons() << endl;
    }
    else if (vehicleType == "Moped") {

        cout << "Vehicle Type: " << getVehicleType() << endl;
        cout << "Make: " << mop.getMake() << endl;
        cout << "Model: " << mop.getModel() << endl;
        cout << "Year: " << mop.getYear() << endl;
        cout << "Lisence Plate: " << mop.getLicensePlate() << endl;
        cout << "Moped Power: " << mop.getMopedPower() << endl;
        cout << "Commute Distance: " << mop.getCommuteDistance() << endl;
    }
    else if (vehicleType == "Motorcycle") {

        cout << "Vehicle Type: " << getVehicleType() << endl;
        cout << "Make: " << motor.getMake() << endl;
        cout << "Model: " << motor.getModel() << endl;
        cout << "Year: " << motor.getYear() << endl;
        cout << "Lisence Plate: " << motor.getLicensePlate() << endl;
        cout << "Wheels: " << motor.getWheels() << endl;
        cout << "Side Car: " << motor.getSideCar() << endl;
    }

    cout << "Total: $" << fixed << setprecision(2) << calcTotal() << endl;
}