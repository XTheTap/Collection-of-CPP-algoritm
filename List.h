#pragma once
#include <iostream>

template<typename T>
struct Node {
	T data;//input data, lol
	Node<T>* next; //pointer to the next link of list 

	//
	/*CONSTRUCTORS*/
	//

	Node()
		: data{}, next {}
	{}

	Node(const T& v, Node<T>* node = nullptr)
		:data{ v }, next{ node }
	{}
};

template <typename T>
class LinkedList
{
private:
	Node<T>* first; //pointer to the 1st element of the list
	Node<T>* last; //pointer to the last element of the list 
	size_t lenght; //actual lenght of list
public:

	//
	/*CONSTRUCTORS*/
	//

	LinkedList() noexcept; //clear cinstructor
	LinkedList(const T&) noexcept; //1-element constructor
	LinkedList(const LinkedList<T>&) noexcept; //copy constructor 
	LinkedList(LinkedList<T>&&) noexcept; //Right lavue construcotr
	LinkedList(const LinkedList<T>&&) noexcept; // по noexcept тоже

	//
	/*OPERATORS*/
	//

	const LinkedList<T>& operator=(const LinkedList<T>&); //operator appropriation

	friend std::ostream& operator<<(std::ostream& ot, const LinkedList<T>& l) //operator of output 
	{		//its just doesent work if it bounce of class
		Node<T>* it{ l.first };
		while (it)
		{
			ot << "	" << it->data;
			it = it->next;
		}
		ot << '\n';
		return ot;
	}

	~LinkedList(); //destructor, lol

	//
	/*FUNCTIONS*/
	//

	Node<T>* prepend(const T&); //add to start of list
	Node<T>* apend(const T&); //add to end of list
	Node<T>* insertAfter(const T& , const T&); //add element after chousen element
	Node<T>* insertAfter(Node<T>*, const T&); //add element after chousen link
	void remove(const T&);

	Node<T>* beg() const { return first; };
	Node<T>* end() const { return last; };
	Node<T>* find(const T&) const;

	bool isEmpty() const { return first == nullptr; }

	void clear();
	void copy(const LinkedList<T>);
};

template <typename T>
LinkedList<T>::LinkedList() noexcept
	:first{}, last{}, lenght{}
{}

template <typename T>
LinkedList<T>::LinkedList(const T& it) noexcept
	: first{ new Node<T>{it} }, last{ first }, lenght{ 1 }
{}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& B) noexcept
{
	if (!B.isEmpty())
	{
		lenght = B.lenght;
		//copy first element 
		first = new Node<T>{ B.first->data };

		//copy next elements
		Node<T>* pB{ B.first->next };
		Node<T>* pA{ first };
		while (pB)
		{
			pA->next = new Node<T>{ pB->data };
			pA = pA->next;
			pB = pB->next;
		}
		last = pA;
		pA = nullptr;
		pB = nullptr;
	}
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& B) noexcept
{
	first = B.first;
	last = B.last;
	lenght = B.lenght;
	B.first = B.last = nullptr;
	B.lenght = 0;
}

template<typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& B)
{
	if (this != &B)
	{
		clear();

		if (!B.isEmpty())
		{
			lenght = B.lenght;
			Node<T>* ptrB{ B.first };
			first = new Node<T>{ ptrB->data };
			Node<T>* ptrA{ first };
			ptrB = ptrB->next;
			while (ptrB)
			{
				ptrA->next = new Node<T>{ ptrB->data };
				ptrB = ptrB->next;
				ptrA = ptrA->next;
			}
			last = ptrA;
			ptrA = nullptr;
		}
	}

	return *this;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	Node<T>* del{ first };
	while (first)
	{
		del = first;
		first = first->next;
		delete del;
	}
	last = nullptr;
	lenght = 0;
}

template<typename T>
Node<T>* LinkedList<T>::insertAfter(Node<T>* node, const T& d)
{
	if (node)
	{
		node->next = new Node<T>{ d, node->next };
		if (node == last)
			last = node->next;
		++lenght;
		return node->next;
	}
	return nullptr;
}

template<typename T>
Node<T>* LinkedList<T>::insertAfter(const T& d, const T& n)
{
	insertAfter(find(d), n);
	return nullptr;
}

template<typename T>
Node<T>* LinkedList<T>::prepend(const T& it)
{
	if (isEmpty())
		first = last = new Node<T>{ it };
	else
		first = new Node<T>{ it, first };
	lenght++;
	return first;
}

template<typename T>
Node<T>* LinkedList<T>::apend(const T& it)
{
	if (isEmpty())
		first = last = new Node<T>{ it };
	else
		last = last->next = new Node<T>{ it };
	lenght++;
	return last;
}


template<typename T>
void LinkedList<T>::remove(const T& d)
{
	Node<T>* toDel{ find(d) };
	if (!toDel) return;
	if (toDel == first)
	{
		first = first->next;
		if (toDel == last)	last = nullptr;
	}
	else
	{
		Node<T>* trail{ first };
		while (trail && trail->next != toDel)
		{
			trail = trail->next;
		}
		trail->next = toDel->next;
		if (toDel == last)
			last = trail;
	}
	delete toDel;
	--lenght;
}

template<typename T>
Node<T>* LinkedList<T>::find(const T& d) const
{
	Node<T>* target{ first };
	while (target && target->data != d)
		target = target->next;
	return target;
}

template<typename T>
void LinkedList<T>::clear()
{
	Node<T>* del{ first };
	while (first)
	{
		del = first;
		first = first->next;
		delete del;
	}
	last = nullptr;
	lenght = 0;
}

template<typename T>
void LinkedList<T>::copy(const LinkedList<T> B)
{
	if (!B.isEmpty())
	{
		lenght = B.lenght;
		Node<T>* ptrB{ B.first };
		first = new Node<T>{ ptrB->data };
		Node<T>* ptrA{ first };

		ptrB = ptrB->next;
		while (ptrB)
		{
			ptrA->next = new Node<T>{ ptrB->data };
			ptrB = ptrB->next;
			ptrA = ptrA->next;
		}
		last = ptrA;
		ptrA = nullptr;
	}
}

