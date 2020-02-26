#include "stdafx.h"
#include "TBINTREEITEM.h"

#include <iostream>

template <class T> BinTreeItem <T> ::BinTreeItem(const std::shared_ptr <T> & item) {

	this->item = item;
	this->leftson = nullptr;
	this->rightson = nullptr;

	std::cout << "Stack item: created" << std::endl;

}


template <class T> std::shared_ptr <T>  BinTreeItem <T> :: GetItem() const {
	return this->item;
}

template <class T> std::shared_ptr<BinTreeItem <T>> BinTreeItem <T> :: GetLeftSon() {

	return this->leftson;

}

template <class T> std::shared_ptr<BinTreeItem <T>> BinTreeItem <T> :: GetRightSon() {

	return this->rightson;

}

template <class T> BinTreeItem <T> :: ~BinTreeItem() {

	std::cout << "Stack item: deleted" << std::endl;
}

template <class A> std::ostream& operator<<(std::ostream& os, const BinTreeItem <A>& obj) {
		
	/*if (obj.leftson != nullptr) os << *obj.leftson;
		os << "[" << obj.rhomb << "]" << std::endl;
	if (obj.rightson != nullptr) os << *obj.rightson;*/
	return os;
}


#include "Figure.h"
template class BinTreeItem<Figure>;
template std::ostream& operator<<(std::ostream& os, const BinTreeItem<Figure>& obj);