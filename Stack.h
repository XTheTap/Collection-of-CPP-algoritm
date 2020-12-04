#include "List.h"

template <typename T>
class Stack : private LinkedList<T> //Stack is just illusion.
{
private:
	//top = first 
	//ignore last, he is bad man
public:

	//
	/*CONSTRUCTORS*/
	//

	Stack() : LinkedList<T>::LinkedList() { };

	//
	/*FUNCTIONS*/
	//

	void Push(const T&);
	void Pop();
	T Top();

	//
	/*OPERATORS*/
	//
	
};

template<typename T>
void Stack<T>::Push(const T& k)
{
	LinkedList<T>::prepend(k);
}

template<typename T>
void Stack<T>::Pop()
{
	LinkedList<T>::remove(LinkedList<T>::first);
}

template<typename T>
T Stack<T>::Top()
{
	return LinkedList<T>::first->data;
}