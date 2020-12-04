#include "Collection.h"
#include <iostream>

using namespace std;

int main()
{
	system("chcp 1251 & cls");

	Stack<int> te;
	stack<int> tl;
	
	for (size_t i = 0; i < 10; i++)
	{
		te.Push(i);
		tl.push(i);
	}

	for (size_t i = 0; i < 10; i++)
	{
		cout << te.Top() << " " << tl.top() << endl;
		te.Pop();
		tl.pop();
	}


}