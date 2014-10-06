#include "PriorityQueue.h"

template<typedef T>
PriorityQueue<T>::PriorityQueue(int size = 20)  { //added a default to act as default constructor
		SIZE = size;
		priorities = new T[SIZE];
		count = 0;
}

template<typedef T>
PriorityQueue<T>::~PriorityQueue()  {
	delete [] priorities;	//do we need to erase all data before deleting the array?
	priorities = NULL;
}

template<typedef T>
int PriorityQueue<T>::push(T priority)  {
	for (int i = 0; i < SIZE; i++)  {
		if(i+1 != SIZE)  {
			priorities[i+1] = priorities[i];
		}
	}
	priorities[0] = priority; 
	count++;
}

template<typedef T>
bool PriorityQueue<T>::isEmpty()  {
	if(count == 0)  {
		return true;
	}
	else {
		return false;
	}
/*		//I removed the following lines since the count should determine if it is empty or not.

	for(int i = 0; i < SIZE; i++)  {
		if(!priorities[i].isEmpty())  {
			return false;
		}
	}
	return true;
*/
}

template<typedef T>
int PriorityQueue<T>::pop()  {
	if(isEmpty())  {
		cout << "Cannot pop item from empty queue!" << endl;
	}
	else  {

		priorities[count-1] = NULL;
/*	//Taken out because it implements a stack, not a FIFO queue

		for(int i = 0; i < SIZE; i++)  {
			priorities[i] = priorities[i+1];
		}
*/
		count--;
	}
}

template<typedef T>
T PriorityQueue<T>::fetch(int index)  {
	return priorities[index];	
}



