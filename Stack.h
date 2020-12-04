#include "List.h"

template <typename T>
class Stack : public LinkedList<T>
{
private:
	//top = first 
	//ignore last, he is bad man
public:

	//
	/*CONSTRUCTORS*/
	//

	Stack() : LinkedList<T>::LinkedList() {};

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
Stack<T>::Stack() 
{
}

/*
template<typename T>
class Stack {
	T* storage;
	int top;
	int size;

public:
	Stack();
	explicit Stack(int);

	~Stack() { delete[] storage; };

	bool pop();
	bool push(const T&);
	void resize();
	T* peek() const;

	bool isFull() const { return top == size; }
	bool isEmpty() const { return top == 0; }
};

template<typename T>
Stack<T>::Stack()
	:storage{}, top{}, size{}
{}

template<typename T>
Stack<T>::Stack(int n)
	: storage{ new T[n]{} }, top{}, size{ n }
{}

template<typename T>
bool Stack<T>::pop() {
	if (!isEmpty()) {
		top--;
		return true;
	}
	return false;
}

template<typename T>
bool Stack<T>::push(const T& d) {
	if (!isFull()) {
		storage[top++] = d;
		return true;
	}
	else {
		resize();
		storage[top++] = d;
		return true;
	}

	return false;
}

template<typename T>
T* Stack<T>::peek() const {
	if (top > 0) return storage + top - 1;
	return nullptr;
}

template<typename T>
void Stack<T>::resize() {
	size = top + 5;
	T* arr{ new T[size]{} };
	for (size_t i = 0; i < top; i++) {
		arr[i] = std::move(storage[i]);
	}
	T* tmp = std::move(storage);
	storage = std::move(arr);

	delete[] tmp;
}

//ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ

bool isoper(char ch) {
	if (ch == '+' || ch == '-' || ch == '/' || ch == '*')
		return true;
	return false;
}

bool calculate(Stack<double>& st, char ch) {
	double rhv = *st.peek();
	st.pop();
	double lhv = *st.peek();
	st.pop();
	switch (ch) {
	case '+':
		st.push(rhv + lhv);
		break;
	case '-':
		st.push(lhv - rhv);
		break;
	case '*':
		st.push(rhv * lhv);
		break;
	case '/':
		if (rhv == 0) {
			cout << "Деление на 0 недопустимо " << endl;
			return false;
		}
		st.push(lhv / rhv);
		break;
	}

	return true;
}

int prior(char sb) {
	switch (sb) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

char* createPostfix() {
	Stack<char> stChar;
	char* postfExpr = new char[101]{};
	int ind{};
	char ch;

	cout << "Введите выражение: ";
	while ((ch = cin.peek()) != '\n') {
		if (ch == ' ') {
			getchar();
			continue;
		}

		if (isoper(ch)) {
			getchar();
			while (!stChar.isEmpty() && prior(*stChar.peek()) >= prior(ch)) {
				postfExpr[ind++] = *stChar.peek();
				postfExpr[ind++] = ' ';
				stChar.pop();
			}

			stChar.push(ch);
			cout << *stChar.peek() << endl;
		}
		else if (ch == '(') {
			getchar();
			stChar.push(ch);
			while (cin.peek() == ' ') getchar();

			if (cin.peek() == '-') {
				postfExpr[ind++] = '0';
				postfExpr[ind++] = ' ';
			}
		}
		else if (ch == ')') {
			getchar();
			while (*stChar.peek() != '(') {
				postfExpr[ind++] = *stChar.peek();
				postfExpr[ind++] = ' ';
				stChar.pop();
			}
			stChar.pop();
		}
		else {
			while (ch != '\n' && isdigit(ch)) {
				postfExpr[ind++] = ch;
				getchar();
				ch = cin.peek();
			}
			postfExpr[ind++] = ' ';
			if (ch == '\n')
				cin.putback(ch);
		}
	}

	while (!stChar.isEmpty()) {
		postfExpr[ind++] = *stChar.peek();
		postfExpr[ind++] = ' ';
		stChar.pop();
	}

	cout << "Постфиксная форма: " << postfExpr << endl;
	return postfExpr;
}

double calculatePostfix(const char* postfExpr) {
	Stack<double> stDouble;
	char digits[6]{};
	double num;
	int ind = 0;

	while (ind < strlen(postfExpr)) {
		int j{};
		if (postfExpr[ind] == ' ') {
			ind++;
			continue;
		}
		if (isdigit(postfExpr[ind])) {
			digits[j++] = postfExpr[ind++];

			while (ind < strlen(postfExpr) && isdigit(postfExpr[ind]))
				digits[j++] = postfExpr[ind++];

			num = strtod(digits, nullptr);
			stDouble.push(num);

			for (int i = 0; i < sizeof(digits); i++)
				digits[i] = '\0';
		}
		else if (isoper(postfExpr[ind])) {
			if (calculate(stDouble, postfExpr[ind]))
				ind++;
			else break;
		}
	}

	double* value = stDouble.peek();
	if (value) return *value;
	return 0;
} */