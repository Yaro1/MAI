#ifndef TBINTREE_H

#define TBINTREE_H

#include "Rhombus.h"

#include "TBINTREEITEM.h"

class TBinTree {

public:

	TBinTree();

	TBinTree(const TBinTree& orig);

	void push(Rhombus &&rhombus);

	BinTreeItem* FindMin(BinTreeItem * elem);

	bool empty();

	void pop(double square);

	friend std::ostream& operator<<(std::ostream& os, const TBinTree& stack);

	virtual ~TBinTree();

private:

	BinTreeItem * head;

};

#endif /* TBINTREE_H */
