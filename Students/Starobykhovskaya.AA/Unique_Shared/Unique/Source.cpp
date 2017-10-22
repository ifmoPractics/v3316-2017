#include <iostream>
//#include <conio.h>

using namespace std;

class Cat {
public:
	int name;
	friend ostream& operator<<(ostream& os, Cat& cat);
};

ostream& operator<<(ostream& os, Cat& cat) {
	os << cat.name << endl;
	return os;
}

template <class T>
class Unique_ptr {
private:

	T *obj; // pointer, which we store

	bool isExist;
	// переопределение оператора присваивания
	Unique_ptr& operator= (const Unique_ptr& tmp) {}
	Unique_ptr(const Unique_ptr& t) {}
public:
	//конструктор
	Unique_ptr(T *t) {

		obj = t;
		isExist = true;
	}
	//конструктор копирования(объект своего класса инициализируется другим объектом своего класса)

	// деструктор
	~Unique_ptr() {

		this->Reset();
	}

	//сброс счетчика
	void Reset() {
		if (isExist) {
			delete obj;
			isExist = false;
			cout << "The object was deleted." << endl;
			//_getch();
		}

	}

	// переопределение оператора *
	T* operator* () {
		return obj;
	}
	// переопределение оператора ->
	T* operator-> () {
		return obj;
	}
	// возвращение голой ссылки(адреса объекта)
	T* Release() {
		T* temp = obj;
		obj = nullptr;
		//cout << "release" << endl;
		isExist = false;
		return temp;
	}


};

int main()
{
	setlocale(LC_ALL, "Russian");
	
	Unique_ptr<int> t(new int(2));
	Unique_ptr<Cat> a(new Cat());
	a->name = 78;
	cout << a->name << endl;
	Cat *c;
	c = a.Release();

	//_getch();

}
