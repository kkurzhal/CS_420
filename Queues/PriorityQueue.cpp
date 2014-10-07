#include "PriorityQueue.h"

template<typename T>
PriorityQueue<T>::PriorityQueue()  {
	SIZE = 20;
	priorities = new T[SIZE];
	count = 0;
}

template<typename T>
PriorityQueue<T>::PriorityQueue(int size)  {
		SIZE = size;
		priorities = new T[SIZE];
		count = 0;
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()  {
	delete [] priorities;
	priorities = NULL;
}

template<typename T>
int PriorityQueue<T>::push(T priority)  {
	if(count < SIZE)	//added check for if the queue is full
	{
		for (int i = 0; i < SIZE; i++)  {
			if(i+1 != SIZE)  {
				priorities[i+1] = priorities[i];
			}
		}
		priorities[0] = priority; 
		count++;
	}
	else
		return count;
}

template<typename T>
bool PriorityQueue<T>::isEmpty()  {
	if(count == 0)  {
		return true;
	}
	else  {
		return false;
	}
	/*for(int i = 0; i < SIZE; i++)  {
		if(!priorities[i].isEmpty())  {
			return false;
		}
	}
	return true;*/
}

template<typename T>
int PriorityQueue<T>::pop()  {
	if(isEmpty())  {
		return 0;
	
		//return the number of items in the queue instead of printing
		//cout << "Cannot pop item from empty queue!" << endl;
	}
	else  {
		//priorities[count-1] = NULL;	//cannot do this for specific types; maybe a more generic way?		
		return --count;
	}
}

template<typename T>
T PriorityQueue<T>::fetch(int index)  {
	return priorities[index];
} 



