#ifndef RECTANGLE_H
#define RECTANGLE_H

// Class declaration
class Rectangle {

    private:
        double length;
        double width;
    
    public:
        bool setLength(double);
        bool setWidth(double);
        double getLength();
        double getWidth();
        double calcArea();
};

#endif