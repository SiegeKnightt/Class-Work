#ifndef DATE_H
#define DATE_H
#include <string>

class Date {

    private:
        int day = 1;
        int month = 1;
        int year = 2021;
    public:
        // Default constructor declaration
        Date();
        // Constructor with parameters declaration
        Date(int d, int m, int y);
        bool setDay(int);
        bool setMonth(int);
        bool setYear(int);
        int getDay();
        int getMonth();
        int getYear();
        std::string showDate();
};

#endif