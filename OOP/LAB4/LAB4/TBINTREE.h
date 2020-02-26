#ifndef TBINTREE_H

#define TBINTREE_H

#include "Rhombus.h"
#include "Hexagon.h"
#include "Pentagon.h"
#include <memory>

#include "TBINTREEITEM.h"

template <class T> class TBinTree {

public:

	TBinTree();

	TBinTree(const TBinTree <T> & orig);

	void push(std::shared_ptr <T>  &&item);

	std::shared_ptr <BinTreeItem <T> > FindMin(std::shared_ptr <BinTreeItem <T> > elem);

	bool empty();

	std::shared_ptr <BinTreeItem <T>> pop(std::shared_ptr <BinTreeItem <T>> nowelem, double square);

	template <class A> friend std::ostream& operator<<(std::ostream& os, const TBinTree <A> & stack);

	void print_Tree(std::shared_ptr <BinTreeItem <T> > p, int level);

	virtual ~TBinTree();

	std::shared_ptr <BinTreeItem <T> > head;
private:

};

#endif /* TBINTREE_H */
