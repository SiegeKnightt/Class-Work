#ifndef RECTANGLE_H
#define RECTANGLE_H

// Class declaration
class Rectangle {

    private:
        double length = 1.0;
        double width = 1.0;
    
    public:
        Rectangle();
        Rectangle(double l, double w);
        bool setLength(double);
        bool setWidth(double);
        double getLength();
        double getWidth();
        double calcArea();
};

#endif