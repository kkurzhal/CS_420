/*********************************************
* Filename: shell.cpp
*
* Authors:  Kyle Kurzhal, Morgan Burcham
*
* Course:   CS 420
*********************************************/
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iterator>

using namespace std;

/******************************************************
* Input: None
*
* Output: Print to screen.
*
* Actions: Takes command input from the user and
*	   then implements the call to the appropriate
*	   binary file with the specified options.
******************************************************/
int main()
{
    string str;
    bool exit = false;

    while(!exit)
    {
        pid_t pid;
        int status;

	cout << "user@linux$ ";
	getline(cin,str);

	//this block is taken from http://www.cplusplus.com/forum/beginner/87238/
        istringstream buf(str);
        istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end); // done!

	const char *options[tokens.size()+1];

	for(int i = 1; i < tokens.size(); ++i)
	{
		options[i] = tokens[i].c_str();
	}

	options[tokens.size()] = NULL;


	// Fork a child process.
	pid = fork();

	// Execute the process.
	if(pid == 0)  { 

		//system(str.c_str());

		const char *temp = ("/bin/" + tokens[0]).c_str();
		//got type conversion from http://stackoverflow.com/questions/5797837/how-to-pass-a-vector-of-strings-to-execv
		execv(temp, (char **)options);
		return 0;
	}
	// Check for an error.
	else if (pid < 0)  {
		cout << "An error occurred." << endl;	
	}
	// Wait for the child process to finish.
	else  {
		waitpid(pid,&status,0);
	}


	if(tokens[0] == "exit" || tokens[0] == "EXIT")
//	if(str == "exit" || str == "EXIT")
            exit = true;
    }

    return 0;
}
