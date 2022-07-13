#include "Queue.h"

template<class V_T, size_t MAX>
class Stack
{
private:
	List<V_T, MAX> myS;
public:

	void push(V_T a);
	void pop();
	bool empty() { return myS.empty(); }
	int size() { return myS.size(); }
	V_T top();
};
/* Adds a new value to the stack */
template<class V_T, size_t MAX>
void Stack<V_T, MAX>::push(V_T a)
{
	myS.last();
	myS.insertAfter(a);
}
/* Removes the latest element added onto the stack */
template<class V_T, size_t MAX>
void Stack<V_T, MAX>::pop()
{
	myS.last();
	myS.erase();
}
/* Returns the value of the top element of the stack */
template<class V_T, size_t MAX>
V_T Stack<V_T, MAX>::top()
{
	myS.last();
	return myS.getElement();
}

