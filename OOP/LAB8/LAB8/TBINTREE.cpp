#include "stdafx.h"
#include "TBINTREE.h"
#include "TIterator.h"



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

		BinTreeItem <Figure> *a1 = p.get();
		Figure * a2 = a1->item.get();
		double square = a2->Square();

		if (p->item->Square() != 0)
			p->item->Print();

		print_Tree(p->rightson, level + 1);
	}
}

template <class T> void TBinTree<T> ::push(std::shared_ptr <T> &&item) { // добавление элемента в дерево

	std::shared_ptr <BinTreeItem <T>> other(new BinTreeItem <T>(item));

	std::shared_ptr <BinTreeItem <T> > nowelem = this->head;

	BinTreeItem <Figure> *b1 = other.get();
	Figure * b2 = b1->item.get();
	double square_now = b2->Square();

	if (nowelem == nullptr)
	{
		head = other;
	}
	else
		while (1)
		{
			BinTreeItem <Figure> *a1 = nowelem.get();
			Figure * a2 = a1->item.get();
			double square = a2->Square();

			if (square < square_now)
			{
				if (nowelem->GetRightSon() == nullptr)
				{
					nowelem->rightson = other;
					other->father = nowelem;
					break;
				}
				nowelem = nowelem->GetRightSon();
			}
			else if (square > square_now)
			{
				if (nowelem->GetLeftSon() == nullptr)
				{
					nowelem->leftson = other;
					other->father = nowelem;
					break;
				}
				nowelem = nowelem->GetLeftSon();
			}
		}

}


template <class T> std::shared_ptr <BinTreeItem <T> > TBinTree <T> :: FindMin(std::shared_ptr <BinTreeItem <T>> elem)
{
	if (elem == nullptr)
		return nullptr;
	if (elem->leftson == nullptr)
		return elem;
	else
		return FindMin(elem->leftson);
}
/*
template <class T> void TBinTree <T> ::pop(double square, std::shared_ptr <BinTreeItem <T>> nowelem) {
	BinTreeItem <T> a1 = nowelem.get();
	T * a2 = a1->item.get();
	double squareFind = a2->Square();
	if (squareFind == square)
	{
		std::shared_ptr <BinTreeItem <T> > delelem = FindMin(nowelem->rightson);
		if()
	}
	else if (squareFind < square)
	{
		if (nowelem->GetRightSon() == nullptr)
		{
			std::cout << "Element not find" << std::endl;
			return NULL;
		}
		pop(square, nowelem->rightson);
	}
	else if (squareFind > square)
	{
		if (nowelem->GetLeftSon() == nullptr)
		{
			std::cout << "Element not find" << std::endl;
			return NULL;
		}
		pop(square, nowelem->leftson);
	}
}
*/

template <class T> std::shared_ptr <BinTreeItem <T>> TBinTree <T> ::pop(std::shared_ptr <BinTreeItem <T>> nowelem, double square) {
	if (nowelem == nullptr)
		return nowelem;
	if (square < nowelem->item->Square())
	{
		nowelem->leftson = pop(nowelem->leftson, square);
	}
	else if (square > nowelem->item->Square())
	{
		nowelem->rightson = pop(nowelem->rightson, square);
	}
	else if (nowelem->leftson != nullptr && nowelem->rightson != nullptr)
	{
		std::shared_ptr <BinTreeItem <T>> promelem = FindMin(nowelem->rightson);
		nowelem->item = promelem->item;
		std::shared_ptr <BinTreeItem <T>> father_prom = promelem->father;
		if (promelem->item->Square() > father_prom->item->Square())
			father_prom->rightson = nullptr;
		else
			father_prom->leftson = nullptr;

		//nowelem->item = promelem->item;
		//nowelem->rightson = pop(nowelem->rightson, promelem->item->Square());
	}
	else
	{
		if (nowelem->leftson != nullptr)
			nowelem = nowelem->leftson;
		else
			nowelem = nowelem->rightson;
	}
	return nowelem;
}

template <class T> TBinTree <T> ::~TBinTree() {
}

#include "Figure.h"
template class TBinTree<Figure>;
template std::ostream& operator<<(std::ostream& os, const TBinTree<Figure>& tree);