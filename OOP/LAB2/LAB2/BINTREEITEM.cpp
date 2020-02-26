#include "stdafx.h"
#include "TBINTREEITEM.h"

#include <iostream>

BinTreeItem::BinTreeItem(const Rhombus& rhomb) {

	this->rhomb = rhomb;

	this->leftson = nullptr;
	this->rightson = nullptr;

	std::cout << "Stack item: created" << std::endl;

}

BinTreeItem::BinTreeItem(const BinTreeItem& orig) {

	this->rhomb = orig.rhomb;

	this->leftson = orig.leftson;
	this->rightson = orig.rightson;

	std::cout << "Stack item: copied" << std::endl;

}


Rhombus BinTreeItem::GetRhombus() const {

	return this->rhomb;

}

BinTreeItem* BinTreeItem::GetLeftSon() { 

	return this->leftson;

}

BinTreeItem* BinTreeItem::GetRightSon() { 

	return this->rightson;

}

BinTreeItem::~BinTreeItem() {

	std::cout << "Stack item: deleted" << std::endl;

	if(leftson != nullptr)
		delete leftson;
	if(rightson != nullptr)
		delete rightson;

}

std::ostream& operator<<(std::ostream& os, const BinTreeItem& obj) {
		
	if (obj.leftson != nullptr) os << *obj.leftson;
		os << "[" << obj.rhomb << "]" << std::endl;
	if (obj.rightson != nullptr) os << *obj.rightson;
	return os;
}