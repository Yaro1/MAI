#ifndef BINTREE_H

#define BINTREE_H

#include "Rhombus.h"

#include "Pentagon.h"

#include "Hexagon.h"

#include <memory>

template <class T> class BinTreeItem {

public:

	BinTreeItem(const std::shared_ptr <T> & item);

	template <class A>  friend std::ostream& operator<<(std::ostream& os, const BinTreeItem <A> & obj);

	std::shared_ptr <BinTreeItem <T> > GetRightSon();

	std::shared_ptr <BinTreeItem <T> > GetLeftSon();

	std::shared_ptr <T> GetItem() const;

	virtual ~BinTreeItem();
	

	std::shared_ptr <T> item;
	std::shared_ptr <BinTreeItem <T> > leftson;
	std::shared_ptr <BinTreeItem <T> > rightson;
private:
};

#endif /* BINTREE_H */
