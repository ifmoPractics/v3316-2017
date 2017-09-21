#include "polar.h"
#include <stdexcept>
#include <math.h>

Polar::Polar() {
    radius = 0;
    angle = 0;
}

Polar::Polar(double r, double a) {
    if ( isValid(r,a) ) {
        radius = r;
        angle = a;
    }
}

bool Polar::isValid(double r, double a) {
    if (r >= 0 && a >= 0 && a < 360) {
        return true;
    }
    
    throw std::logic_error("Invalid polar coordinates.");
}

void Polar::set(double r, double a) {
    if ( isValid(r,a) ) {
        radius = r;
        angle = a;
    }
}

double Polar::getRadius() {
    return radius;
}

double Polar::getAngle() {
    return angle;
}

Cartesian Polar::toCartesian() {
    Cartesian tCart;
    
    tCart.set(radius * cos(angle), radius * sin(angle));
    
    return tCart;
}
