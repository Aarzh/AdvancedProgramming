/*
    MADE BY: AARON ZAJAC
    GITHUB: AARZAJ
    MAT: A01023376
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void factorial() {
    char num[50];//AN ARRAY OF CHARS FOR THE NUMBER
    strcpy(num, "0");//INITIALIZE THE ARRAY
    printf("Enter the factorial number: \n");//GETS THE NUMBER
    scanf("%s", num);
    char * program = "/usr/bin/python3";
    char * parameters[] = {"python", "python_test.py", num, (char *) NULL};
    execv(program, parameters);//EXECUTE THE PYTHON PROGRAM
}

void BiggestNum(){
    char num1[50];//AN ARRAY OF CHARS FOR THE NUMBER
    char num2[50];//AN ARRAY OF CHARS FOR THE NUMBER
    strcpy(num1, "0");//INITIALIZE THE ARRAY
    strcpy(num2, "0");//INITIALIZE THE ARRAY
    printf("Enter the first number: \n");//GETS THE NUMBER
    scanf("%s", num1);
    printf("Enter the second number: \n");//GETS THE NUMBER2
    scanf("%s", num2);
    char * program = "/usr/bin/python3";
    char * parameters[] = {"python", "argument.py", num1, num2, (char *) NULL};
    execv(program, parameters);//EXECUTE THE PYTHON PROGRAM

}

void Parent(){
    int menu = 1;//KEEPS THE MENU OPEN
    while (menu > 0) {//LOOP FOR MENU
        int ress = 0;
        pid_t new_id;//CREATE A PROCESS
        printf("Select the process you want: \n");
        printf("1. Factorial of a number \n");
        printf("2. Biggest number\n");
        printf("-1. Exit\n");
        scanf("%d", &menu);//MENU
        if (menu == 1) {
            new_id = fork();//FORK THE PROCESS IN 2
            if (new_id > 0) {
                int status;
                waitpid(new_id, &status, 0);//WAIT UNTIL THE PYTHON PROGRAM FINISHES
                if (WIFEXITED(status))
                {
                    int num = WEXITSTATUS(status);//RETURN THE VALUE OF THE PYTHON PROGRAM
                    printf("Your number is %d\n", num);
                }
            }else if (new_id == 0) {
                factorial();//CALL THE CHILD PROCESS
            }else{
                printf("ERROR CREATING THE PROCESS \n");
            }
        }else if (menu == 2) {
            new_id = fork();//FORK THE PROCESS IN 2
            if (new_id > 0) {
                int status;
                waitpid(new_id, &status, 0);//WAIT UNTIL THE PYTHON PROGRAM FINISHES
                if (WIFEXITED(status))
                {
                    int num = WEXITSTATUS(status);//RETURN THE VALUE OF THE PYTHON PROGRAM
                    printf("Your biggest number is %d\n", num);
                }
            }else if (new_id == 0) {
                BiggestNum();//CALL THE CHILD PROCESS
            }else{
                printf("ERROR CREATING THE PROCESS \n");
            }
        }
    }

}

int main()
{
    Parent();//CAL THE PARENT FUNCTION
    return 0;
}
