#include "list.h"

template<class V_T, size_t MAX>
class Queue
{
private:
	List<V_T, MAX> myQ;
public:

	void inQueue(V_T a);
	void deQueue();
	bool empty() { return myQ.empty(); }
	int size() { return myQ.size(); }
	V_T front();
};
/* Adds a new value to the back of the queue */
template<class V_T, size_t MAX>
void Queue<V_T, MAX>::inQueue(V_T a)
{
	myQ.first();
	myQ.insertBefore(a);
}
/* Removes the first element at the front of the queue */
template<class V_T, size_t MAX>
void Queue<V_T, MAX>::deQueue()
{
	myQ.last();
	myQ.erase();
}
/* Returns the value of the front element of the queue */
template<class V_T, size_t MAX>
V_T Queue<V_T, MAX>::front()
{
	myQ.last();
	return myQ.getElement();
}

