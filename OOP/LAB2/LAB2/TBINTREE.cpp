#include "stdafx.h"
#include "TBINTREE.h"

TBinTree::TBinTree() : head(nullptr) {

}

TBinTree::TBinTree(const TBinTree& orig) {

	head = orig.head;

}

bool TBinTree::empty() {

	return head == nullptr;

}

std::ostream& operator<<(std::ostream& os, const TBinTree& tree) { // вывод дерева
	if (tree.head == nullptr) return os;
	os << *tree.head;
	return os;
}

void TBinTree::push(Rhombus &&rhombus) { // добавление элемента в дерево

	BinTreeItem *other = new BinTreeItem(rhombus);
	BinTreeItem *nowelem = this->head;
	if (nowelem == nullptr)
	{
		nowelem = other;
		head = nowelem;
	}
	else
		while (1)
		{
			if (nowelem->rhomb.Square() < other->rhomb.Square())
			{
				if (nowelem->GetRightSon() == nullptr)
				{
					nowelem->rightson = other;
					break;
				}
				nowelem = nowelem->GetRightSon();
			}
			else if (nowelem->rhomb.Square() > other->rhomb.Square())
			{
				if (nowelem->GetLeftSon() == nullptr)
				{
					nowelem->leftson = other;
					break;
				}
				nowelem = nowelem->GetLeftSon();
			}
		}

}

BinTreeItem * TBinTree::FindMin(BinTreeItem * elem)
{
	if (elem->leftson == nullptr)
		return elem;
	else
		return FindMin(elem->leftson);
}


void TBinTree::pop(double square) {
	BinTreeItem *nowelem = head;

	while (1)
	{
		if (nowelem->rhomb.Square() == square)
		{
			BinTreeItem *delelem = FindMin(nowelem->rightson);
			nowelem->rhomb = delelem->rhomb;
			delete delelem;
			nowelem->rightson = nullptr;
			break;
		}
		else if (nowelem->rhomb.Square() < square)
		{
			if (nowelem->GetRightSon() == nullptr)
			{
				std::cout << "Element not find" << std::endl;
				break;
			}
			nowelem = nowelem->GetRightSon();
		}
		else if (nowelem->rhomb.Square() > square)
		{
			if (nowelem->GetLeftSon() == nullptr)
			{
				std::cout << "Element not find" << std::endl;
				break;
			}
			nowelem = nowelem->GetLeftSon();
		}
	}

}

TBinTree::~TBinTree() {

	delete head;

}