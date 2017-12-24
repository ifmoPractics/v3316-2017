#include <iostream>
#include <math.h>

using namespace std;

class Coordinat{
public:
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual void setX(double x) = 0;
    virtual void setY(double y) = 0;
    virtual void set(double x, double y) = 0;
    virtual ~Coordinat(){};
};

class Polar;

class Decart : public Coordinat
{
private:
    double m_x;
    double m_y;
public:
    double getX() const override;
    double getY() const override;
    void setX(double x) override;
    void setY(double y) override;
    void set(double x, double y) override;
    friend ostream& operator << (ostream &stream, Decart &obj);
    friend istream& operator >> (istream &stream, Decart &obj);
    Polar convert_to_Polar();
    Decart(double x, double y) : m_x(x), m_y(y) {}
    Decart() : m_x(0), m_y(0) {}
    ~Decart(){}
};

double Decart::getX() const{
    return  m_x;
}

double Decart::getY() const{
    return m_y;
}

void Decart::setX(double x){
    m_x = x;
}

void Decart::setY(double y){
    m_y = y;
}

void Decart::set(double x, double y){
    m_x = x;
    m_y = y;
}

ostream& operator << (ostream &stream, Decart &obj){
    stream<<obj.m_x<< " " << obj.m_y;
    return stream;
}

istream& operator >> (istream &stream, Decart &obj){
    stream >> obj.m_x >> obj.m_y;
    return stream;
}

class Polar : public Coordinat
{
private:
    double m_r;
    double m_phi;
public:
    double getX() const override;
    double getY() const override;
    void setX(double r) override;
    void setY(double phi) override;
    void set(double r, double phi) override;
    friend ostream& operator << (ostream &stream, Polar &obj);
    friend istream& operator >> (istream &stream, Polar &obj);
    Decart convert_to_Dec();
    Polar(double r, double phi){
        if (r<0){
            cout<<"Invalid R"<<endl;
            m_r = 0;
        }
        else
            m_r = r;
        if (phi<0 || phi>360){
            cout<<"Invalid Phi"<<endl;
            m_phi = 0;
        }
        else
            m_phi = phi;
    }
    Polar() : m_r(0), m_phi(0) {}
    ~Polar(){}
};

double Polar::getX() const{
    return m_r;
}

double Polar::getY() const{
    return m_phi;
}

void Polar::setX(double r){
    if (r<0)
        throw "invalid r";
    m_r = r;
}

void Polar::setY(double phi){
    if (phi<0 || phi>360)
        throw "invalid phi";
    m_phi = phi;
}

void Polar::set(double r, double phi){
    if (r<0)
        throw "invalid r";
    if (phi<0 || phi>360)
        throw "invalid phi";
    m_r = r;
    m_phi = phi;
}

ostream& operator << (ostream &stream, Polar &obj){
    stream<<obj.m_r<<" "<<obj.m_phi;
    return stream;
}

istream& operator >> (istream &stream, Polar &obj){
    stream >> obj.m_r >> obj.m_phi;
    return stream;
}

Polar Decart::convert_to_Polar(){
    return Polar(sqrt(pow(m_x, 2)+pow(m_y, 2)), atan(m_y/m_x));
}

Decart Polar::convert_to_Dec(){
    return Decart(m_r*cos(m_phi), m_r*sin(m_phi));
}

int main() {
    
    return 0;
}
