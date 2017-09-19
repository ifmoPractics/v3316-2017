#include <iostream>
#include <math.h>

using namespace std;

class Cartesian {
public:
	Cartesian(float xc, float yc) {
		x = xc;
		y = yc;
	}

	void setX(float xc) {
		x = xc;
	}

	void setY(float yc) {
		y = yc;
	}

	void setDot(float xc, float yc) {
		x = xc;
		y = yc;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	/*float* getDot(){
	float* dot;
	int i = 0;
	dot[i++] = x;
	dot[i] = y;
	return dot;
	}*/
private:

	float x;

	float y;
};

class Polar {
public:
	Polar(float radC, float angleC) {
		setRad(radC);
		setAngle(angleC);
	}

	void setRad(float radC) {
		if (radC < 0) radC *= -1;
		rad = radC;
	}

	void setAngle(float angleC) {
		if (angleC > 360) angle = angleC - (int)angleC + (int)angleC % 360;
		else
			if (angleC < 0) angle = angleC - (int)angleC + 360 - (int)angleC % 360;
			else angle = angleC;
	}

	void setDot(float radC, float angleC) {
		setRad(radC);
		setAngle(angleC);
	}

	float getRad() {
		return rad;
	}

	float getAngle() {
		return angle;
	}

	/*float* getDot(){
	float* dot;
	int i = 0;
	dot[i++] = rad;
	dot[i] = angle;
	return dot;
	}*/
private:

	float rad;

	float angle;//Radians

};
Cartesian p_to_c(Cartesian dot1, Polar dot2) {
	float x, y, rad, angle;

	x = dot1.getX();
	y = dot1.getY();

	rad = dot2.getRad();
	angle = dot2.getAngle();

	x = rad*cos(angle);
	y = rad*sin(angle);

	return Cartesian(x, y);
}
Polar c_to_p(Cartesian dot1, Polar dot2) {
	float x, y, rad, angle;

	x = dot1.getX();
	y = dot1.getY();

	rad = dot2.getRad();
	angle = dot2.getAngle();

	rad = sqrt(x*x + y*y);
	angle = atan(y / x);

	return Polar(rad, angle);
}
int main() {
	float x = 0, y = 0;
	cin >> x >> y;
	Cartesian dot1(x, y);
	cout << dot1.getX() << " " << dot1.getY() << endl;

	float rad = 0, angle = 0;
	cin >> rad >> angle;
	Polar dot2(rad, angle);
	cout << dot2.getRad() << " " << dot2.getAngle() << endl;

	Cartesian dot3 = p_to_c(dot1, dot2);
	cout << dot3.getX() << " " << dot3.getY() << endl;

	Polar dot4 = c_to_p(dot1, dot2);
	cout << dot4.getRad() << " " << dot4.getAngle() << endl;

	return 0;
}