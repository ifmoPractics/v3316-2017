#include "headers.h"



int main(){
	CoordDecart a(1, 0);
	cout << a << endl;
	a.Set(0, 1);
	cout << a << endl;
	cout << "_______________________" << endl;

	CoordPolar b(2, 30);
	cout << b << endl;
	b.Set(3, 45);
	cout << b << endl;
	cout << "_______________________" << endl;

	ICoord *someCoord = new CoordDecart(5, 3);
	cout << "ICoord" << endl << "x: " << someCoord->GetX() << " y: " << someCoord->GetY() << endl;
	someCoord->Set(1, 1);
	cout << "ICoord" << endl << "x: " << someCoord->GetX() << " y: " << someCoord->GetY() << endl;
	delete someCoord;
}