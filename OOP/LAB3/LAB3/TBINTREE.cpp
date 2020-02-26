#include "stdafx.h"
#include "TBINTREE.h"

template <class T>  TBinTree <T>::TBinTree() : head(nullptr) {

}

template <class T> TBinTree <T> ::TBinTree(const TBinTree <T> & orig) {

	head = orig.head;

}

template <class T> bool TBinTree <T> :: empty() {

	return head == nullptr;

}

template <class T> std::ostream& operator<<(std::ostream& os, const TBinTree <T> & tree) { // вывод дерева
	if (tree.head == nullptr) return os;
	os << *tree.head;
	return os;
}

template <class T> void TBinTree <T> ::print_Tree(std::shared_ptr <BinTreeItem <T> > p, int level)
{
	if (p)
	{
		print_Tree(p->leftson, level + 1);
		for (int i = 0; i< level; i++) std::cout << "   ";

		if (p->hexagon.Square() != 0)
			p->hexagon.Print();

		else if (p->pentagon.Square() != 0)
			p->pentagon.Print();

		else if (p->rhomb.Square() != 0)
			p->rhomb.Print();

		print_Tree(p->rightson, level + 1);
	}
}

template <class T> void TBinTree<T> ::push(std::shared_ptr <T> &&item) { // добавление элемента в дерево

	std::shared_ptr <BinTreeItem <T>> other(new BinTreeItem(T));
	std::shared_ptr <BinTreeItem <T> > nowelem = this->head;
	double square;
	if (nowelem == nullptr)
	{
		nowelem = other;
		head = nowelem;
	}
	else
		while (1)
		{
			if (square < other->item.Square())
			{
				if (nowelem->GetRightSon() == nullptr)
				{
					nowelem->rightson = other;
					break;
				}
				nowelem = nowelem->GetRightSon();
			}
			else if (square > other->item.Square())
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


template <class T> std::shared_ptr <BinTreeItem <T> > TBinTree <T> :: FindMin(std::shared_ptr <BinTreeItem <T>> elem)
{
	if (elem->leftson == nullptr)
		return elem;
	else
		return FindMin(elem->leftson);
}


template <class T> void TBinTree <T> ::pop(double square) {
	std::shared_ptr <BinTreeItem <T> > nowelem = head;

	while (1)
	{
		if (nowelem->item.Square() == square)
		{
			std::shared_ptr <BinTreeItem <T> > delelem = FindMin(nowelem->rightson);
			nowelem->rhomb = delelem->rhomb;
			nowelem->rightson = nullptr;
			break;
		}
		else if (nowelem->item.Square() < square)
		{
			if (nowelem->GetRightSon() == nullptr)
			{
				std::cout << "Element not find" << std::endl;
				break;
			}
			nowelem = nowelem->GetRightSon();
		}
		else if (nowelem->item.Square() > square)
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

template <class T> TBinTree <T> ::~TBinTree() {
}