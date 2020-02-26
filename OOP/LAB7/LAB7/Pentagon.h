#ifndef Pentagon_H
#define	Pentagon_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Pentagon : public Figure {
public:
	Pentagon();
	Pentagon(std::istream &is);
	Pentagon(size_t i);
	Pentagon(Pentagon& orig);

	friend std::ostream& operator<<(std::ostream& os, const Pentagon& obj);

	double Square() override;
	void   Print() override;

	virtual ~Pentagon();
private:
	double side_a;
	double square;
};

#endif	/* Pentagon_H */

