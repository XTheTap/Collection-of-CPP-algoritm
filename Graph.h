#pragma once
#include <iostream>
#include <fstream>
#include <stack>

template<typename T = int>
class Graph
{
private:
	T** adj_matrix; //make template that we can choose any type of date as way
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
	void floydWarshall() const;

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
	:count{ n }, adj_matrix{ new T * [n] {} }
{
	for (size_t i = 0; i < count; i++)
		adj_matrix[i] = new T[count]{};	
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
		delete[] adj_matrix[i];

	delete[] adj_matrix;

	adj_matrix = nullptr;
}

template<typename T>
void Graph<T>::CreateDirMat(std::ifstream& in) //oriented suspended Graph 
{
	if (!in) return;

	if (adj_matrix) Clear();

	size_t i, j; T k;

	in >> count; //take a size of matr
	adj_matrix = new T * [count] {};

	for (size_t i = 0; i < count; i++) //create a matrix
		adj_matrix[i] = new T[count]{};

	do
	{
		in >> i >> j >> k;
		adj_matrix[i - 1][j - 1] = k;
	} while (in);
}

template<typename T>
void Graph<T>::copy(const Graph<T>& n)
{
	count = n.count;
	adj_matrix = new T * [count] {};

	for (size_t i = 0; i < count; i++)
		adj_matrix[i] = new T[count]{};

	for (size_t i = 0; i < n.count; i++)
		for (size_t j = 0; j < n.count; j++)
			adj_matrix[i][j] = n.adj_matrix[i][j];
		
}

template<typename T>
void Graph<T>::Dijkstra(size_t vrtx) const //cout in function is pour code, but its necessary sacrifice to make normal 
{										// output without returning type data like list of stack or smth like this
	if (!adj_matrix || !count) return;

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
			if (!ready[j] && adj_matrix[closest][j]) //if not used - use index of min by row 
			{
				if (min + adj_matrix[closest][j] < weight[j]) //if minimum + way of all row < that we calculated paster 
				{
					weight[j] = min + adj_matrix[closest][j]; //write a new write from this 
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
void Graph<T>::floydWarshall() const
{
	if (!adj_matrix || !count) return;

	int** weight_mtx = new int* [count] {};

	for (size_t i = 0; i < count; i++)
	{
		weight_mtx[i] = new int[count] {};
		for (size_t j = 0; j < count; j++)
		{
			if (i == j)
			{
				weight_mtx[i][j] = 0;
				continue;
			}
			weight_mtx[i][j] = adj_matrix[i][j] ? adj_matrix[i][j] : INT_MAX;
		}
	}

	for (size_t i = 0; i < count; i++)
		for (size_t j = 0; j < count; j++)
			for (size_t k = 0; k < count; k++)
				if (weight_mtx[j][i] < INT_MAX && weight_mtx[i][k] < INT_MAX)
					if (weight_mtx[j][k] > weight_mtx[j][i] + weight_mtx[i][k])
						weight_mtx[j][k] = weight_mtx[j][i] + weight_mtx[i][k];
	

	for (size_t i = 0; i < count; i++)
		for (size_t j = 0; j < count; j++)
			if (weight_mtx[i][j] == INT_MAX) weight_mtx[i][j] = 0;

	std::cout << "От любой точки до любой кратчайший путь:\n";
	for (size_t i = 0; i < count; i++)
	{
		for (size_t j = 0; j < count; j++)
			std::cout << "\t" << weight_mtx[i][j];
		std::cout << "\n";
	}

	std::cout << "\n";
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Graph<T>& gr)
{
	for (size_t i = 0; i < gr.count; i++)
	{
		for (size_t j = 0; j < gr.count; j++)
		{
			out << gr.adj_matrix[i][j] << '\t';
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
	gr.adj_matrix[i - 1][j - 1] = k;

	return in;
}

template<typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& equt)
{
	copy(equt);
	return *this;
}
