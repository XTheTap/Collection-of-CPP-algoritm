#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

template<typename T = int>
class Graph
{
private:
	T** adjMatrix; //make template z choose any type of date as way

	size_t count;
	
	void copy(const Graph<T>&);
public:

	//
	/*CONSTRUCTORS*/
	//

	explicit Graph(size_t = 0);
	Graph(const Graph<T>&);

	~Graph();

	//
	/*FUNCTIONS*/
	//


	void Clear();
	void CreateDirMat(std::ifstream&);
	void Dijkstra(size_t) const;
	std::vector<size_t> floydWarshallWay(size_t, size_t) const;
	void bellmanFord(size_t) const;

	//
	/*OPERATORS*/
	//

	template<typename T>
	friend std::ostream& operator<<(std::ostream&, const Graph<T>&);

	template<typename T>
	friend std::istream& operator>>(std::istream&, Graph<T>&);

	Graph<T>& operator=(const Graph<T>&);
};

template<typename T>
Graph<T>::Graph(size_t n)
	:count{ n }, adjMatrix{ new T * [n] {} }
{
	for (size_t i = 0; i < count; i++) 
		adjMatrix[i] = new T[count]{};
	
}

template<typename T>
Graph<T>::Graph(const Graph<T>& n)
{
	copy(n);
}

template<typename T>
Graph<T>::~Graph()
{
	Clear();
}

template<typename T>
void Graph<T>::Clear()
{
	for (size_t i = 0; i < count; i++)
		delete[] adjMatrix[i];
	
	delete[] adjMatrix;

	adjMatrix = nullptr;
}

template<typename T>
void Graph<T>::CreateDirMat(std::ifstream& in) //oriented suspended Graph 
{
	if (!in) return;

	if (adjMatrix) Clear();

	size_t i, j; T k;

	in >> count; //take a size of matr
	adjMatrix = new T * [count] {};

	for (size_t i = 0; i < count; i++) 
		adjMatrix[i] = new T[count]{};


	do
	{
		in >> i >> j >> k;
		adjMatrix[i - 1][j - 1] = k;
	} while (in);
}

template<typename T>
void Graph<T>::copy(const Graph<T>& n)
{
	count = n.count;
	adjMatrix = new T * [count] {};

	for (size_t i = 0; i < count; i++)
		adjMatrix[i] = new T[count]{};

	for (size_t i = 0; i < n.count; i++)
		for (size_t j = 0; j < n.count; j++)
			adjMatrix[i][j] = n.adjMatrix[i][j];
		
}

