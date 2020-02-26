#include "stdafx.h"
#include "Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() : Pentagon(0) {
}

Pentagon::Pentagon(size_t i) : side_a(i) {
	std::cout << "Pentagon created: " << side_a << std::endl;
	square = Square();
}

Pentagon::Pentagon(std::istream &is) {
	std::cout << "Enter the side" << std::endl;
	is >> side_a;
	square = Square();
}

Pentagon::Pentagon(Pentagon& orig) {
	std::cout << "Pentagon copy created" << std::endl;
	side_a = orig.side_a;
	square = orig.square;
}

double Pentagon::Square() {
	double hald_side = side_a / 2;
	double PI = 3.14159265;
	double h = hald_side / tan((36 * PI)/180);
	return 5 * h * hald_side;

}

void Pentagon::Print() {
	std::cout << "Pentagon : side=" << side_a << "  Square is " << Square() << std::endl;
}

Pentagon::~Pentagon() {
	std::cout << "Pentagon deleted" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Pentagon& obj) {

	os << "a=" << obj.side_a << " , square=" << obj.square << std::endl;

	return os;

}