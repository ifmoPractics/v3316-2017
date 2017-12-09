#include "coordinates.h"

using namespace std;

ostream & operator<<(ostream &s, const Coordinates const *c)
{
  s << "(";
  for(auto coord : c->getCoordsList()) {
    s << coord << ", ";
  }
  s << ")";
  return s;
}

istream & operator>>(istream &s, Coordinates *const c)
{
  Coordinates::lcoord coords(c->countCoord());

  cout << "Coordinates\n";
  for(size_t i = 0; i < coords.size(); ++i) {
    cout << i + 1 << ": ";
    cin >> coords[i];
  }

  c->setCoordsList(coords);

  return s;
}

PolarCoord::PolarCoord(double r, double angle)
  :_r(r), _angle(angle)
{
}

double PolarCoord::angle() const
{
  return _angle;
}

double PolarCoord::r() const
{
  return _r;
}

void PolarCoord::setAngle(double angle)
{
  _angle = angle;
}

void PolarCoord::setR(double r)
{
  _r = r;
}

Cartesian2DCoord PolarCoord::toCartesian2DCoord() const
{
  double x = _r * cos(_angle);
  double y = _r * sin(_angle);
  return Cartesian2DCoord(x, y);
}

PolarCoord::lcoord PolarCoord::getCoordsList() const
{
  lcoord ret(2);
  ret[0] = _r;
  ret[1] = _angle;
  return ret;
}

void PolarCoord::setCoordsList(const lcoord &coords)
{
  if(coords[0] < 0 || coords[0] > 360) {
    throw "Error: if PolarCoord::setCoordsList : coords[0] != {0, 360}";
  }
  if(coords[1] < 0 ) {
    throw "Error: if PolarCoord::setCoordsList : coords[1] < 0";
  }
  _r = coords[0];
  _angle = coords[1];
}

size_t PolarCoord::countCoord() const
{
  return 2;
}

Cartesian3DCoord::Cartesian3DCoord(double x, double y, double z)
  :_x(x), _y(y), _z(z)
{
}

double Cartesian3DCoord::x() const
{
  return _x;
}

double Cartesian3DCoord::y() const
{
  return _y;
}

double Cartesian3DCoord::z() const
{
  return _z;
}

void Cartesian3DCoord::setX(double x)
{
  _x = x;
}

void Cartesian3DCoord::setY(double y)
{
  _y = y;
}

void Cartesian3DCoord::setZ(double z)
{
  _z = z;
}

Cartesian3DCoord::lcoord Cartesian3DCoord::getCoordsList() const
{
  lcoord ret(3);
  ret[0] = _x;
  ret[1] = _y;
  ret[2] = _z;
  return ret;
}

void Cartesian3DCoord::setCoordsList(const lcoord &coords)
{
  _x = coords[0];
  _y = coords[1];
  _z = coords[2];
}

size_t Cartesian3DCoord::countCoord() const
{
  return 3;
}

Cartesian2DCoord::Cartesian2DCoord(double x, double y)
  :_x(x), _y(y)
{
}

double Cartesian2DCoord::x() const
{
  return _x;
}

double Cartesian2DCoord::y() const
{
  return _y;
}

void Cartesian2DCoord::setX(double x)
{
  _x = x;
}

void Cartesian2DCoord::setY(double y)
{
  _y = y;
}

PolarCoord Cartesian2DCoord::toPolarCoord() const
{
  double r = sqrt(_x * _x + _y * _y);
  double angle = atan(_y / _x);
  return PolarCoord(r, angle);
}

Cartesian2DCoord::lcoord Cartesian2DCoord::getCoordsList() const
{
  lcoord ret(2);
  ret[0] = _x;
  ret[1] = _y;
  return ret;
}

void Cartesian2DCoord::setCoordsList(const lcoord &coords)
{
  _x = coords[0];
  _y = coords[1];
}

size_t Cartesian2DCoord::countCoord() const
{
  return 2;
}
