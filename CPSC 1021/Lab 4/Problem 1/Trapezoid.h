#ifndef TRAPEZOID_H
#define TRAPEZOID_H

// Class declaration
class Trapezoid {

    private:
        double base1 = 1.0;
        double base2 = 1.0;
        double height = 1.0;

    public:
        Trapezoid();
        Trapezoid(double base1, double base2, double height);
        bool setBase1(double);
        bool setBase2(double);
        bool setHeight(double);
        double getBase1();
        double getBase2();
        double getHeight();
        double calcArea();
};

#endif