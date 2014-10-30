#define _MULTI_THREADING
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define SIZE 16 //11

// Struct to keep track of bounds on halves of array.
typedef struct Data {
	int begin;
	int end;
	int *list;
} parameters;

void *split(void *a);
//void *merge(void *);
void *sort(void *a);

int main()  {

	// Initialize unsorted array.
//	int array[SIZE] = {11, 9, 35}; //, 3, 47, 54, 63, 88, 17, 1, 74};
//	int *array = new int[SIZE] {11,9,35,3, 47, 54, 63, 88, 17, 1, 74};
	int array[] = {11,9,35,-148, 3, 47, -50, 54, 0, 80001, 63, 88, 17, 1, 74, 10000};

	cout << "UNSORTED ARRAY" << endl;
	
	for(int i = 0; i < SIZE; i++)  
		cout << array[i] << " ";
	
	cout << endl << endl;
	
	// Create parameters for use in threads.
	parameters *data = new parameters(); //, data2;
	
	// Set bounds for parameters (each half of the array).
	data->begin = 0;
//	data.end = (SIZE/2)-1;
	
//	data2.begin = (SIZE/2);
	data->end = SIZE-1;
	data->list = array;


	// Create the threads.
	pthread_t mainSplit;
	pthread_create(&mainSplit, NULL, split, (void *)data);


	// Wait for threads to terminate.
	pthread_join(mainSplit, NULL);

	cout << endl;
	cout << "SORTED ARRAY" << endl;
	
	for(int i = 0; i < SIZE; i++)  
		cout << array[i] << " ";
		
	cout << endl;

//	delete [] array;
//	array = NULL;
	data->list = NULL;
	delete data;	

	return 0;
}

void *split(void *a) {

	parameters *data = (parameters *) a;
	int size = data->end - data->begin + 1;	
/*
	cout << "0: " << data->list[0];
	cout << "1: " << data->list[1];
	cout << "2: " << data->list[2];
*/
	if(size > 1) {
		pthread_t mergeThread;

		if(size > 2) {

			parameters *dataLeftSplit = new parameters(), *dataRightSplit = new parameters();	
		try{	
			dataLeftSplit->begin = data->begin;
			dataLeftSplit->end = size/2 -1;

			dataRightSplit->begin = size/2;
			dataRightSplit->end = data->end;

			dataLeftSplit->list = data->list;
			dataRightSplit->list = data->list;
		}
		catch(int e){
			cout << "Problem 1!";
			exit(1);
		}

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

		cout << "THREAD (INDEX " << data->begin << "-" << data->end << ")" << endl;

		for(int i = data->begin; i <= data->end; ++i) {
			cout << data->list[i] << " ";
		}

		cout << endl << endl;

	}
	else {
		cout << "THREAD (INDEX " << data->begin << "-" << data->end << ")" << endl;
		try{
		for(int i = data->begin; i <= data->end; ++i) {
			cout << data->list[i] << " ";
		}
		}
		catch(int e) {
			cout << "Problem 2!";
			exit(1);
		}
		cout << endl << endl;
	}
/*
	data->list = NULL;
	delete data;
	data = NULL;
*/
	cout << "COMPLETED!!!" << endl;
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

	list = NULL;
	data = NULL;

	// Complete the thread.
	pthread_exit(NULL);
}

/*
void *merge(void *)  {
	// helper array for merging
	int temp[SIZE];
	
	// Copy two sorted halves into temp array.
	for (int i = 0; i < SIZE; i++)
		temp[i] = array[i];
	
	// Set bounds on halves of the array.
	int i = 0, j = (SIZE/2), k = 0;
	
	// Compare each subarray and sort.
	while(i < (SIZE/2) && j < SIZE)  {
		if(temp[i] < temp[j])  {
			array[k++] = temp[i++];
		}
		else  {
			array[k++] = temp[j++];
		}
	} 
	
	// Copy rest of first subarray.
	while(i < SIZE/2)  
		array[k++] = temp[i++];
		
	// Copy rest of second subarray.
	while(j < SIZE) 
		array[k++] = temp[j++];
		
	// Complete the thread.
	pthread_exit(NULL);
}
*/
