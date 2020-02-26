#include "stdafx.h"
#include "Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() : Pentagon(0) {
}

Pentagon::Pentagon(size_t i) : side_a(i) {
	std::cout << "Pentagon created: " << side_a << std::endl;
}

Pentagon::Pentagon(std::istream &is) {
	std::cout << "Enter the side" << std::endl;
	is >> side_a;
}

Pentagon::Pentagon(const Pentagon& orig) {
	std::cout << "Pentagon copy created" << std::endl;
	side_a = orig.side_a;
}

double Pentagon::Square() {
	double hald_side = side_a / 2;
	double PI = 3.14159265;
	double h = hald_side / tan((36 * PI)/180);
	return 5 * h * hald_side;

}

void Pentagon::Print() {
	std::cout << "a=" << side_a << std::endl;
}

Pentagon::~Pentagon() {
	std::cout << "Pentagon deleted" << std::endl;
}