#include "Trapezoid.h"

// Checks if base 1 is greater than
// or equal to zero and returns false
// if less than zero
bool Trapezoid::setBase1(double b1) {

    bool validateData = true;

    if (b1 >= 0 ) {

        base1 = b1;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Checks if base 2 is greater than
// or equal to zero and returns false
// if less than zero
bool Trapezoid::setBase2(double b2) {

    bool validateData = true;

    if (b2 >= 0) {

        base2 = b2;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Checks if height is greater than
// or equal to zero and returns false
// if less than zero
bool Trapezoid::setHeight(double hi) {

    bool validateData = true;

    if (hi >= 0) {

        height = hi;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Returns the base 1 value as a member variable
double Trapezoid::getBase1() {

    return base1;
}

// Returns the base 2 value as a member variable
double Trapezoid::getBase2() {

    return base2;
}

// Returns the height value as a member variable
double Trapezoid::getHeight() {

    return height;
}

// Calculates and returns the area of the trapezoid
double Trapezoid::calcArea() {

    return (.5 * (base1 + base2)) * height;
}


// Trapezoid default constructor
Trapezoid::Trapezoid() {


}

// Trapezoid constructor with parameter initialization
Trapezoid::Trapezoid(double b1, double b2, double h) {

    base1 = b1;
    base2 = b2;
    height = h;
}