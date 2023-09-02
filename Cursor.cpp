#include "Cursor.h"

Cursor::Cursor(double x, double y) {
    this->x = x;
    this->y = y;
}

Cursor::~Cursor() {
    //dtor
}
double Cursor::getX() {
    return x;
}

double Cursor::getY() {
    return y;
}
