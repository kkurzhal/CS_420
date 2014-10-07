#include "PriorityQueue.cpp"

int main()  {
	PriorityQueue<int> *testQueue = new PriorityQueue<int>(3);
	

	// push a few random int's
	testQueue->push(4);
	testQueue->push(7);
	testQueue->push(1);
	
	// queue shouldn't be empty; check this
	if(testQueue->isEmpty())  {
		cout << "The queue is empty!" << endl;
	}
	
	// pop items (more items than were pushed)
	cout << testQueue->pop() << endl;
	cout << testQueue->pop() << endl;
	cout << testQueue->pop() << endl;
	cout << testQueue->pop() << endl;
	
	// should be empty now; check this
	if(testQueue->isEmpty())  {
		cout << "The queue is empty!" << endl;
	}
	
	return 0;
}
