#ifndef Rhombus_H
#define	Rhombus_H
#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Rhombus : public Figure {
public:
	Rhombus();
	Rhombus(std::istream &is);
	Rhombus(size_t i, size_t j, size_t k);
	Rhombus(const Rhombus& orig);

	double Square() override;
	void   Print() override;

	Rhombus& operator++();

	friend Rhombus operator+(const Rhombus& left, const Rhombus& right);

	friend std::ostream& operator<<(std::ostream& os, const Rhombus& obj);

	friend std::istream& operator>>(std::istream& is, Rhombus& obj);

	Rhombus& operator=(const Rhombus& right);

	virtual ~Rhombus();

private:
	double side_a;
	double d1;
	double d2;
	double square;
};

#endif	/* Rhombus_H */

