#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

struct Process
{
	int processTime;
	int completedTime;
	int finished;
	int lastAccess;
	int wait;
	int priority;
	string name;
};

void processInit(Process &p, int time, int priority, string name)
{
	p.processTime = time;
	p.completedTime = 0;
	p.finished = 0;
	p.lastAccess = 0;
	p.wait = 0;
	p.priority = priority;
	p.name = name;
}

void printStats(Process &p)
{
	cout << "Process " << p.name << " - Remaining time is " << p.processTime << " - Current wait time is " << p.wait << endl;
}


void printEnd(list<Process> &completed)
{
	Process *p;
	int totalWait = 0;
	int processCount = completed.size();

	cout << endl << endl << "Results" << endl << "-------" << endl;

	while(!completed.empty())
	{
		p = &(completed.front());
		cout << "Process " << p->name << " - Total process time: " << p->completedTime << " - Wait time: " << p->wait << " - Finish time: " << p->finished << endl;
		totalWait += p->wait;

		p = NULL;
		completed.pop_front();
	}

	cout << endl << "Average wait time: " << (double)totalWait/processCount << endl;
}

void roundRobin(queue<Process,list<Process> > waitQueue, int quantum)
{
	Process *p;
	list<Process> completed;
	int counter = 0;
	bool empty;

	while(!waitQueue.empty())
	{
		p = &(waitQueue.front());
		waitQueue.pop();
		p->wait = counter - p->lastAccess + p->wait;

		for(int k = 0; k < quantum && p->processTime != 0; ++k)
		{
			++counter;

			if(--p->processTime == 0)
				p->finished = counter;

			++p->completedTime;

			printStats(*p);
		}

		p->lastAccess = counter;

		if(p->processTime > 0)
		{
			waitQueue.push(*p);
		}
		else
		{
			completed.push_front(*p);
			p = NULL;
		}
	}

	printEnd(completed);
	p = NULL;
}

void priority(queue<Process,list<Process> > pArr[], int length)
{
	Process *p;
	int counter = 0;
	list<Process> completed;

	for(int i = length - 1; i > -1; --i)
	{
		while(!pArr[i].empty())
		{
			p = &(pArr[i].front());
			pArr[i].pop();

			p->wait = counter;

			while(p->processTime > 0)
			{
				++counter;

				if(--p->processTime == 0)
					p->finished = counter;

				++p->completedTime;

				printStats(*p);
			}

			p->lastAccess = counter;

			completed.push_front(*p);
		}
	}
	
	printEnd(completed);
	completed.clear();
	p = NULL;
}

void sortProcesses(queue<Process,list<Process> > pArr[], int length)
{
	for(int i = length - 1; i > 0; --i)
	{
		for(int j = i - 1; j > -1; --j)
		{
			if(pArr[i].front().processTime > pArr[j].front().processTime)
			{
				queue<Process,list<Process> > temp = pArr[i];
				pArr[i] = pArr[j];
				pArr[j] = temp;
			}
		}
	}
}

int createProcesses(Process *&pArr)
{
	int pNum = 0;
	int choice = 0;
	
	string fileName;

	do
	{
		cout << endl << "Please specify the file that you wish to use:" << endl << "(0) - Exit" << endl << "(1) - smExample1.txt" << endl << "(2) - smExample2.txt" << endl << "(3) - smExample3.txt (Contains one large process)" << endl << "(4) - lgExample1.txt" << endl << "(5) - lgExample2.txt" << endl << "(6) - lgExample3.txt (Contains one large process)" << endl << "(7) - lgExample4.txt (Copy of lgExample1.txt, priority 2 is swapped)" << endl << "(8) - lgExample5.txt (Copy of lgExample1.txt, priority 3 is swapped)" << endl << "(9) - lgExample6.txt (Copy of lgExample1.txt, priorities 2 & 3 are swapped)" << endl << endl << ">> ";
	
		cin >> choice;
		cout << endl;

		switch(choice)
		{
			case 0:
				break;
			case 1:
				fileName = "smExample1.txt";
				break;
			case 2:
				fileName = "smExample2.txt";
				break;
			case 3:
				fileName = "smExample3.txt";
				break;
			case 4:
				fileName = "lgExample1.txt";
				break;
			case 5:
				fileName = "lgExample2.txt";
				break;
			case 6:
				fileName = "lgExample3.txt";
				break;
			case 7:
				fileName = "lgExample4.txt";
				break;
			case 8:
				fileName = "lgExample5.txt";
				break;
			case 9:
				fileName = "lgExample6.txt";
				break;
			default:
				cout << "Unrecognized option selected" << endl << endl;
		}
	}
	while(choice < 0 || choice > 9);

	if(choice == 0)
		return 0;
	else
	{
		ifstream infile(fileName.c_str());
		infile >> pNum;
		pArr = new Process[pNum];

		for(int i = 0; i < pNum; ++i)
		{
			string name;
			int processTime;
			int priority;
			infile >> name;
			infile >> processTime;
			infile >> priority;
			processInit(pArr[i], processTime, priority, name);
		}

		return pNum;
	}
}

