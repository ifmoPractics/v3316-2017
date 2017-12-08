#pragma once

#include <deque>
#include <vector>
#include <map>

class CarService {
public:

  constexpr static const size_t MAX_LICENSE_COUNT = 6;
  constexpr static const size_t MAX_OWNER_COUNT = 256;

  struct Car {
    char licensePlate[MAX_LICENSE_COUNT];
    int color;
    int numWheels;
    char owner[MAX_OWNER_COUNT];
  };

  using vCar = std::vector<Car>;
  using plate = char[MAX_LICENSE_COUNT];

public:
  void    addCar(const Car&);
  Car     getCar(const size_t index) const;
  Car     getCar(const plate& number) const;
  vCar    getCars() const;
  Car     popCar();
 
private:
  std::deque<plate> _dCars;
  std::map<plate, Car> _mCars;
};

//-----------------------------------------------------------------------------

void CarService::addCar(const Car &car)
{
  if(_mCars.count(car.licensePlate) != 0) {
    throw "Car exists";
  }
  _mCars.emplace(car.licensePlate, car);
  _dCars.push_back(car.licensePlate);
}

CarService::Car CarService::getCar(const size_t index) const
{
  if(index < 0 || index > _dCars.size()) {
    throw "Index isn't correct";
  }
  return _mCars.at(_dCars.at(index));
}

CarService::Car CarService::getCar(const plate & number) const
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
  return std::move(retCars);
}

CarService::Car CarService::popCar()
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
