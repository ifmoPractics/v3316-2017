#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class ICoord {
public:
	virtual void Set(double num1, double num2) = 0;
	virtual double GetX() = 0;
	virtual double GetY() = 0;
	virtual ~ICoord(){}

};

class CoordPolar;

class CoordDecart :public ICoord {
private:
	double m_x, m_y;
public:
	void Set(double x, double y) override;
	double GetX() override;
	double GetY() override;
	CoordPolar ToPolar();
	CoordDecart(double x, double y);
	~CoordDecart(){}
	friend ostream& operator<<(ostream& os, const CoordDecart& dec);
	friend istream& operator>>(istream& is, CoordDecart& dec);

};



class CoordPolar :public ICoord {
private:
	double m_r, m_ang;
public:
	void Set(double r, double ang) override;
	double GetX() override;
	double GetY() override;
	CoordDecart ToDecart();
	CoordPolar(double r, double ang);
	~CoordPolar(){}
	friend ostream& operator<<(ostream& os, const CoordPolar& pol);
	friend istream& operator>>(istream& is, CoordPolar& pol);
};





