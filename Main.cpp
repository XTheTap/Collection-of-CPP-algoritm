#include "Collection.h"
#include <iostream>

using namespace std;

int main()
{
	LinkedList<double> ost;
	
	LinkedList<double> tost;
	
	for (size_t i = 0; i < 10; i++)
	{
		tost.apend(i);
	}

	ost = tost;
	
	cout << ost;

	ost.insertAfter(2, 3);

	cout << ost;

}