/*
    MADE BY: AARON ZAJAC
    GITHUB: AARZAJ
    MAT: A01023376
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void Parent(){
    pid_t new_id;
    new_id = fork(); // Create a new process

    //printf("My pid: [%d], my parent id: [%d], new_id: [%d]\n", getpid(), getppid(), new_id);

    // The parent process
    if (new_id > 0)
    {
        int menu = 0;
        int ress = 0;
        printf("Select the process you want: \n");
        printf("1. Factorial of a number \n");
        printf("2. Biggest number\n");
        //scanf("%d", &menu);
        if (menu == 1) {
            int status;
            waitpid(new_id, &status, 0);
            if (WIFEXITED(status))
            {
                printf("Child finished with status: %d\n", WEXITSTATUS(status));
            }
        }else if (menu == 0) {
            printf("hola\n");
        }
    }
    // The child process
    else if (new_id == 0)
    {
        //execl("g++ ", "factorial.cpp", (char *) NULL);
        char * program = "/usr/bin/python3";
        char * parameters[] = {"python", "python_test.py", (char *) NULL};
        execv(program, parameters);
        //execl("/bin/ls", "ls", "-l", "-h", (char *) NULL);
    }
    // If the new_id is negative
    else
    {
        printf("COULD NOT CREATE A NEW PROCESS\n");
    }
}

int main()
{
    Parent();
    return 0;
}
