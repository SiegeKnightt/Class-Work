/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/21/2022
Desc: Parking pass application
using OOP concepts
Time: 
*/

#include <iostream>
#include <string>
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

int main () {

    // Instantiates Invoice class
    Invoice in;
    Student st;
    Employee e;
    Visitor v;
    Service se;
    Car car;
    LEV lev;
    Moped mop;
    Motorcycle motor;

    string customerType;
    string vehicleType;
    string name;
    string email;
    string address;
    string make;
    string model;
    string licensePlate;
    int year;

    cout << "Please enter user type:" << endl;
    cout << "Options: Student, Employee, Visitor, Service" << endl;

    cin >> customerType;
    in.setPermit(customerType);

    // Options for customer type
    if (customerType == "Student") {
        
        string ID;
        int classStanding;

        cout << "Enter your full name:" << endl;

        cin.ignore();
        getline(cin, name);
        st.setName(name);

        cout << "Enter your full address:" << endl;

        getline(cin, address);
        st.setAddress(address);

        cout << "Enter your email address:" << endl;

        cin >> email;
        st.setEmail(email);

        cout << "Enter your student ID:" << endl;
        
        cin >> ID;
        st.setStudentID(ID);

        cout << "Enter your class standing:" << endl;
        cout << "Ex. 1 = Freshman, 2 = Sophmore, etc..." << endl;

        cin >> classStanding;
        st.setClassStanding(classStanding);
    }
    else if (customerType == "Employee") {

        int employeeID;
        string employeeJob;

        cout << "Enter your full name:" << endl;

        cin.ignore();
        getline(cin, name);
        e.setName(name);

        cout << "Enter your full address:" << endl;

        getline(cin, address);
        e.setAddress(address);

        cout << "Enter your email address:" << endl;

        cin >> email;
        e.setEmail(email);

        cout << "Enter your employee ID number:" << endl;
        
        cin >> employeeID;
        e.setEmployeeID(employeeID);

        cout << "Enter your job title:" << endl; 

        cin.ignore();
        getline(cin, employeeJob);
        e.setEmployeeJob(employeeJob);
    }
    else if (customerType == "Visitor") {
        
        string duration;
        bool isParent;

        cout << "Enter your full name:" << endl;

        cin.ignore();
        getline(cin, name);
        v.setName(name);

        cout << "Enter your full address:" << endl;

        getline(cin, address);
        v.setAddress(address);

        cout << "Enter your email address:" << endl;

        cin >> email;
        v.setEmail(email);

        cout << "Enter the duration for your pass:" << endl;
        
        cin.ignore();
        getline(cin, duration);
        v.setDuration(duration);

        cout << "Are you a parent?" << endl;
        cout << "Enter 1 for yes or 0 for no:" << endl;

        cin >> isParent;
        v.setParent(isParent);
    }
    else if (customerType == "Service") {

        string department;
        int yearsService;
        
        cout << "Enter your full name:" << endl;

        cin.ignore();
        getline(cin, name);;
        se.setName(name);

        cout << "Enter your full address:" << endl;

        getline(cin, address);
        se.setAddress(address);

        cout << "Enter your email address:" << endl;

        cin >> email;
        se.setEmail(email);

        cout << "Enter your department:" << endl;
        
        cin.ignore();
        getline(cin, department);
        se.setDepartment(department);

        cout << "How many years have you been in service?" << endl;

        cin >> yearsService;
        se.setYearsService(yearsService);
    }

    cout << "Which vehicle type would you like a pass for?" << endl;
    cout << "Options: Car, LEV, Moped, Motorcycle" << endl;

    cin >> vehicleType;
    in.setVehicleType(vehicleType);

    // Options for vehicle type
    if (vehicleType == "Car") {

        if (customerType == "Student") {

            in.setPrice(173.0);
        }
        else if (customerType == "Employee") {

            in.setPrice(150.0);
        }
        else if (customerType == "Visitor") {

            in.setPrice(30.0);
        }
        else if (customerType == "Servie") {

            in.setPrice(150.0);
        }

        in.setDiscount(1);

        string gasType;
        double mpg;

        cout << "Enter the make of your vehicle:" << endl;
        
        cin.ignore();
        getline(cin, make);
        car.setMake(make);

        cout << "Enter the model of your vehicle:" << endl;

        getline(cin, model);
        car.setModel(model);

        cout << "What year is your vehicle?" << endl;

        cin >> year;
        car.setYear(year);

        cout << "What is your license plate number?" << endl;

        cin >> licensePlate;
        car.setLPN(licensePlate);

        cout << "What is your car's gas type?" << endl;

        cin.ignore();
        getline(cin, gasType);
        car.setGasType(gasType);

        cout << "What is the miles per gallon for your car?" << endl;
        cout << "Please enter a decimal:" << endl;

        cin >> mpg;
        car.setMPG(mpg);
    }
    else if (vehicleType == "LEV") {

        if (customerType == "Student") {

            in.setPrice(173.0);
        }
        else if (customerType == "Employee") {

            in.setPrice(150.0);
        }
        else if (customerType == "Visitor") {

            in.setPrice(30.0);
        }
        else if (customerType == "Servie") {

            in.setPrice(150.0);
        }

        in.setDiscount(0.8);

        double charge;
        double gallons;

        cout << "Enter the make of your vehicle:" << endl;
        
        cin.ignore();
        getline(cin, make);
        lev.setMake(make);

        cout << "Enter the model of your vehicle:" << endl;

        getline(cin, model);
        lev.setModel(model);

        cout << "What year is your vehicle?" << endl;

        cin >> year;
        lev.setYear(year);

        cout << "What is your license plate number?" << endl;

        cin >> licensePlate;
        lev.setLicensePlate(licensePlate);

        cout << "What is your LEV's charge time in hours?" << endl;
        cout << "Please enter a decimal:" << endl;

        cin >> charge;
        lev.setChargeTime(charge);

        cout << "What is your LEV's tank size in gallons?" << endl;
        cout << "Please enter a decimal:" << endl;

        cin >> gallons;
        lev.setGallons(gallons);

    }
    else if (vehicleType == "Moped") {

        double mopedPrice = 75.0;
        in.setDiscount(1);
        in.setPrice(mopedPrice);

        int mopedPower;
        int commuteDistance;

        cout << "Enter the make of your vehicle:" << endl;
        
        cin.ignore();
        getline(cin, make);
        mop.setMake(make);

        cout << "Enter the model of your vehicle:" << endl;

        getline(cin, model);
        mop.setModel(model);

        cout << "What year is your vehicle?" << endl;

        cin >> year;
        mop.setYear(year);

        cout << "What is your license plate number?" << endl;

        cin >> licensePlate;
        mop.setLicensePlate(licensePlate);

        cout << "What is your moped's power?" << endl;

        cin >> mopedPower;
        mop.setMopedPower(mopedPower);

        cout << "What is your commute distance to the nearest mile?" << endl;

        cin >> commuteDistance;
        mop.setCommutedistance(commuteDistance);
    }
    else if (vehicleType == "Motorcycle") {

        double motorcyclePrice = 75.0;
        in.setDiscount(1);
        in.setPrice(motorcyclePrice);

        int wheels;
        bool sideCar;

        cout << "Enter the make of your vehicle:" << endl;
        
        cin.ignore();
        getline(cin, make);
        motor.setMake(make);

        cout << "Enter the model of your vehicle:" << endl;

        getline(cin, model);
        motor.setModel(model);

        cout << "What year is your vehicle?" << endl;

        cin >> year;
        motor.setYear(year);

        cout << "What is your license plate number?" << endl;

        cin >> licensePlate;
        motor.setLicensePlate(licensePlate);

        cout << "How many wheels does your motorcycle have?" << endl;

        cin >> wheels;
        motor.setWheels(wheels);

        cout << "Does your motorcyle have a side car?" << endl;
        cout << "Enter 1 for yes or 0 for no:" << endl;

        cin >> sideCar;
        motor.setSideCar(sideCar);
    }

    in.printInvoice(st, e, v, se, car, lev, mop, motor);

    return 0;
}