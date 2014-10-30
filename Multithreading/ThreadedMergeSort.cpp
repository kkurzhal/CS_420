#define _MULTI_THREADING
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

// Struct to keep track of bounds on halves of array.
typedef struct Data {
	int begin;
	int end;
	int *list;
} parameters;

void *split(void *a);
void *sort(void *a);

int main()  {

	// Initialize unsorted array.
	int array[] = {11,9,35,-148, 3, 47, -50, 54, 0, 80001, 63, 88, 17, 1, 74, 10000};
	int size = sizeof(array)/sizeof(array[0]);

	cout << endl << "\tUNSORTED ARRAY" << endl << "\t--------------" << endl << "\t[ ";
	
	for(int i = 0; i < size; i++) {
		cout << array[i];

		if(i < size-1)
			cout << ",";

		cout << " ";
	}
	
	cout << "]" << endl << endl;
	
	// Create parameters for use in threads.
	parameters *data = new parameters(); //, data2;
	
	// Set bounds for parameters (each half of the array).
	data->begin = 0;
	data->end = size - 1;
	data->list = array;


	// Create the threads.
	pthread_t mainSplit;
	pthread_create(&mainSplit, NULL, split, (void *)data);


	// Wait for threads to terminate.
	pthread_join(mainSplit, NULL);

	cout << endl;
	cout << "\tSORTED ARRAY" << endl << "\t------------" << endl << "\t[ ";
	
	for(int i = 0; i < size; i++) {
		cout << array[i];

		if(i < size-1)
			cout << ",";

		cout << " ";
	}

	cout << "]" << endl << endl;

	data->list = NULL;
	delete data;	

	return 0;
}

void *split(void *a) {

	parameters *data = (parameters *) a;
	int size = data->end - data->begin + 1;	

	if(size > 1) {
		pthread_t mergeThread;

		if(size > 2) {

			parameters *dataLeftSplit = new parameters(), *dataRightSplit = new parameters();

			dataLeftSplit->begin = data->begin;
			dataLeftSplit->end = size/2 -1;

			dataRightSplit->begin = size/2;
			dataRightSplit->end = data->end;

			dataLeftSplit->list = data->list;
			dataRightSplit->list = data->list;

/*			Uncomment to see progress
			-------------------------

			cout << "Begin = " << data->begin << endl;
			cout << "End = " << data->end << endl;
			cout << "THREAD" << endl;
			for(int i = data->begin; i <= data->end; ++i) {
				cout << data->list[i] << " ";
			}

			cout << endl << "SIZE = " << size << endl;
			cout << "LEFT = ";
			for(int i = dataLeftSplit->begin; i <= dataLeftSplit->end; ++i) {
				cout << data->list[i] << " ";
			}
			cout << endl << "RIGHT = ";
			for(int i = dataRightSplit->begin; i <= dataRightSplit->end; ++i) {
				cout << data->list[i] << " ";
			}
			cout << endl << endl;
*/
			// Create the threads.
			pthread_t threadLeftSplit, threadRightSplit;
			pthread_create(&threadLeftSplit, NULL, split, (void *)dataLeftSplit);	
			pthread_create(&threadRightSplit, NULL, split, (void *)dataRightSplit);

	
			// Wait for threads to terminate.
			pthread_join(threadLeftSplit, NULL);
			pthread_join(threadRightSplit, NULL);

			dataLeftSplit->list = NULL;
			dataRightSplit->list = NULL;
			delete dataLeftSplit;
			delete dataRightSplit;
			dataLeftSplit = NULL;
			dataRightSplit = NULL;
			

			// Create the final thread (merge thread).
			pthread_create(&mergeThread, NULL, sort, (void *)data);
			pthread_join(mergeThread, NULL);
		}
		else {
			// Create the final thread (merge thread).
			pthread_create(&mergeThread, NULL, sort, (void *)data);
			pthread_join(mergeThread, NULL);		
		}

/*			Uncomment to see progress
			-------------------------

		cout << "THREAD (INDEX " << data->begin << "-" << data->end << ")" << endl;

		for(int i = data->begin; i <= data->end; ++i) {
			cout << data->list[i] << " ";
		}

		cout << endl << endl;
*/
	}
/*	else if(size == 1) {
		cout << "THREAD (INDEX " << data->begin << "-" << data->end << ")" << endl;
		cout << data->list[data->begin] << endl << endl;
	}

	cout << "COMPLETED!!!" << endl;
*/

	pthread_exit(NULL);
}

void *sort(void *a)  {
	// Get the parameters passed in.
	parameters *data = (parameters *) a;
	int smallestIndex = 0; 
	int temp = 0;
	int *list = data->list;
	
	// Cycle through bounded piece of array and sort.
	for (int i = data->begin; i <= data->end /*((data->end)-1)*/; i++)  {
		smallestIndex = i;
		for(int j = i+1; j <= data->end; j++)  {
			if(list[j] < list[smallestIndex])  
				smallestIndex = j;
		}
		// Reorder the current piece of the array by sorting.
		temp = list[smallestIndex];
		list[smallestIndex] = list[i];
		list[i] = temp;
	}

	// Complete the thread.
	pthread_exit(NULL);
}
