#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>

using namespace std;

template<typename T>
class PriorityQueue
{
	public:
		PriorityQueue();
		PriorityQueue(int size);
		~PriorityQueue();

		//return the number of items in the queue for both functions
		int enqueue(T priority);	//pushes to index 0
		int dequeue();		//pops from index 'n-1' out of 'n' inserted items

		T get(int index);

		T getHead();
		T getTail();

		bool isEmpty();

	private:
		T* priorities;
		int SIZE;
		int count;                 // added this in to determine if queue is empty
};

#endif
