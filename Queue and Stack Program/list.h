

#include <iostream>
#include <iomanip>

using namespace std;

template <class V_T, const size_t MAX>
class List
{
public:
	/* Two constructors: a default, and a copy*/
	List() { clear(); }
	List(List<V_T, MAX> &l);
	/* This set of methods manipulate the position */
	void first();
	void last();
	void prev();
	void next();
	void setPos(int n);
	/* These methods are used to interact with the elements in respect of position */
	void replace(int n);
	void erase();
	void clear();
	void insertBefore(V_T n);
	void insertAfter(V_T n);
	/* All methods that return a boolean value along with operator overloads */
	bool empty() { return (used == 0); }
	bool operator==(List &l);
	bool operator!=(List &l);
	List operator+(List &l);
	void operator=(List &l);
	friend ostream& operator<<(ostream& out, List &l);
	
	int getPos() { return pos; }
	V_T getElement() {return ary[pos];}
	size_t size() { return used; }
private:
	V_T ary[MAX];
	size_t used;
	size_t pos;
};
/* Copy constructor calls assignment overloaded operator */
template <class V_T, size_t MAX>
List<V_T, MAX>::List(List<V_T, MAX> &l)
{
	operator=(l);
}
/* Sets position to first element */
template <class V_T, size_t MAX>
void List<V_T, MAX>::first()
{
	pos = 0;
}
/* Sets position to last element before 'used' */
template <class V_T, size_t MAX>
void List<V_T, MAX>::last()
{
	if (used > 0)
	pos = used - 1;
}
/* Sets position to previous element if not at 0 */
template <class V_T, size_t MAX>
void List<V_T, MAX>::prev()
{
	if (pos > 0)
	pos--;
}
/* Sets position to next element if not at 'last' already */
template <class V_T, size_t MAX>
void List<V_T, MAX>::next()
{
	if (pos < used - 1)
	pos++;
}
/* Sets position from passed in value IF within constraints of 0 to 'used' */
template <class V_T, size_t MAX>
void List<V_T, MAX>::setPos(int n)
{
	if (n < used && n >= 0)
	pos = n;
}
/* Replaces element of current position with passed value */
template<class V_T, size_t MAX>
void List<V_T, MAX>::replace(int n)
{
	if (used == 0)
	{
		used++;
		pos = 0;
	}
	ary[pos] = n;
}
/* Erases element of current position and left-justifies following elements if any */
template<class V_T, size_t MAX>
void List<V_T, MAX>::erase()
{
	if (used == 0)
		return;
	used--;
	for (int i = pos; i < used; i++)
		ary[i] = ary[i + 1];
}
/* Clears the entire array; is used in default constructor to clean up the array */
template<class V_T, size_t MAX>
void List<V_T, MAX>::clear()
{
	used = 0;
	pos = 0;
}
/* Inserts a value in the current position pushing everything right */
template<class V_T, size_t MAX>
void List<V_T, MAX>::insertBefore(V_T n)
{
	int t;
	if (used == MAX)
		return;
	used++;
	for (int i = used - 1; i > pos; i--)
		ary[i] = ary[i - 1];
	ary[pos] = n;
}
/* Inserts a value in position after current position; position moved to inserted value */
template<class V_T, size_t MAX>
void List<V_T, MAX>::insertAfter(V_T n)
{
	int t;
	if (used == MAX)
		return;
	used++;
	if (used > 1)
	{
		next();
		for (int i = used - 1; i > pos; i--)
			ary[i] = ary[i - 1];
	}
	ary[pos] = n;
}
/* Overloaded operator to test equality between two 'list' objects */
template<class V_T, size_t MAX>
bool List<V_T, MAX>::operator==(List<V_T, MAX> &l)
{
	if (used != l.size())
		return 0;
	if (pos != l.getPos())
	return 0;
	
	for (int i = 0; i < used; i++)
	{
		l.setPos(i);
		if (ary[i] != l.getElement())
			return 0;
	}
	return 1;
}
/* Overloaded operator to test inequality between two 'list' objects; calls '==' operator */
template<class V_T, size_t MAX>
bool List<V_T, MAX>::operator!=(List<V_T, MAX> &l)
{
	if (operator==(l))
		return 0;
	return 1;
}
/* Overloaded operator to add two 'list' objects returning a temporary list object */
template<class V_T, size_t MAX>
List<V_T, MAX> List<V_T, MAX>::operator+(List &l)
{
	List temp;
	if (operator==(l))
	{
		for (int i = 0; i < used; i++)
		{
			l.setPos(i);
			temp.insertAfter(ary[i] + l.getElement());
		}
	}
	return temp;
}
/* Overloaded operator assign 'list' object to another; called in copy constructor */
template<class V_T, size_t MAX>
void List<V_T, MAX>::operator=(List<V_T, MAX> &l)
{
	used = l.size();
	for (int i = 0; i < used; i++)
	{
		l.setPos(i);
		ary[i] = l.getElement();
	}
}
/* Overloaded operator to print array in 'list' object */
template<class V_T, size_t MAX>
ostream& operator<<(ostream& out, List<V_T, MAX> &l)
{
	for (int i = 0; i < l.size(); i++)
	{
		l.setPos(i);
		cout << l.getElement() << " ";
	}
	return out;
}
