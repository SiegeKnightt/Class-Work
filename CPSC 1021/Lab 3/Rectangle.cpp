#include "Rectangle.h"

// Checks if length is greater than
// or equal to zero and returns false
// if less than zero
bool Rectangle::setLength(double len) {

    bool validateData = true;

    if (len >= 0 ) {

        length = len;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Checks if width is greater than
// or equal to zero and returns false
// if less than zero
bool Rectangle::setWidth(double wid) {

    bool validateData = true;

    if (wid >= 0) {

        width = wid;
    }
    else {

        validateData = false;
    }

    return validateData;
}

// Returns the length value as a member variable
double Rectangle::getLength() {

    return length;
}

// Returns the width value as a member variable
double Rectangle::getWidth() {

    return width;
}

// Calculates and returns the area of the rectangle
double Rectangle::calcArea() {

    return length * width;
}