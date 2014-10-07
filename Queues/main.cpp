#include "PriorityQueue.cpp"
#include <iostream>

using namespace std;

int main()  {
	PriorityQueue<int> testQueue(3);
	
	// push a few random int's
	testQueue.push(4);
	testQueue.push(7);
	testQueue.push(1);
	
	// queue shouldn't be empty; check this
	if(testQueue.isEmpty())  {
		cout << "The queue is empty!" << endl;
	}
	
	// pop items (more items than were pushed)
	testQueue.pop();
	testQueue.pop();
	testQueue.pop();
	testQueue.pop();
	
	// should be empty now; check this
	if(testQueue.isEmpty())  {
		cout << "The queue is empty!" << endl;
	}
	
	return 0;
}
