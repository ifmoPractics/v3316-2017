#include "stdafx.h"
#include <iostream>
#include <math.h>


using namespace std;
class Coordinates {
public:
	virtual void set(double c1, double c2)=0;//абстрактный метод=нет определения
	virtual double getX() = 0;
	virtual double getY() = 0;
};

class Polar;
class Decart :public Coordinates {
private:
	double x, y;
public:
	void set(double coor1, double coor2);
	double getX();
	double getY();
	Polar convertToPol();
	Decart(double x1, double x2);
	~Decart();
	friend ostream& operator<<(ostream& os, const Decart& dec);
	friend istream& operator>>(istream& is, Decart& dec);

};
ostream& operator<<(ostream& os, const Decart& dec)// дружественная функция
{
	os << dec.x << " ; " << dec.y;
	return os;
}
istream& operator>>(istream& is, Decart& dec)// дружественная функция
{
	is >> dec.x >> dec.y;
	return is;
}
Decart::Decart(double x1, double x2) {
	x = x1;
	y = x2;
}
Decart::~Decart() {}
void Decart::set(double coor1, double coor2) {
	x = coor1;
	y = coor2;
}

double Decart::getX() {
	return x;
}
double Decart::getY() {
	return y;
}
Polar Decart::convertToPol() {
	double r, phi;
	r = sqrt(this->x*this->x + this->y*this->y);
	phi = atan(this->y / this->x);
	return Polar(r, phi);
}

class Polar:public Coordinates {
private:
	double r,phi;
public:
	void set(double r1, double phi1);
	double getX();
	double getY();
	Decart convertToDec();
	Polar(double r1, double phi1);
	~Polar();
	friend ostream& operator<<(ostream& os, const Polar& pol);
	friend istream& operator>>(istream& is, Polar& pol);
};
ostream& operator<<(ostream& os, const Polar& pol)// дружественная функция
{
	os << pol.r << " ; " << pol.phi;
	return os;
}
istream& operator>>(istream& is, Polar& pol)// дружественная функция
{
	is >> pol.r >> pol.phi;
	return is;
}
Polar::Polar(double r1, double phi1) {
	if ((phi1 < 0) && (phi > 360)) {
		throw 0;
	}
	phi = phi1;
	r = r1;

}
Polar::~Polar() {};
Decart Polar::convertToDec() {
	double x, y;
	x = this->r*cos(this->phi);
	y = this->r*sin(this->phi);
	return Decart(x, y);
}


void Polar::set(double r1, double phi1) {
	if ((phi1 < 0) && (phi > 360)) {
			throw 0;
			}
	phi = phi1;
	r = r1;
}
double Polar::getX() {
	return r;
}
double Polar::getY() {
	return phi;
}




int main()
{
	
	Polar x(3,45);
	Decart y(1 , 2);
	cin >> y;
	y = x.convertToDec();
	cout << y<<endl;
    return 0;
	
}

