#include <iostream>

void fizzBuzz(int number) {
    if (number % 3 == 0) {
        std::cout << "Fizz";
    }
    if (number % 5 == 0) {
        std::cout << "Buzz";
    }
    
    std::cout << std::endl;
}

int main() {
    for (int i = 1; i < 101; ++i) {
        std::cout << "[" << i << "] "; 
        fizzBuzz(i);
    }
}
