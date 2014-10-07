#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>

using namespace std;

template<typename T>
class PriorityQueue
{
	public:
		PriorityQueue<T>(int size);
		~PriorityQueue<T>();

		int push(T priority);
		int pop();

		T fetch(int index);

		bool isEmpty();

	private:
		T* priorities;
		const int SIZE;
		int count;                 // added this in to determine if queue is empty
};

#endif
