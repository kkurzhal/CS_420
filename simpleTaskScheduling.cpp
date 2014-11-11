#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

struct Process
{
	int processTime;
	int completedTime;
	int finished;
	int lastAccess;
	int wait;
	string name;
};

void processInit(Process &p, int time, string name)
{
	p.processTime = time;
	p.completedTime = 0;
	p.finished = 0;
	p.lastAccess = 0;
	p.wait = 0;
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
		p->wait = counter - p->lastAccess;

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

int main()
{
	int task;

	do
	{
		cout << endl << "Please specify the type of task scheduler:" << endl << "(0) - Exit" << endl << "(1) - Priority" << endl << "(2) - Round Robin" << endl << endl << ">> ";

		cin >> task;

		//create and initialize all processes
		Process p1 = Process(), p2 = Process(), p3 = Process(), p4 = Process(), p5 = Process();
		processInit(p1, 2, "P1");
		processInit(p2, 1, "P2");
		processInit(p3, 8, "P3");
		processInit(p4, 4, "P4");
		processInit(p5, 5, "P5");

		switch(task)
		{
			case 0:
				cout << "Now exiting..." << endl << endl;
				break;
			case 1:
			{
				//create the priorities array
				int size = 5;
				queue<Process,list<Process> > priorities[size];
				for(int i = 0; i < size; ++i)
				{
					priorities[i] = queue<Process,list<Process> >();
				}

				priorities[1].push(p2);
				priorities[2].push(p1);
				priorities[2].push(p4);
				priorities[3].push(p5);
				priorities[4].push(p3);

				cout << endl << "Processing Priorities" << endl << "---------------------" << endl;

				priority(priorities,size);
				break;
			}
			case 2:
			{			
				int quantum = 0;
				queue<Process,list<Process> > waitQueue = queue<Process,list<Process> >();
				waitQueue.push(p1);
				waitQueue.push(p2);
				waitQueue.push(p3);
				waitQueue.push(p4);
				waitQueue.push(p5);

				cout << "Please input your time quantum (positive integer): ";
				cin >> quantum;
				if(quantum < 1)
					quantum = 1;

				cout << endl << "Processing Round Robin" << endl << "----------------------" << endl;

				roundRobin(waitQueue,quantum);
				break;
			}
			default:
				cout << "Unrecognized option selected" << endl << endl;
		}
	}
	while(task != 0);

	return 0;
}
