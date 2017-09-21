#include "cartesian.h"

#ifndef POLAR_H
#define POLAR_H

class Polar {
    public:
        Polar();
        Polar(double r, double a);
        void set(double r, double a);
        double getRadius();
        double getAngle();
        Cartesian toCartesian();
    private:
        bool isValid(double r, double a);
        double radius;
        double angle;
};

#endif
