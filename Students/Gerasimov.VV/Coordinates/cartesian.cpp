#include "cartesian.h"
#include "polar.h"
#include <math.h>

Cartesian::Cartesian() {
    x = 0;
    y = 0;
}

Cartesian::Cartesian(double nx, double ny) {
    x = nx;
    y = ny;
}

void Cartesian::set(double nx, double ny) {
    x = nx;
    y = ny;
}

double Cartesian::getX() {
    return x;
}

double Cartesian::getY() {
    return y;
}

Polar Cartesian::toPolar() {
    Polar tPolar(0,0);
    
    if ((x > 0 && y >=0) || (x == 0 && y == 0)) {
        tPolar.set(sqrt(x*x + y*y), atan2(y, x));
    }
    else if (x > 0 && y < 0) {
        tPolar.set(sqrt(x*x + y*y), atan2(y, x) + 2*M_PI);
    }
    else if (x < 0) {
        tPolar.set(sqrt(x*x + y*y), atan2(y, x) + M_PI);
    }
    else if (y > 0) {
        tPolar.set(sqrt(x*x + y*y), M_PI/2);
    }
    else if (y < 0) {
        tPolar.set(sqrt(x*x + y*y), 3*M_PI/2);
    }
    
    return tPolar;
}
