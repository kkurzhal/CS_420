#include "PriorityQueue.h"

template<typedef T>
PriorityQueue<T>::PriorityQueue(int size)  {
		SIZE = size;
		priorities = new T[SIZE];
		count = 0;
}

template<typedef T>
PriorityQueue<T>::~PriorityQueue()  {
	delete [] priorities;
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
	for(int i = 0; i < SIZE; i++)  {
		if(!priorities[i].isEmpty())  {
			return false;
		}
	}
	return true;
}

template<typedef T>
int PriorityQueue<T>::pop()  {
	if(isEmpty())  {
		cout << "Cannot pop item from empty queue!" << endl;
	}
	else  {
		for(int i = 0; i < SIZE; i++)  {
			priorities[i] = priorities[i+1];
		}
		count--;
	}
}

template<typedef T>
T PriorityQueue<T>::fetch(int index)  {
	
} 



