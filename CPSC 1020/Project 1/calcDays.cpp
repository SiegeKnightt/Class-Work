#include <iostream>
#include "calcDays.h"
#include "Date.h"

int calcDays (const Date &date1, const Date &date2) {

    // Sets instance equal to the constanst so they can be changed
    Date d1 = date1;
    Date d2 = date2;

    // Month, day, year
    // 01/01/2021
    int defaultDate[] = {1, 1, 2021};
    // Months of the year with corresponding days
    // Index 0 = January
    int daysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31};
    int daysDiff1;
    int daysDiff2; 
    int day1 = d1.getDay();
    int month1 = d1.getMonth();
    int year1 = d1.getYear();
    int day2 = d2.getDay();
    int month2 = d2.getMonth();
    int year2 = d2.getYear();

    // Calculates the difference between date1 and the default date
    int dd1 = day1 - defaultDate[1];
    int mm1 = month1 - defaultDate[0];
    int yy1 = year1 - defaultDate[2];

    // Calculates the difference between date2 and the default date
    int dd2 = day2 - defaultDate[1];
    int mm2 = month2 - defaultDate[0];
    int yy2 = year2 - defaultDate[2];

    // Adds the days for the whole year to current day value
    daysDiff1 = (yy1 * 365) + dd1;

    // Adds days corresponding to the months in the date
    for (int i = 0; i < mm1; i++) {

        daysDiff1 = daysDiff1 + daysOfMonth[i];
    }

    // Adds the days for the whole year to current day value
    daysDiff2 = (yy2 * 365) + dd2;

    // Adds days corresponding to the months in the date
    for (int j = 0; j < mm2; j++) {

        daysDiff2 = daysDiff2 + daysOfMonth[j];
    }

    // Return differences between saysDiff1 and daysDiff2
    if (daysDiff1 > daysDiff2) {

        return daysDiff1 - daysDiff2;
    }
    else {

        return daysDiff2 - daysDiff1;
    }
}