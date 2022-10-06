#ifndef SQUARE_H
#define SQUARE_H

// Class declaration
class Square {

    private:
        double side = 1.0;
    
    public:
        Square();
        Square(double s);
        bool setSide(double);
        double getSide();
        double calcArea();
};

#endif