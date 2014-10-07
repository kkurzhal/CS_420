#include "PriorityQueue.h"

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
	for (int i = 0; i < SIZE; i++)  {
		if(i+1 != SIZE)  {
			priorities[i+1] = priorities[i];
		}
	}
	priorities[0] = priority; 
	count++;
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
		cout << "Cannot pop item from empty queue!" << endl;
	}
	else  {
		priorities[count-1] = NULL;
		/*for(int i = 0; i < SIZE; i++)  {
			priorities[i] = priorities[i+1];
		}*/
		count--;
	}
}

template<typename T>
T PriorityQueue<T>::fetch(int index)  {
	return priorities[index];
} 



