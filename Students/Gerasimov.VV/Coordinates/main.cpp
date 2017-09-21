#include "cartesian.h"
#include "polar.h"
#include <iostream>
#include <stdexcept>

double getDoubleWithCheck() {
    double clean;
    
    while (true) {
        if (std::cin >> clean) {
            break;
        }
        else {
            std::cout << "Invalid number. Please try again." << std::endl;
            std::cin.clear();
            std::cin.sync();
        }
    }
    
    return clean;
}

int getIntWithCheck() {
    int clean;
    
    while (true) {
        if (std::cin >> clean) {
            break;
        }
        else {
            std::cout << "Invalid number. Please try again." << std::endl;
            std::cin.clear();
            std::cin.sync();
        }
    }
    
    return clean;
}

int main() {
    Polar exPolar(0,0);
    Cartesian exCart(0,0);
    
    int item = 0;
    
    while (item != 6) {
        std::cout << "[0] Set Polar" << std::endl;
        std::cout << "[1] Set Cartesian" << std::endl;
        std::cout << "[2] Get Polar" << std::endl;
        std::cout << "[3] Get Cartesian" << std::endl;
        std::cout << "[4] Convert Polar" << std::endl;
        std::cout << "[5] Convert Cartesian" << std::endl;
        std::cout << "[6] Exit" << std::endl;
        std::cout << "Your choice?" << std::endl;
        
        item = getIntWithCheck();
        
        double tR = 0;
        double tA = 0;
        double tX = 0;
        double tY = 0;
        
        switch (item) {
            case 0:
                tR = 0;
                tA = 0;
                std::cout << "Radius: ";
                tR = getDoubleWithCheck();
                std::cout << "Angle (rad): ";
                tA = getDoubleWithCheck();
                try {
                    exPolar.set(tR, tA);
                }
                catch (std::logic_error const& err) {
                    std::cerr << err.what() << std::endl;
                }
                break;
            case 1:
                tX = 0;
                tY = 0;
                std::cout << "X: ";
                tX = getDoubleWithCheck();
                std::cout << "Y: ";
                tY = getDoubleWithCheck();
                exCart.set(tX, tY);
                break;
            case 2:
                std::cout << "Radius: " << exPolar.getRadius() << std::endl;
                std::cout << "Angle: " << exPolar.getAngle() << " rad" << std::endl;
                break;
            case 3:
                std::cout << "X: " << exCart.getX() << std::endl;
                std::cout << "Y: " << exCart.getY() << std::endl;
                break;
            case 4:
                std::cout << "Converted from:" << std::endl;
                std::cout << "Radius: " << exPolar.getRadius() << std::endl;
                std::cout << "Angle: " << exPolar.getAngle() << " rad" << std::endl;
                std::cout << "to:" << std::endl;
                std::cout << "X: " << exPolar.toCartesian().getX() << std::endl;
                std::cout << "Y: " << exPolar.toCartesian().getY() << std::endl;
                break;
            case 5:
                std::cout << "Converted from:" << std::endl;
                std::cout << "X: " << exCart.getX() << std::endl;
                std::cout << "Y: " << exCart.getY() << std::endl;
                std::cout << "to:" << std::endl;
                std::cout << "Radius: " << exCart.toPolar().getRadius() << std::endl;
                std::cout << "Angle: " << exCart.toPolar().getAngle() << " rad" << std::endl;                
                break;
            default:
                break;
        }
    }
    
    return 0;
}
