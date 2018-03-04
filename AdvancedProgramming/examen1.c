/*
MADE BY: AARON ZAJAC
GITHUB: AARZAJ
MAT: A01023376
*/
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 255

void parent();//PARENT FUNCTION
void openPipe(int pipe_channel[]);//OPEN PIPES
void preparePipes(int pipe_out[], int pipe_in[]);//PREPARE PIPES
void closePipes(int pipe_out[], int pipe_in[]);//CLOSE PIPES
void readFCipher(int pipe_out[], int pipe_in[], char * name, char * name2, char * key);//READ FROM A FILE
char * cipher(char * name, char * key);//ENCRYPT AND DECRYPT

int main()
{
    parent();
    return 0;
}

void readFCipher(int pipe_out[], int pipe_in[], char * name, char * name2, char * key){
    FILE *fp;//OPEN THE FILE
    FILE *fp2;
    char buff[SIZE];//BUFFER
    char * result;//TEXT NAME
    fp = fopen(name, "r");
    fp2 = fopen(name2, "w");
    if ( fp != NULL )
    {
        char line [4096]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, fp ) != NULL ) /* read a line */
        {
            strcpy (buff, line);/* asign a line*/
            cipher(buff, key);
            //fprintf(fp2, "%s", result); /* write the line */
        }
    }
    fclose(fp);//CLOSE THE FILES
    fclose(fp2);
    sprintf(buff, "%s", name2);
    // Write all the characters in the buffer, and also the null character at the end
    write(pipe_out[1], buff, strlen(buff) + 1);
}

char * cipher(char * name, char * key)//FUNCTION Cipher
{
    int msgLen = strlen(name), keyLen = strlen(key), i, j;//DECLARE VARIABLES

    char newKey[msgLen], encryptedMsg[msgLen], decryptedMsg[msgLen];//DECLARE ARRAYS

    //generating new key
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)
            j = 0;

        newKey[i] = key[j];
    }

    newKey[i] = '\0';

    //encryption
    for(i = 0; i < msgLen; ++i)
        encryptedMsg[i] = ((name[i] + newKey[i]) % 26) + 'A';//WIKIPEDIA FORMULA

    encryptedMsg[i] = '\0';

    //decryption
    for(i = 0; i < msgLen-1; ++i)//
        decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';//WIKIPEDIA FORMULA

    decryptedMsg[i] = '\0';

    printf("Original Message: %s", name);
    printf("\nKey: %s", key);
    printf("\nNew Generated Key: %s\n", newKey);
    printf("\nEncrypted Message: %s\n", encryptedMsg);
    printf("\nDecrypted Message: %s\n", decryptedMsg);

    return 0;
}
void parent() {

    pid_t new_id;
    // Variables for the pipes, indicating the direction of communication
    int pipe_parent_child[2];
    int pipe_child_parent[2];

    // Open the two channels
    openPipe(pipe_parent_child);
    openPipe(pipe_child_parent);

    //DECLARATION OF VARIABLES
    int menu = 1;
    char nametext[50];
    strcpy(nametext, "0");
    char result[50];
    strcpy(result, "0");
    char key[50];
    strcpy(key, "0");
    char buffer[SIZE];
    printf("Welcome!\n");

    while (menu > 0)
    {
        printf("Remember write the key and text in UPPERCASE\n");
        printf("Select the process you want: \n");
        printf("1. Cipher \n");
        printf("2. Decipher\n");
        printf("-1. Exit\n");
        scanf("%d", &menu);//MENU
        if (menu == 1) {
            printf("Name of the file to modify: \n");
            scanf("%s", nametext);
            printf("keyword: \n");
            scanf("%s", key);
            new_id = fork();//FORK THE PROCESS IN 2
            if (new_id > 0) {//PARENT PROCESS
                // Get the reply from the child
                read(pipe_child_parent, buffer, SIZE);
                sscanf(buffer, "%s", result);
                printf("The name of your file is %s\n", result);
                closePipes(pipe_child_parent, pipe_parent_child);
            }else if (new_id == 0) {//CHILD
                preparePipes(pipe_child_parent, pipe_parent_child);//PREPARE THE PIPES
                readFCipher(pipe_parent_child, pipe_child_parent, nametext, "encrypted.txt",  key);//CALL THE CHILD PROCESS
                exit(0);
            }else{
                printf("ERROR CREATING THE PROCESS \n");
            }
        }else if (menu == 2) {
            printf("Name of the file to modify: \n");
            scanf("%s", nametext);
            printf("keyword: \n");
            scanf("%s", key);
            new_id = fork();//FORK THE PROCESS IN 2
            if (new_id > 0) {//PARENT PROCESS
                // Get the reply from the child
                read(pipe_child_parent, buffer, SIZE);
                sscanf(buffer, "%s", result);
                printf("The name of your file is %s\n", result);
                closePipes(pipe_child_parent, pipe_parent_child);
            }else if (new_id == 0) {//CHILD
                preparePipes(pipe_child_parent, pipe_parent_child);
                readFCipher(pipe_child_parent, pipe_parent_child, nametext, "decrypted.txt",  key);//CALL THE CHILD PROCESS
            }else{
                printf("ERROR CREATING THE PROCESS \n");
            }
        }else{
            break;
        }
    }
}

// Verify the opening of a commuication pipe
void openPipe(int pipe_channel[])
{
    if (pipe(pipe_channel) == -1)
    {
        perror("Unable to create pipe\n");
        exit(EXIT_FAILURE);
    }
}

// Close the pipe directions that are not necessary
// Receive the file descriptors
void preparePipes(int pipe_out[], int pipe_in[])
{
    // Close the unwanted channels
    close(pipe_in[1]);
    close(pipe_out[0]);
}

// Close the remaining pipes
// Receive the file descriptors
void closePipes(int pipe_out[], int pipe_in[])
{
    // Close the file descriptors
    close(pipe_in[0]);
    close(pipe_out[1]);
}