int main()
{
	int task;
	int pArrLength = 0;
	Process *pArr = NULL;

	do
	{
		pArrLength = createProcesses(pArr);

		cout << endl << "Please specify the type of task scheduler:" << endl << "(0) - Exit" << endl << "(1) - Priority" << endl << "(2) - Round Robin" << endl << "(3) - First Come First Serve" << endl << "(4) - Shortest Job First" << endl << endl << ">> ";
	
		if(pArrLength == 0)
			task = 0;
		else
			cin >> task;

		//create and initialize all processes
		Process p1 = Process(), p2 = Process(), p3 = Process(), p4 = Process(), p5 = Process();
		processInit(p1, 2, 0, "P1");
		processInit(p2, 1, 0, "P2");
		processInit(p3, 8, 0, "P3");
		processInit(p4, 4, 0, "P4");
		processInit(p5, 5, 0, "P5");

		switch(task)
		{
			case 0:
				cout << "Now exiting..." << endl << endl;
				break;
			case 1:
			{
				//create the priorities array
				int size = pArrLength;
				queue<Process,list<Process> > priorities[size];
				for(int i = 0; i < size; ++i)
				{
					priorities[i] = queue<Process,list<Process> >();
				}
/*
				priorities[1].push(p2);
				priorities[2].push(p1);
				priorities[2].push(p4);
				priorities[3].push(p5);
				priorities[4].push(p3);
*/

				for(int i = 0; i < pArrLength; ++i)
				{
					priorities[pArr[i].priority].push(pArr[i]);
					//cout << pArr[i].name << " " << pArr[i].priority << " " << pArr[i].processTime << endl;
				}

				cout << endl << "Processing Priorities" << endl << "---------------------" << endl;

				priority(priorities,size);
				break;
			}
			case 2:
			{			
				int quantum = 0;
				queue<Process,list<Process> > waitQueue = queue<Process,list<Process> >();
/*
				waitQueue.push(p1);
				waitQueue.push(p2);
				waitQueue.push(p3);
				waitQueue.push(p4);
				waitQueue.push(p5);
*/
				for(int i = 0; i < pArrLength; ++i)
					waitQueue.push(pArr[i]);

				cout << "Please input your time quantum (positive integer): ";
				cin >> quantum;
				if(quantum < 1)
					quantum = 1;

				cout << endl << "Processing Round Robin" << endl << "----------------------" << endl;

				roundRobin(waitQueue,quantum);
				break;
			}
			case 3:
			{
				int size = pArrLength;
				queue<Process,list<Process> > waitQueue[size];
/*
				waitQueue[4].push(p1);
				waitQueue[3].push(p2);
				waitQueue[2].push(p3);
				waitQueue[1].push(p4);
				waitQueue[0].push(p5);
*/
				for(int i = 0; i < pArrLength; ++i)
					waitQueue[i].push(pArr[i]);

				cout << endl << "Processing First Come First Serve" << endl << "---------------------------------" << endl;
				priority(waitQueue, size);
				break;
			}
			case 4:
			{
				int size = pArrLength;
				queue<Process,list<Process> > waitQueue[size];
/*
				waitQueue[4].push(p1);
				waitQueue[3].push(p2);
				waitQueue[2].push(p3);
				waitQueue[1].push(p4);
				waitQueue[0].push(p5);
*/
				for(int i = 0; i < pArrLength; ++i)
					waitQueue[i].push(pArr[i]);

				cout << endl << "Processing Shortest Job First" << endl << "---------------------------------" << endl;
				sortProcesses(waitQueue, size);
				priority(waitQueue, size);
				break;
			}
			default:
				cout << "Unrecognized option selected" << endl << endl;
		}

		delete [] pArr;
		pArr = NULL;
	}
	while(task != 0);

	return 0;
}
