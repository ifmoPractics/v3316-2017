#pragma once

#include <deque>
#include <vector>
#include <map>
#include <string>

constexpr static const size_t LICENSE_COUNT = 6;
constexpr static const size_t OWNER_COUNT = 256;

struct Car
{
  char licensePlate[LICENSE_COUNT];
  int color;
  int numWheels;
  char owner[OWNER_COUNT];
};

class CarService {
public:
  using vCar = std::vector<Car>;

public:
  void    addCar(const Car& );
  Car     getCar(const size_t index) const;
  Car     getCar(const std::string &number) const;
  vCar    getCars() const;
  Car     popCar();
 
private:
  std::deque<std::string> _dCars;
  std::map<std::string, Car> _mCars;
};

//-----------------------------------------------------------------------------

void CarService::addCar(const Car &car)
{
  if(_mCars.count(car.licensePlate) != 0) {
    throw "Car exists";
  }
  _mCars.insert({ car.licensePlate, car });
  _dCars.push_back(car.licensePlate);
}

Car CarService::getCar(const size_t index) const
{
  if(index <= 0 || index > _dCars.size()) {
    throw "Index isn't correct";
  }
  return _mCars.at(_dCars.at(index-1));
}

Car CarService::getCar(const std::string &number) const
{
  auto it = _mCars.find(number);
  if(it == _mCars.end()) {
    throw "Car doesn't exist";
  }
  return it->second;
}

CarService::vCar CarService::getCars() const
{
  std::vector<Car> retCars(_dCars.size());
  for(size_t i = 0; i < _dCars.size(); ++i) {
    retCars[i] = _mCars.at(_dCars.at(i));
  }
  return retCars;
}

Car CarService::popCar()
{
  if(_dCars.empty()) {
    throw "No car avaliable";
  }
  auto it = _mCars.find(_dCars.front());
  Car retCar = it->second;
  _dCars.pop_front();
  _mCars.erase(it);  
  return retCar;
}