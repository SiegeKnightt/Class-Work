#ifndef CIRCLE_H
#define CIRCLE_H

// Class declaration
class Circle {

    private:
        double radius = 1.0;
    
    public:
        Circle();
        Circle(double rad);
        bool setRadius(double);
        double getRadius();
        double calcArea();
};

#endif