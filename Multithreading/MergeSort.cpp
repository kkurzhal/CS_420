#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define SIZE 11

// Initialize unsorted array.
int array[SIZE] = {11, 9, 35, 3, 47, 54, 63, 88, 17, 1, 74};

// Struct to keep track of bounds on halves of array.
typedef struct Data {
	int begin;
	int end;
} parameters;

void *merge(void *);
void *sort(void *a);

int main()  {
	cout << "UNSORTED ARRAY" << endl;
	
	for(int i = 0; i < SIZE; i++)  
		cout << array[i] << " ";
	
	cout << endl;
	
	// Create parameters for use in threads.
	parameters data1, data2;
	
	// Set bounds for parameters (each half of the array).
	data1.begin = 0;
	data1.end = (SIZE/2)-1;
	
	data2.begin = (SIZE/2);
	data2.end = SIZE-1;
	
	// Create the threads.
	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, sort, &data1);	
	pthread_create(&thread2, NULL, sort, &data2);
	
	// Wait for threads to terminate.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	// Create the final thread (merge thread).
	pthread_create(&thread3, NULL, merge, NULL);
	pthread_join(thread3, NULL);
	
	cout << endl;
	cout << "SORTED ARRAY" << endl;
	
	for(int i = 0; i < SIZE; i++)  
		cout << array[i] << " ";
		
	cout << endl;
	
	return 0;
}

void *sort(void *a)  {
	// Get the parameters passed in.
	parameters *data = (parameters *) a;
	int smallestIndex = 0; 
	int temp = 0;
	
	// Cycle through bounded piece of array and sort.
	for (int i = data->begin; i <= data->end /*((data->end)-1)*/; i++)  {
		smallestIndex = i;
		for(int j = i+1; j <= data->end; j++)  {
			if(array[j] < array[smallestIndex])  
				smallestIndex = j;
		}
		// Reorder the current piece of the array by sorting.
		temp = array[smallestIndex];
		array[smallestIndex] = array[i];
		array[i] = temp;
	}

	// Complete the thread.
	pthread_exit(NULL);
}

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
