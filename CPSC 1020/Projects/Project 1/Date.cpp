#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

Date::Date() = default;

// Input validation for every member variable
// Sets values to default if invalid
Date::Date(int d, int m, int y) {

    int defaultDay = 1;
    int defaultMonth = 1;
    int defaultYear = 2021;

    day = d;
    month = m;
    year = y;

    if (!setMonth(m) || !setDay(d) || !setYear(y)) {

        d = defaultDay;
        m = defaultMonth;
        y = defaultYear;
    }

    day = d;
    month = m;
    year = y;
}

// Input validation for day variable
// Leaves input unchanged if false
bool Date::setDay(int d) {

    bool validateInfo = false;

    // Condition for if month is february
    if (month == 2 && d > 28) {

        validateInfo = false;
    }  
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && d > 30) {

        validateInfo = false;
    }
    else if (d >= 1 && d <= 31) {

        day = d;
        validateInfo = true;
    }


    return validateInfo;
}

// Getter function for day
int Date::getDay() {

    return day;
}

// Input validation for month variable
// Leaves input unchanged if false
bool Date::setMonth(int m) {

    bool validateInfo = false;

    if (m >= 1 && m <= 12) {

        month = m;
        validateInfo = true;
    }

    return validateInfo;
}

// Getter function for month
int Date::getMonth() {

    return month;
}

// Input validation for year variable
// Leaves input unchanged if false
bool Date::setYear(int y) {

    bool validateInfo = false;

    if (y == 2021 || y == 2022) {

        year = y;
        validateInfo = true;
    }

    return validateInfo;
}

// Getter function for year
int Date::getYear() {

    return year;
}

// Shows full date
string Date::showDate() {

    string fullDate;
    string m = to_string(getMonth());
    string d = to_string(getDay());
    string y = to_string(getYear());

    // Determines if a zero is needed before the day or month
    if (getMonth() < 10) {

        if (getDay() < 10) {

            fullDate = "0" + m + "/0" + d + "/" + y;
        }
        else {

            fullDate = "0" + m + "/" + d + "/" + y;
        }
    }
    else {

        if (getDay() < 10) {

            fullDate = m + "/0" + d + "/" + y;
        }
        else {

            fullDate = m + "/" + d + "/" + y;
        }
    }

    return fullDate;
}