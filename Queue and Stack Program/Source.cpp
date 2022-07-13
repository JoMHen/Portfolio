// John Hendrick
// CS 372 Data Structures
// Encoding and Decoding
// This program uses the Aggregate stack and queue class to use one of each to
// interleave the values read in.  Using templates, we can declare an object
// to work with different data types and different sizes of arrays as desired

#include "Stack.h"
#include <fstream>
#include <string>

/* Calls to interleave elements and encode a list using stacks and queues */
template<class V_T, const size_t MAX>
void encode(Stack<V_T, MAX> &s, Queue<V_T, MAX> &q, size_t sz)
{
	size_t half = sz / 2;
	for (int i = 0; i < half; i++)
	{
		s.push(q.front());
		q.deQueue();
	}

	while (!s.empty())
	{
		q.inQueue(s.top());
		s.pop();
	}

	for (int i = 0; i < half; i++)
	{
		s.push(q.front());
		q.deQueue();
		q.inQueue(s.top());
		s.pop();
	}

	for (int i = 0; i < half; i++)
	{
		s.push(q.front());
		q.deQueue();
	}

	while (!s.empty())
	{
		q.inQueue(s.top());
		s.pop();
		s.push(q.front());
		q.deQueue();
		q.inQueue(s.top());
		s.pop();
	}
}
/* Is called to decode an encoded list */
template<class V_T, const size_t MAX>
void decode(Stack<V_T, MAX> &s, Queue<V_T, MAX> &q, size_t sz)
{
	size_t half = sz / 2;

	for (int i = 0; i < half; i++)
	{
		s.push(q.front());
		q.deQueue();
		s.push(q.front());
		q.deQueue();
		q.inQueue(s.top());
		s.pop();
	}
	for (int i = 0; i < half; i++)
	{
		s.push(q.front());
		q.deQueue();
	}
	while (!s.empty())
	{
		q.inQueue(s.top());
		s.pop();
	}

	for (int i = 0; i < sz; i++)
	{
		s.push(q.front());
		q.deQueue();
	}

	while (!s.empty())
	{
		q.inQueue(s.top());
		s.pop();
	}
	for (int i = 0; i < half; i++)
	{
		s.push(q.front());
		q.deQueue();
	}
	while (!s.empty())
	{
		q.inQueue(s.top());
		s.pop();
	}

}

int main()
{
	const size_t sz = 30;
	Queue<int, sz> Q;
	Stack<int, sz> S;
	ifstream f;
	std::string temp;
	
	for (int i = 1; i <= sz; i++)
		Q.inQueue(i);
	
	encode(S, Q, sz);

	cout << "Encoded (1-30): ";
	for (int i = 0; i < sz; i++)
	{
		cout << Q.front() << " ";
		Q.deQueue();
	}

	const size_t szs = 170;
	Queue<string, szs> Qu;
	Stack<string, szs> St;
	f.open("Encoded.txt");
	while (f >> temp)
	{
		Qu.inQueue(temp);
	}

	decode(St, Qu, szs);
	cout << "\n\nDecoded Text:\n\n";
	for (int i = 1; i <= szs; i++)
	{
		cout << Qu.front() << " ";
		Qu.deQueue();
		if (i % 10 == 0)
			cout << endl;
	}
	system("pause");
}