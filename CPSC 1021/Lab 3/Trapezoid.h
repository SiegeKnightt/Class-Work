#ifndef TRAPEZOID_H
#define TRAPEZOID_H

// Class declaration
class Trapezoid {

    private:
        double base1;
        double base2;
        double height;

    public:
        bool setBase1(double);
        bool setBase2(double);
        bool setHeight(double);
        double getBase1();
        double getBase2();
        double getHeight();
        double calcArea();
};

#endif