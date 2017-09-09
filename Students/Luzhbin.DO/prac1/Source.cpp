#include <iostream>
using namespace std;

int main()
{
	for (int i = 1; i < 101; i++)
	{
		long n = i;
		if ((n % 3 != 0) & (n % 5 != 0)) { cout << (i) << endl; }
		else if (n % 3 != 0) { cout << "Fizz" << endl; }
		else if (n % 5 != 0) { cout << "Buzz" << endl; }
		else { cout << "FizzBuzz" << endl; };


	}
	return (0);

}