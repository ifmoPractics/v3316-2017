#include <iostream>
#include <math.h>


using namespace std;
class Coordinates {
public:
	virtual void set(double c1, double c2) = 0;//абстрактный метод=нет определения
	virtual double getX() = 0;
	virtual double getY() = 0;
	virtual ~Coordinates() = default;// надо или нет?
/*если у вас в классе присутствует хотя бы одна виртуальная функция, деструктор также следует сделать виртуальным*/
};

class Polar;

class Decart :public Coordinates {
private:
	double x, y;
public:
	void set(double coor1, double coor2) override;
	/*Собственно, возвращаясь к virtual.
	Я мог в классах A и B не объявлять методы как virtual, всё равно сработает метод из B.
	Точно так же, независимо от того, напишу я так  virtual void bar() в B классе или так virtual void bar() override, 
	тоже ничего не изменится.Что с override, что без него метод дочернего класса перекроет метод базового.
	Просто написав override мы явно это указываем.Очень полезно, если вы с кодом работаете не один.*/
	double getX() override;
	double getY() override;
	Polar convertToPol();
	Decart(double x1, double x2);
	~Decart() = default;
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



class Polar :public Coordinates {
private:
	double r, phi;
public:
	void set(double r1, double phi1) override;
	double getX() override;
	double getY() override;
	Decart convertToDec();
	Polar(double r1, double phi1);
	~Polar() = default;
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


Polar Decart::convertToPol() {
	double r, phi;
	r =  sqrt(this->x*this->x + this->y*this->y);
	phi =  atan(this->y / this->x);
	return Polar(r, phi);
}

int main()
{
	//cout << "start" << endl;
	Coordinates *tmp = new Polar(0,0);
	cout << "Y of tmp " << tmp->getY() << endl;
	Polar x(3, 45);
	//cout << "Body1" << endl;
	Decart y(1, 2);
	//cout << "Body1" << endl;
	//cin >> y;
	//cout << "Body1" << endl;
	double k = y.getX();
	cout << "X of k "<< k << endl;
	x = y.convertToPol();
	cout << "Y converted into Polar" << x << endl;
	cout << x << endl;
	system("pause");
	return 0;

}

