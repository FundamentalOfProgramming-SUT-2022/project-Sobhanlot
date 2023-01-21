#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <conio.h>
#include <dir.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>

#define inputsize 600
char command[20][100];
char input[inputsize];

void zero();
void spliter(char *);
void createfile();

int main()
{
    zero();
    int i = -1;
    gets(input);

    spliter(input);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            printf("%c", command[i][j]);
        }
        printf("\n");
    }

    if (!strcmp(command[0], "createfile"))
    {
        printf("i wanna create a file!\n");
        createfile();
    }else if(!strcmp(command[0],"insertstr")){
       // insertstr();
    }

    return 0;
}

void zero()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            input[i] = '\0';
            command[i][j] = '\0';
        }
    }
}

void spliter(char input[])
{
    int counter = 0;
    int com_sec = 0;
    int quotation = -1;
    int backslash = 0;
    for (int i = 0; i < inputsize; i++)
    {
        if(input[i]=='\\'){
            i++;
            if(input[i]=='n'){
                command[counter][com_sec]='\n';
                com_sec++;
                continue;
            }else if((input[i]=='\\')||(input[i]=='"')){
                command[counter][com_sec]=input[i];
                com_sec++;
                continue;
            }
        }else if(input[i]=='"'){
            if(quotation==-1){
                quotation=1;
                continue;
            }else if(quotation==1){
                quotation=-1;
                continue;
            }
        }else if((input[i]==' ')&&(quotation==-1)){
            counter++;
            com_sec=0;
            continue;
        }else{
            command[counter][com_sec]=input[i];
            com_sec++;
            continue;
        }
    }
}

void createfile()
{
    char address[200];
    memset(address, 0, 200);
    address[0] = '.';
    address[1] = '/';

    if(access(command[2], F_OK) != 0)
    {
        for (int i = 2; command[2][i] != '\0'; i++)
        {
            if (command[2][i] == '/')
            {
                mkdir(address);
                printf("%s\n", address);
            }

            address[i] = command[2][i];
        }
        printf("%s", address);
        FILE *the_file;
        the_file = fopen(address, "w");
        fclose(the_file);
        printf("The file created!\n");
    }
    else
    {
        printf("the file exists!\n");
    }
}

// void insertstr(){
//      if(access(command[2], F_OK) == 0){
//         char save_file[100][inputsize];
//         FILE *the_file=fopen(command[2],"w");
//         fgets(,inputsize,the_file)
//      }
// }


