#include <iostream>

int main() {
	bool flag;
	for (int i = 1; i < 101; i++) {
		flag = true;
		if (i % 3 == 0) {
			flag = false;
			std::cout << "Fizz";
		}
		if (i % 5 == 0) {
			flag = false;
			std::cout << "Buzz";
		}
		if (flag) std::cout << i;
		std::cout << std::endl;
	}
}