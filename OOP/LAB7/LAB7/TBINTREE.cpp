#include "stdafx.h"
#include "TBINTREE.h"
#include "TIterator.h"


#define MAX 5



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
		for (int i = 0; i < p->count; i++)
		{
			Figure * a2 = a1->item[i].get();
			double square = a2->Square();

			if (p->item[i]->Square() != 0)
				p->item[i]->Print();
		}
		std::cout << std::endl << std::endl;
		print_Tree(p->rightson, level + 1);
	}
}

template <class T> void TBinTree<T> ::push(std::shared_ptr <T> &&item) { // добавление элемента в дерево
	if (head == nullptr)
	{
		std::shared_ptr <BinTreeItem <T>> shoulder(new BinTreeItem <T>(item));
		head = shoulder;
		return;
	}
	std::shared_ptr <BinTreeItem <T> > p = head;
	while (1)
	{
		if (p->count < MAX)
		{
			if (p->count == 0)
				p->item[p->count] = item;
			else
				for (int i = 0; i < p->count; i++)
					if (p->item[i]->Square() >= item->Square())
					{
						for (int j = p->count; j > i; j--)
							p->item[j] = p->item[j - 1];
						p->item[i] = item;
						p->count++;
						return;
					}
			p->item[p->count] = item;
			p->count++;
			return;

		}
		if (p->leftson == NULL)
		{
			std::shared_ptr <BinTreeItem <T>> left(new BinTreeItem <T>(item));
			p->leftson = left;
			return;
		}
		if (p->leftson->count < MAX)
		{
			if (p->leftson->count == 0)
				p->leftson->item[p->leftson->count] = item;
			else
				for (int i = 0; i < p->leftson->count; i++)
					if (p->leftson->item[i]->Square() >= item->Square())
					{
						for (int j = p->leftson->count + 1; j > i; j--)
							p->leftson->item[j] = p->leftson->item[j - 1];
						p->leftson->item[i] = item;
						p->leftson->count++;
						return;
					}
			p->leftson->item[p->leftson->count] = item;
			p->leftson->count++;
			return;
		}
		if (p->rightson == NULL)
		{
			std::shared_ptr <BinTreeItem <T>> right (new BinTreeItem <T>(item));
			p->rightson = right;
			return;
		}
		if (p->rightson->count < MAX)
		{
			if (p->rightson->count == 0)
				p->rightson->item[p->rightson->count] = item;
			else
				for (int i = 0; i < p->rightson->count; i++)
					if (p->rightson->item[i]->Square() >= item->Square())
					{
						for (int j = p->rightson->count + 1; j > i; j--)
							p->rightson->item[j] = p->rightson->item[j - 1];
						p->rightson->item[i] = item;
						p->rightson->count++;
						return;
					}
			p->rightson->item[p->rightson->count] = item;
			p->rightson->count++;
			break;
		}
		else
		{

			if (item->Square() > 10 == 0)
				p = p->rightson;
			else
				p = p->leftson;
		}
		
	}

	return;
}

template <class T> std::shared_ptr <BinTreeItem <T>> TBinTree <T> ::pop(std::shared_ptr <BinTreeItem <T>> nowelem, double square) {
	
	if (nowelem == nullptr)
		return nowelem;
	for (int i = 0; i < nowelem->count; i++)
	{
		if (nowelem->item[i]->Square() == square)
		{
			for (int j = i; j < MAX - 1; j++)
			{
				nowelem->item[j] = nowelem->item[j + 1];
			}
			nowelem->item[MAX - 1] = nullptr;
			nowelem->count--;
			if (nowelem->count == 0)
			{
				nowelem->rightson->leftson = nowelem->leftson;
				nowelem = nowelem->rightson;
			}
			return nowelem;
		}
	}
	nowelem->leftson = pop(nowelem->leftson, square);
	nowelem->rightson = pop(nowelem->rightson, square);
	return nowelem;
}

template <class T> TBinTree <T> ::~TBinTree() {
}

#include "Figure.h"
template class TBinTree<Figure>;
template std::ostream& operator<<(std::ostream& os, const TBinTree<Figure>& tree);