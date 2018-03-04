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
#include <cs50.h>

#define SIZE 255

void parent();
void openPipe(int pipe_channel[]);
void preparePipes(int pipe_out[], int pipe_in[]);
void closePipes(int pipe_out[], int pipe_in[]);
void readFCipher(int pipe_out[], int pipe_in[], char * name, char * key);
char * cipher(char * name, char * key);

int main()
{
    parent();
    return 0;
}

void readFCipher(int pipe_out[], int pipe_in[], char * name, char * key){

    FILE *fp;
    char buffer[SIZE];
    char * result;
    char c;
    fp = fopen(name, "r");
    if ( fp != NULL )
    {
        do {
            c = fgetc(fp);
            cipher(c, key);
            printf("entre");
            if( feof(fp) ) {
                break ;
                }
            }while(1);
    }
    fp = fopen(name, "w");
    printf("sali");
    fputc(c, fp);
    //Send the result
    sprintf(buffer, "%s", name);
    // Write all the characters in the buffer, and also the null character at the end
    write(pipe_out[1], buffer, strlen(buffer) + 1);
    fclose(fp);
}

char * cipher(char * name, char * key)
{
    int msgLen = strlen(name), keyLen = strlen(key), i, j;

    char newKey[msgLen], encryptedMsg[msgLen], decryptedMsg[msgLen];

    //generating new key
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)
            j = 0;

        newKey[i] = key[j];
    }

    newKey[i] = '\0';

    //encryption
    for(i = 0; i < msgLen; ++i)
        encryptedMsg[i] = ((name[i] + newKey[i]) % 26) + 'A';

    encryptedMsg[i] = '\0';

    //decryption
    for(i = 0; i < msgLen; ++i)
        decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';

    decryptedMsg[i] = '\0';

    printf("Original Message: %s", name);
    printf("\nKey: %s", key);
    printf("\nNew Generated Key: %s\n", newKey);
    printf("\nEncrypted Message: %s\n", encryptedMsg);
    printf("\nDecrypted Message: %s\n", decryptedMsg);

    return encryptedMsg;
}
void parent() {

    pid_t new_id;
    // Variables for the pipes, indicating the direction of communication
    int pipe_parent_child[2];
    int pipe_child_parent[2];

    // Open the two channels
    openPipe(pipe_parent_child);
    openPipe(pipe_child_parent);

    int menu = 1;
    char buffer[SIZE];
    char nametext[50];
    strcpy(nametext, "0");
    char result[50];
    strcpy(result, "0");
    char key[50];
    strcpy(key, "0");

    while (menu > 0)
    {
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
            if (new_id > 0) {
                menu = 1;
            }else if (new_id == 0) {
                preparePipes(pipe_child_parent, pipe_parent_child);
                readFCipher(pipe_child_parent, pipe_parent_child, nametext, key);//CALL THE CHILD PROCESS
                // Get the reply from the child
                read(pipe_child_parent, buffer, SIZE);
                sscanf(buffer, "%s", result);
                printf("The result sent by child is %s\n", result);
                closePipes(pipe_child_parent, pipe_parent_child);
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
