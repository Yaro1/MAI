#include "stdafx.h"
#include "Rhombus.h"
#include <iostream>
#include <cmath>

Rhombus::Rhombus() : Rhombus(0, 0, 0) {
}

Rhombus::Rhombus(size_t i, size_t j, size_t k) : side_a(i), d1(j), d2(k) {
	std::cout << "Rhombus created: " << side_a << ", " << d1 << ", " << d2 << std::endl;
}

Rhombus::Rhombus(std::istream &is) {
	std::cout << "Enter side, first diagonal, second diagonal" << std::endl;
	is >> side_a;
	is >> d1;
	is >> d2;
}

Rhombus::Rhombus(const Rhombus& orig) {
	std::cout << "Rhombus copy created" << std::endl;
	side_a = orig.side_a;
	d1 = orig.d1;
	d2 = orig.d2;
}

double Rhombus::Square() {
	return 0.5 * d1 * d2;

}

void Rhombus::Print() {
	std::cout << "Side=" << side_a << ", First diagonal=" << d1 << ", Second diagonal=" << d2 << std::endl;
}

Rhombus::~Rhombus() {
	std::cout << "Rhombus deleted" << std::endl;
}
