#include <iostream>
#include <map>
#include <deque>
#include <string>
#include <conio.h>

using namespace std;

struct Car {
	char license_plate[6];
	int color;
	int num_wheels;
	char owner[256];
};

class CarSyst {
private:
	map <string, Car> cars;
	deque <string> dequeCars ;

public:

	void Registration(const Car& object) {
		if (cars.find(object.license_plate) == cars.end()) {
			cars[object.license_plate] = object;
			dequeCars.push_back(object.license_plate);
		}
	}

	void  InfByIndex(int index) const {
		if ((index < 1) || (index > dequeCars.size())) {
			throw "Invalide index";
		}
		InfByPlate(dequeCars[index-1]);
		 
	}

	void  InfByPlate(const string& plate) const {
		if (cars.find(plate) != cars.end()) {
			cout << "Color: " << cars[plate].color << endl;
			cout << "Num wheels: " << cars[plate].num_wheels << endl;
			cout << "License plate: " << cars[plate].license_plate << endl;
			cout << "Owner: " << cars[plate].owner << endl;
			cout << "__________________" << endl;
		}
		else
			throw "Invalide plate or not car in system";
	}

	void  AllCars() const {
		for each (pair<string, Car> tmp in cars) {
			cout << "Color: " << tmp.second.color << endl;
			cout << "Num wheels: " << tmp.second.num_wheels << endl;
			cout << "License plate: " << tmp.second.license_plate << endl;
			cout << "Owner: " << tmp.second.owner << endl;
			cout << "__________________" << endl;
		}
	}

	Car GetCar() {
		if (dequeCars.empty()) {
			throw "System is empty";
		}
		Car temp = cars[dequeCars.front()];
		cars.erase(dequeCars.front());
		dequeCars.pop_front();
		return temp;
	}

};

int main() {
	CarSyst ss;
	int mainmenu = 1;
	while (mainmenu != 0) {
		cout << "MENU" << endl;
		cout << "1-Registration;" << endl;
		cout << "2-Information by number in the system;" << endl;
		cout << "3-Information by plate in the system;" << endl;
		cout << "4-Information about all cars;" << endl;
		cout << "5-Issue car and delete it;" << endl;

		cout << "0-EXIT" << endl;
		cout << endl << endl;
		cin >> mainmenu;
		switch (mainmenu)
		{
		case 1: {
			Car c;
			cout << "Input color (number) -> ";
			cin >> c.color;
			cout << "Input license plate (5 simbols) -> ";
			cin >> c.license_plate; 
			cout << "Input num wheels (number) -> ";
			cin >> c.num_wheels; 
			cout << "Input the name owner -> ";
			cin >> c.owner;
			ss.Registration(c);
					
			break;
		}
		case 2: {
			int index = 0;
			cout << "Please, enter the index of car -> ";
			cin >> index;
			try {
				ss.InfByIndex(index);
			}
			catch (...) {
				cout <<"ERROR" << endl;
			}
			break;
		}
		case 3: {
			string plate = "";
			cout << "Please, enter the plate of car -> ";
			cin >> plate;
			try {
				ss.InfByPlate(plate);
			}
			catch (...) {
				cout << "ERROR" << endl;
			}
			break;
		}
		case 4: {
			ss.AllCars();
			break;
		}
		case 5: {
			try {
				ss.GetCar();
				cout << "SUCCESSFULLY" << endl;
			}
			catch (...) {
				cout << "ERROR" << endl;
			}
			
			break;
		}
		default:
			break;
		}
		cout << endl << "Please, press ENTER to continue..." << endl;
		_getch();
		system("cls");
	}






	system("Pause");
}