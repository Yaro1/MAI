#include <iostream>
#include <iostream>
#include <chrono>
#include <fstream>
#include "TLongNum.h"

int main() {
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::string str1, str2;
    std::ifstream in("00.t");
    char op;
    while (in >> str1 && in >> str2) {

        TLongNum bigInt1(str1);
        TLongNum bigInt2(str2);

        in >> op;

        switch (op) {
            case '+':
                std::cout << bigInt1 + bigInt2 << std::endl;
                break;
            case '>':
                std::cout << (bigInt1 > bigInt2 ? "true" : "false") << std::endl;
                break;
            case '<':
                std::cout << (bigInt1 < bigInt2 ? "true" : "false") << std::endl;
                break;
            case '=':
                std::cout << (bigInt1 == bigInt2 ? "true" : "false") << std::endl;
                break;
            case '-':
                if (bigInt1 >= bigInt2) {
                    std::cout << bigInt1 - bigInt2 << std::endl;
                } else {
                    std::cout << "Error" << std::endl;
                }
                break;
            case '*':
                std::cout << bigInt1 * bigInt2 << std::endl;
                break;
            case '^':
                if (bigInt1 == TLongNum(1, 0)) {
                    if (bigInt2 == TLongNum(1, 0)) {
                        std::cout << "Error" << std::endl;
                    } else {
                        std::cout << 0 << std::endl;
                    }
                } else if (bigInt1 == TLongNum(1, 1)) {
                    std::cout << 1 << std::endl;
                } else {
                    int numPow = std::stoi(str2);
                    std::cout << (bigInt1 ^ numPow) << std::endl;
                }
                break;
            case '/':
                if (bigInt2 == TLongNum(1, 0)) {
                    std::cout << "Error" << std::endl;
                } else {
                    std::cout << bigInt1 / bigInt2 << std::endl;
                }
                break;
            default:
                std::cout << "Error" << std::endl;
                break;
        }
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "TLongNum: " << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;

    return 0;
}