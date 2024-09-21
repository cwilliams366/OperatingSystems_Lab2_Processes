#include <stdio.h>
#include <stdlib.h>
#include <time.h> // use time.h header file to use time
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void ChildProcess(void);
void ParentProcess(void);
int main(void);


int main(void)
{
    //First Child Process
    pid_t pid = fork();
    //Status
    int status;
    //Check if the child creation process is successful
    if(pid == 0)
    {
        //Call the child process function for the first
        ChildProcess();
    }
    else if(pid < 0)
    {
      perror("Error! Creating the child process was unsuccessful!\n");
    }
    else
    {
        //Proceed to the Second Child Process
        pid_t pid2 = fork();
        //Check if the second child creation process is successful
        if(pid2 == 0)
        {
          //Call the child process for the second child
          ChildProcess();
        }
        else if(pid2 < 0)
        {
          perror("Error! Creating the child process was unsuccessful!\n");
        }
        else
        {
          //Wait for both processes
          wait(&status);
          //Call the parent process function
          ParentProcess();
        }     
    }
    return 0;
}

void ChildProcess(void)
{
    //Seed number for random number generator
    srand((unsigned int)time(NULL));
    //Max number of random iterations
    int i, iterations = rand() % (30 + 1 - 0) + 0;

    for(i = 0; i < iterations; i++)
    {
      //Stall timer for the sleep function
      int stall = rand() % (10 + 1 - 0) + 0;
      //The current child pid is asleep for x amount of seconds
      printf("Child Pid: %d is going to sleep!\n", getpid());
      //Delay the program for x amount of seconds
      sleep(stall);
      //The current child pid is now awake
      printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",getpid(),getppid());
    }
    exit(0);
}

void ParentProcess(void)
{
  printf("Child Pid: %d has completed\n",getpid());
}
