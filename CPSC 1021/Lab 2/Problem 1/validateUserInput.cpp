#include <iostream>
#include <iomanip>
#include "validateUserInput.h"

using namespace std;

bool validateUserInput(double input) {

    if (input < 0) {

        return false;
    }
    else {

        return true;
    }
}