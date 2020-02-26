#include "stdafx.h"
#include "Rhombus.h"
#include <iostream>
#include <cmath>

Rhombus::Rhombus() : Rhombus(0, 0, 0) {
}

Rhombus::Rhombus(size_t i, size_t j, size_t k) : side_a(i), d1(j), d2(k), square(0.5 * d1 * d2) {
	std::cout << "Rhombus created: " << side_a << ", " << d1 << ", " << d2 << std::endl;
}

Rhombus::Rhombus(std::istream &is) {
	std::cout << "Enter side, first diagonal, second diagonal" << std::endl;
	is >> side_a;
	is >> d1;
	is >> d2;
	square = 0.5 * d1 * d2;
}

Rhombus::Rhombus(const Rhombus& orig) {
	std::cout << "Rhombus copy created" << std::endl;
	side_a = orig.side_a;
	d1 = orig.d1;
	d2 = orig.d2;
	square = orig.square;
}

double Rhombus::Square() {
	return 0.5 * d1 * d2;

}

void Rhombus::Print() {
	std::cout << "Rhombus :   Side=" << side_a << ", First diagonal=" << d1 << ", Second diagonal=" << d2 << ", Square=" << square <<std::endl;
}

Rhombus::~Rhombus() {
	std::cout << "Rhombus deleted" << std::endl;
}

Rhombus& Rhombus::operator=(const Rhombus& right) {

	if (this == &right) return *this;

	std::cout << "Rhombus copied" << std::endl;

	side_a = right.side_a;

	d1 = right.d1;

	d2 = right.d2;

	square = right.square;

	return *this;

}

Rhombus& Rhombus::operator++() {

	side_a++;

	d1++;

	d2++;

	return *this;

}

Rhombus operator+(const Rhombus& left, const Rhombus& right) {

	return Rhombus(left.side_a + right.side_a, left.d1 + right.d1, left.d2 + right.d2);

}

std::ostream& operator<<(std::ostream& os, const Rhombus& obj) {

	os << "a=" << obj.side_a << ", d1=" << obj.d1 << ", d2=" << obj.d2 << " , square=" << obj.square << std::endl;

	return os;

}

std::istream& operator>>(std::istream& is, Rhombus& obj) {

	is >> obj.side_a;

	is >> obj.d1;

	is >> obj.d2;

	obj.square = 0.5 * obj.d1 * obj.d2;

	return is;

}
