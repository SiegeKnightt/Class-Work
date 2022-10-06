#include "Circle.h"

// Checks if radius is greater than
// or equal to zero and returns false
// if less than zero
bool Circle::setRadius(double rad) {

    bool validateData = true;

    if (rad >= 0 ) {

        radius = rad;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Returns the radius value as a member variable
double Circle::getRadius() {

    return radius;
}

// Calculates and return the area of the circle
double Circle::calcArea() {

    double PI = 3.14159;

    return (radius * radius) * PI;
}