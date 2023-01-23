#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <sys/types.h>
#include <windows.h>
#include <errno.h>
#include <conio.h>

#define inputsize 600
char command[20][100];
char input[inputsize];

void zero();
void spliter(char *);
void createfile();
void insertstr();
void cat();
void removestr();


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
    }
    else if (!strcmp(command[0], "insertstr"))
    {
        insertstr();
        printf("It's here in insertstr block\n");
    }else if(!strcmp(command[0],"cat")){
        cat();
        printf("It's here in cat block\n");
    }else if(!strcmp(command[0],"removestr")){
        removestr();
        printf("It's here in removestr block!\n");
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
        if (input[i] == '\\')
        {
            i++;
            if (input[i] == 'n')
            {
                command[counter][com_sec] = '\n';
                com_sec++;
                continue;
            }
            else if ((input[i] == '\\') || (input[i] == '"'))
            {
                command[counter][com_sec] = input[i];
                com_sec++;
                continue;
            }
        }
        else if (input[i] == '"')
        {
            if (quotation == -1)
            {
                quotation = 1;
                continue;
            }
            else if (quotation == 1)
            {
                quotation = -1;
                continue;
            }
        }
        else if ((input[i] == ' ') && (quotation == -1))
        {
            counter++;
            com_sec = 0;
            continue;
        }
        else
        {
            command[counter][com_sec] = input[i];
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

    if (access(command[2], F_OK) != 0)
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

void insertstr()
{
    int i;
    char str[2000];
    char direction[500];
    memset(direction, 0, 500);
    memset(str, 0, 2000);
    strcat(direction, command[2]);
    if (access(direction, F_OK) == 0)
    {
        FILE *fp = fopen(direction, "r");
        rewind(fp);
        i = 0;
        while (1)
        {
            str[i] = fgetc(fp);
            if (feof(fp))
                break;
            i++;
        }
        fclose(fp);
    }
    char *line_address;
    char *char_address;
    long line_num = strtol(command[6], &line_address, 10)-1;
    long char_num = strtol(line_address+1,&char_address,10);
    
    FILE *the_file = fopen(command[2], "w");
    
    int line_counter = 0;
    int k = 0;
    for (k; line_counter < line_num; k++)
    {
        fputc(str[k], the_file);
        if (str[k] == '\n')
        {
            line_counter++;
        }
    }
    int char_counter = 0;
    int j;
    for (j = k; char_counter < char_num; j++)
    {
        fputc(str[j], the_file);
        char_counter++;
    }
    fputs(command[4], the_file);

    for (j; j < i; j++)
    {
        fputc(str[j], the_file);
    }
}

void cat(){
    int i;
    char str[2000];
    char direction[500];
    memset(direction, 0, 500);
    memset(str, 0, 2000);
    strcat(direction, command[2]);
    if (access(direction, F_OK) == 0)
    {
        FILE *fp = fopen(direction, "r");
        rewind(fp);
        i = 0;
        while (1)
        {
            str[i] = fgetc(fp);
            if (feof(fp))
                break;
            i++;
        }
        fclose(fp);
    } 
    for(int j=0;j<i;j++){
        printf("%c",str[j]);
    }
}

void removestr(){
int i;
    char str[2000];
    char direction[500];
    memset(direction, 0, 500);
    memset(str, 0, 2000);
    strcat(direction, command[2]);
    if (access(direction, F_OK) == 0)
    {
        FILE *fp = fopen(direction, "r");
        rewind(fp);
        i = 0;
        while (1)
        {
            str[i] = fgetc(fp);
            if (feof(fp))
                break;
            i++;
        }
        fclose(fp);
    }
    char *line_address;
    char *char_address;
    char *size_address;
    long line_num = strtol(command[4], &line_address, 10)-1;
    long char_num = strtol(line_address+1,&char_address,10);
    long size = strtol(command[6],&size_address,10);
    
    FILE *the_file = fopen(command[2], "w");
    int back=0;
    if(!strcmp(command[7],"-b"))
        back=-1;
    int line_counter = 0;
    int k = 0;
    int counter=0;
    for (k; line_counter < line_num; k++)
    {
        counter++;
        if (str[k] == '\n')
        {
            line_counter++;
        }
    }
    for (k=0;k<=counter+char_num+(back*size); k++)
    {
        fputc(str[k], the_file);
    }
    int j=k+size;
    for (j; j < i; j++)
    {
        fputc(str[j], the_file);
    }
}


