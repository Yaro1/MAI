#ifndef Hexagon_H
#define	Hexagon_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Hexagon : public Figure {
public:
	Hexagon();
	Hexagon(std::istream &is);
	Hexagon(size_t i);
	Hexagon(const Hexagon& orig);

	double Square() override;
	void   Print() override;

	virtual ~Hexagon();
private:
	double side_a;
};

#endif	/* Hexagon_H */