#ifndef SQUARE_H
#define SQUARE_H

// Class declaration
class Square {

    private:
        double side;
    
    public:
        bool setSide(double);
        double getSide();
        double calcArea();
};

#endif