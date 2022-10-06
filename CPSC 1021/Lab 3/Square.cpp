#include "Square.h"

// Checks if side is greater than
// or equal to zero and returns false
// if less than zero
bool Square::setSide(double si) {

    bool validateData = true;

    if (si >= 0 ) {

        side = si;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Returns the side value as a member variable
double Square::getSide() {

    return side;
}

// Calculates and return the area of the square
double Square::calcArea() {

    return side * side;
}