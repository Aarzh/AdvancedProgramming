/*
    Program to test changing the child for another process and waiting for it
    Uses: fork, execl, waitpid
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Library to access POSIX functions
#include <sys/wait.h>

int main()
{
    printf("CALL TO FORK\n");
    pid_t new_id;

    // Create a new process
    new_id = fork();

    printf("My pid: [%d], my parent id: [%d], new_id: [%d]\n", getpid(), getppid(), new_id);

    // The parent process
    if (new_id > 0)
    {
        printf("I am the parent of %d\n", new_id);
        int status;

    }
    // The child process
    else if (new_id == 0)
    {
        printf("\tI am the child process\n");
        // Transform the child into another program
        //execl("/bin/ls", "ls", "-l", "-h", (char *) NULL);
        char * program = "/bin/ls";
        char * parameters[] = {"ls", "-l", "-h", (char *) NULL};
        execv(program, parameters);
    }
    // If the new_id is negative
    else
    {
        printf("COULD NOT CREATE A NEW PROCESS\n");
    }

    printf("BACK TO THE MAIN PROGRAM\n");

    return 0;
}
