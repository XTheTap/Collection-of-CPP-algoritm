#include "Collection.h"
#include <iostream>

using namespace std;

int main()
{
	system("chcp 1251 & cls");

	Graph<int> a;

	ifstream b("file1.txt");

	a.CreateDirMat(b);

	cout << a.fordFolkerson(1, 6);

	return 1;

	//size_t c, d;
	//cout << "Из ";
	//cin >> c;
	//cout << "В ";
	//cin >> d;

	//auto path = a.floydWarshallWay(c, d);
	//for (size_t i = 0; i < path.size() - 1; i++)
	//	std::cout << path[i] << " -> ";
	//std::cout << path[path.size() - 1] << '\n';

}