template<typename T>
void Graph<T>::Dijkstra(size_t vrtx) const //cout in function is pour code, but its necessary sacrifice to make normal 
{										// output without returning type data like list of stack or smth like this
	if (!adjMatrix || !count) return;

	if (vrtx < 1 || vrtx > count) return;
	
	bool* ready{ new bool[count] {} }; //bool array to check 
	size_t* weight{ new size_t[count]{} };//array from lenghts of shortest way (i+1)-vartex
	size_t* from{ new size_t[count]{} };//array of number past (i+1)-vartex
	for (size_t i = 0; i < count; i++) weight[i] = UINT_MAX; //make max to find shortest way 

	weight[vrtx - 1] = 0; //shortest way to start vertex, lol
	from[vrtx - 1] = 0; //number past from start vertex

	for (size_t i = 0; i < count - 1; i++)
	{
		size_t min = UINT_MAX; //to find min number
		size_t closest = 0;	//to notused vertex to shortest way 

		for (size_t i = 0; i < count; i++) //detour all vertex to find non processed vertex 
		{
			if (!ready[i] && weight[i] < min) //if not used find min
			{
				min = weight[i]; 
				closest = i;
			}
		}

		ready[closest] = true; //make min as readed

		for (size_t j = 0; j < count; j++) //detour all vertex
		{
			if (!ready[j] && adjMatrix[closest][j]) //if not used - use index of min by row 
			{
				if (min + adjMatrix[closest][j] < weight[j]) //if minimum + way of all row < that we calculated paster 
				{
					weight[j] = min + adjMatrix[closest][j]; //write a new write from this 
					from[j] = closest + 1; //write a way of this
				}
			}
		}
	}

	//
	/*OUTPUT*/
	//

	std::cout << "Кратчайший путь от " << vrtx << " вершины:\n\n";
	for (size_t i = 0; i < count; i++) //lenght if way
		std::cout << "К " << ' ' << i + 1 << "ой вершине: "  << weight[i] << "\n";
	std::cout << "\n";

	std::stack<size_t> st; 
	std::cout << "Путь из " << vrtx << " вершины:\n\n";
	for (size_t i = 0; i < count; i++)//the way 
	{
		std::cout << "К " << ' ' << i + 1 << "ой вершине: " << vrtx;
		for (size_t j = i; weight[j] != 0; j = from[j] - 1)//write the way to steck to reverse it
			st.push(j + 1); //ПУШ ЕГО

		while (!st.empty()) //just output of stack 
		{
			std::cout << " - " << st.top();
			st.pop();
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";

	
	delete[] ready;
	delete[] weight;
	delete[] from;
}


template<class T>
std::vector<size_t> Graph<T>::floydWarshallWay(size_t from, size_t to) const
{
	if (!adjMatrix || !count) return {};

	size_t** weightMtx = new size_t * [count] {};
	size_t** wayMtx = new size_t * [count] {};

	for (size_t i = 0; i < count; i++)
	{
		weightMtx[i] = new size_t[count] {};
		wayMtx[i] = new size_t[count] {};
		
		for (size_t j = 0; j < count; j++) {
			 weightMtx[i][j] = adjMatrix[i][j] ? adjMatrix[i][j] : INT_MAX;
			 wayMtx[i][j] = weightMtx[i][j] ? j : INT_MAX;
		}
	}

	for (size_t k = 0; k < count; k++)
		for (size_t i = 0; i < count; i++)
			for (size_t j = 0; j < count; j++)
				if (weightMtx[i][k] < INT_MAX && weightMtx[k][j] < INT_MAX)
					if (weightMtx[i][j] > weightMtx[i][k] + weightMtx[k][j])
					{
						weightMtx[i][j] = weightMtx[i][k] + weightMtx[k][j];
						wayMtx[i][j] = wayMtx[i][k];
					}
					

	for (size_t i = 0; i < count; i++)
		for (size_t j = 0; j < count; j++)
			if (weightMtx[i][j] == INT_MAX) 
				wayMtx[i][j] = weightMtx[i][j] = 0;



	from--; to--;

	std::cout << "Длинна пути: " << weightMtx[from][to] << "\n";

	if (wayMtx[from][to] == 0) { return {}; }

	std::vector<size_t> path = { from + 1};

	while (from != to)
	{
		from = wayMtx[from][to];
		path.push_back(from + 1);
	}
	

	return path;
}


template<class T>
inline void Graph<T>::bellmanFord(size_t v) const
{
	if (!adjMatrix || !count) return;
	if (v < 1 || v > count) return;

	size_t* weight{ new size_t[count]{} };
	size_t* from{ new size_t[count]{} };

	for (size_t i = 0; i < count; i++) weight[i] = UINT_MAX;

	weight[v - 1] = 0;

	for (size_t i = 0; i < count - 1; i++)
	{
		for (size_t i = 0; i < count; i++) //какого? 
		{
			for (size_t j = 0; j < count; j++)
			{
				if (adjMatrix[i][j] && weight[i] < UINT_MAX)
				{
					if (weight[j] > weight[i] + adjMatrix[i][j])
					{
						weight[j] = weight[i] + adjMatrix[i][j];
						from[j] = i + 1;
					}
				}
			}
		}
	}

	std::cout << "Shortest path from vertex\n" << v << ":\n";
	for (size_t i = 0; i < count; i++)
	{
		std::cout
			<< "Путь к: " << "\t" << i + 1 << ": "
			<< "\t" << weight[i] << "\n";
	}
	std::cout << "\n";
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Graph<T>& gr)
{
	for (size_t i = 0; i < gr.count; i++)
	{
		for (size_t j = 0; j < gr.count; j++)
		{
			out << gr.adjMatrix[i][j] << '\t';
		}
		out << "\n";
	}

	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Graph<T>& gr)
{
	if (1 > gr.count) return in;

	size_t i, j; T k;
	
	in >> i >> j >> k;
	gr.adjMatrix[i - 1][j - 1] = k;

	return in;
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& equt)
{
	copy(equt);
	return *this;
}
