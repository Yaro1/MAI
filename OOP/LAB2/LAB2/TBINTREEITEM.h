#ifndef BINTREE_H

#define BINTREE_H

#include "Rhombus.h"

class BinTreeItem {

public:

	BinTreeItem(const Rhombus& rhombus);

	BinTreeItem(const  BinTreeItem& orig);

	friend std::ostream& operator<<(std::ostream& os, const BinTreeItem& obj);

	BinTreeItem* GetRightSon();

	BinTreeItem* GetLeftSon();

	Rhombus GetRhombus() const;

	virtual ~BinTreeItem();

	Rhombus rhomb;
	BinTreeItem *leftson;
	BinTreeItem *rightson;
private:
	/*Rhombus rhomb;
	BinTreeItem *leftson;
	BinTreeItem *rightson;*/

};

#endif /* BINTREE_H */
