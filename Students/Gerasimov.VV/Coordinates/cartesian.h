#ifndef CARTESIAN_H
#define CARTESIAN_H

class Polar;

class Cartesian {
    public:
        Cartesian();
        Cartesian(double nx, double ny);
        void set(double nx, double ny);
        double getX();
        double getY();
        Polar toPolar();
    private:
        double x;
        double y;
};

#endif

