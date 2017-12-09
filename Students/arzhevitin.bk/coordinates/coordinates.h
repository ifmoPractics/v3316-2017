#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------

class Coordinates
{
public:
  using lcoord = std::vector<double>;

public:
  virtual ~Coordinates() = default;

  virtual lcoord getCoordsList() const = 0;
  virtual void setCoordsList(const lcoord&) = 0;

  friend std::ostream& operator<<(std::ostream&, const Coordinates const*);
  friend std::istream& operator>>(std::istream&, Coordinates *const c);

protected:
  virtual size_t countCoord() const = 0;
};
//-----------------------------------------------------------------------------

class Cartesian2DCoord;

class PolarCoord : protected Coordinates
{
public:
  PolarCoord() = default;
  PolarCoord(double r, double angle);

  double angle() const;
  double r() const;
  void setAngle(double);
  void setR(double);

  Cartesian2DCoord toCartesian2DCoord() const;
  lcoord getCoordsList() const override;
  void setCoordsList(const lcoord&) override;

private:
  size_t countCoord() const override;

private:
  double _r = 0, _angle = 0;
};

//-----------------------------------------------------------------------------

class Cartesian3DCoord: protected Coordinates
{
public:
  Cartesian3DCoord() = default;
  Cartesian3DCoord(double x, double y, double z);

  double x() const;
  double y() const;
  double z() const;
  void setX(double);
  void setY(double);
  void setZ(double);

  lcoord getCoordsList() const override;
  void setCoordsList(const lcoord&) override;

private:
  size_t countCoord() const override;

private:
  double _x = 0, _y = 0, _z = 0;
};

//-----------------------------------------------------------------------------

class Cartesian2DCoord: protected Coordinates
{
public:
  Cartesian2DCoord() = default;
  Cartesian2DCoord(double x, double y);

  double x() const;
  double y() const;
  void setX(double);
  void setY(double);

  PolarCoord toPolarCoord() const;
  lcoord getCoordsList() const override;
  void setCoordsList(const lcoord&) override;

private:
  size_t countCoord() const override;

private:
  double _x = 0, _y = 0;
};

//-----------------------------------------------------------------------------
