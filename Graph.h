#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <queue>
#include <list>

using namespace std;

template<class T = int>
class Graph
{
	template<class T>
	friend ostream& operator<<(ostream&, const Graph<T>&);

	T** adj_matrix;
	size_t count;
	void clear();
	void copy(const Graph<T>&);
	void move(Graph<T>&& n);

public:
	explicit Graph(size_t = 0);
	Graph(const Graph<T>& n);
	Graph(Graph<T>&& n);
	void create_mtx(ifstream);
	void dft(size_t) const;
	void bft(size_t) const;

	~Graph();
};

template<class T>
Graph<T>::Graph(size_t n)
	:count{ n }, adj_matrix{ new T * [n] {} }
{
	cout << "constructor...\n";
	for (size_t i = 0; i < count; i++)
	{
		adj_matrix[i] = new T[count]{};
	}
}

template<class T>
Graph<T>::Graph(const Graph<T> &n)
{
	cout << "Copy constructor\n";
	copy(n);
}

template<class T>
Graph<T>::Graph(Graph<T> &&n)
{
	cout << "Move cinstructor";
	move(n);
}

template<class T>
void Graph<T>::clear()
{
	for (size_t i = 0; i < count; i++)
	{
		delete[] adj_matrix[i];
		cout << setw(4) << i;
	}
	cout << endl;
	delete[] adj_matrix;

	adj_matrix = nullptr;
}

template<class T>
void Graph<T>::copy(const Graph<T>& n)
{
	count = n.count;
	adj_matrix = new T * [count] {};

	for (size_t i = 0; i < count; i++)
	{
		adj_matrix[i] = new T[count]{};
	}

	for (size_t i = 0; i < n.count; i++)
	{
		for (size_t j = 0; j < n.count; j++)
		{
			adj_matrix[i][j] = n.adj_matrix[i][j];
		}
	}
}

template<class T>
void Graph<T>::move(Graph<T>&& n)
{
	count = n.count;
	adj_matrix = new T * [count] {};

	for (size_t i = 0; i < count; i++)
	{
		adj_matrix[i] = new T[count]{};
	}

	for (size_t i = 0; i < n.count; i++)
	{
		for (size_t j = 0; j < n.count; j++)
		{
			adj_matrix[i][j] = n.adj_matrix[i][j];
		}
	}
	
	n.clear();
}

template<class T>
Graph<T>::~Graph()
{
	clear();
}

template<class T>
void Graph<T>::create_mtx(ifstream in)
{
	if (adj_matrix) clear();

	size_t i, j;

	in >> count;
	adj_matrix = new T * [count] {};
	for (size_t i = 0; i < count; i++)
	{
		adj_matrix[i] = new T[count]{};
	}

	in >> i >> j;
	while (in)
	{
		adj_matrix[i - 1][j - 1] = adj_matrix[j - 1][i - 1] = 1;
		in >> i >> j;
	}
}

template<class T>
void Graph<T>::dft(size_t v) const
{
	if (!adj_matrix || !count) return;
	if (v < 1 || v > count)
	{
		cout << "Incorrect input...\n";
		return;
	}

	stack<size_t> st;
	bool* visited{ new bool[count] {} };
	st.push(v-1);
	visited[v - 1] = true;
	cout << setw(4) << v;

	bool pop{ true };
	while (!st.empty())
	{
		for (size_t i = 0; i < count; i++)
		{
			if (adj_matrix[st.top()][i] && !visited[i])
			{
				pop = false;
				st.push(i);
				visited[i] = true;
				cout << setw(4) << i + 1;
				break;
			}
		}
		if (pop) st.pop();
		pop = true;
	}
	delete[] visited;
	cout << endl;
}

template<class T>
void Graph<T>::bft(size_t v) const
{
	if (!adj_matrix || !count) return;
	if (v < 1 || v > count)
	{
		cout << "Incorrect input...\n";
		return;
	}
	
	queue <size_t> q;
	bool* visited{ new bool[count] {} };
	q.push(v - 1);
	visited[v - 1] = true;

	while (!q.empty())
	{
		for (size_t i = 0; i < count; i++)
		{
			if (adj_matrix[q.front()][i] && !visited[i])
			{
				q.push(i);
				visited[i] = true;
			}
		}

		cout << setw(4) << q.front() + 1;
		q.pop();
	}
	delete[] visited;
	cout << endl;
}

template<class T>
ostream& operator<<(ostream& out, const Graph<T>& gr)
{
	for (size_t i = 0; i < gr.count; i++)
	{
		for (size_t j = 0; j < gr.count; j++)
		{
			out << setw(4) << gr.adj_matrix[i][j];
		}
		out << endl;
	}
	return out;
}