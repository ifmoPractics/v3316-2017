#include "headers.h"

ostream& operator<<(ostream& os, const CoordDecart& dec)
{
	os <<"x: " << dec.m_x << " y: " << dec.m_y;
	return os;
}

istream& operator>>(istream& is, CoordDecart& dec)
{
	is >> dec.m_x >> dec.m_y;
	return is;
}
CoordDecart::CoordDecart(double x, double y) {
	Set(x, y);
}
void CoordDecart::Set(double x, double y) {
	m_x = x;
	m_y = y;
}

double CoordDecart::GetX() {
	return m_x;
}
double CoordDecart::GetY() {
	return m_y;
}

CoordPolar CoordDecart::ToPolar() {
	return CoordPolar(sqrt(m_x*m_x + m_y*m_y), atan(m_y / m_x));
}

///////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& os, const CoordPolar& pol)
{
	os <<"r: "<< pol.m_r << " ang: " << pol.m_ang;
	return os;
}
istream& operator>>(istream& is, CoordPolar& pol)
{
	is >> pol.m_r >> pol.m_ang;
	return is;
}
CoordPolar::CoordPolar(double r, double ang) {
	Set(r, ang);

}

CoordDecart CoordPolar::ToDecart() {
	return CoordDecart(m_r*cos(m_ang), m_r*sin(m_ang));
}


void CoordPolar::Set(double r, double ang) {
	if ((ang >= 0) && (ang <= 360)) {
		m_ang = ang;
		m_r = r;
	}
	else
		throw "incorrect values";
}
double CoordPolar::GetX() {
	return m_r;
}
double CoordPolar::GetY() {
	return m_ang;
}