#include "PriorityQueue.cpp"

int main()  {
	PriorityQueue<int> *testQueue = new PriorityQueue<int>(3);
	

	// push a few random int's
	testQueue->enqueue(4);
	testQueue->enqueue(7);
	testQueue->enqueue(1);
	
	// queue shouldn't be empty; check this
	if(testQueue->isEmpty())  {
		cout << "The queue is empty!" << endl;
	}
	
	// pop items (more items than were pushed)
	cout << testQueue->dequeue() << endl;
	cout << testQueue->dequeue() << endl;
	cout << testQueue->dequeue() << endl;
	cout << testQueue->dequeue() << endl;
	
	// should be empty now; check this
	if(testQueue->isEmpty())  {
		cout << "The queue is empty!" << endl;
	}
	
	return 0;
}
