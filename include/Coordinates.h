#ifndef COORDINATES_H
#define COORDINATES_H

// struct for storing location coordinates
struct Coordinates {
    double x;
    double y;
    Coordinates(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Coordinates():Coordinates(0, 0) {}
};

#endif