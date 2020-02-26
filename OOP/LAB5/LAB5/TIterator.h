#define	TITERATOR_H
#include <memory>
#include <iostream>

template <class T, class A>
class TIterator
{
public:

	TIterator(std::shared_ptr<T> n) {

		node_ptr = n;
	}

	std::shared_ptr <A> operator * () {
		return node_ptr->GetItem();
	}

	std::shared_ptr<A> operator -> () {
		return node_ptr->GetItem();
	}

	void operator -- ()
	{
		node_ptr = node_ptr->GetLeftSon();
	}
	
	void operator ++ ()
	{
		node_ptr = node_ptr->GetRightSon();
	}
	

	TIterator operator ++ (int) {
		TIterator iter(*this);
		++(*this);
		return iter;
	}


	bool operator == (TIterator const& i) {
		return node_ptr == i.node_ptr;
	}

	bool operator != (TIterator const& i) {
		return !(*this == i);
	}

	std::shared_ptr <T> node_ptr;
private:

};
