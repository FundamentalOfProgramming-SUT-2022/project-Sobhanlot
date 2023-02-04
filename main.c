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
char clipboard[1000];
int star = 0;
int bychar[100];
int byword[100];

void diagnose();
void zero();
void spliter(char *);
void createfile();
void insertstr();
void cat();
void removestr();
void copystr();
void cutstr();
void pastestr();
void find();
void star_check(char *, int);

int main()
{
    do
    {
        zero();
        int i = -1;
        gets(input);
        spliter(input);
        diagnose();
    } while (strcmp(command[0], "exit"));

    return 0;
}



void diagnose()
{

    if (!strcmp(command[0], "createfile"))
    {
        printf("i wanna create a file!\n");
        createfile();
    }
    else if (!strcmp(command[0], "insertstr"))
    {
        insertstr();
        printf("It's here in insertstr block\n");
    }
    else if (!strcmp(command[0], "cat"))
    {
        cat();
        printf("It's here in cat block\n");
    }
    else if (!strcmp(command[0], "removestr"))
    {
        removestr();
        printf("It's here in removestr block!\n");
    }
    else if (!strcmp(command[0], "copystr"))
    {
        copystr();
        printf("It's here in copy block!\n");
    }
    else if (!strcmp(command[0], "cutstr"))
    {
        memset(clipboard, 0, 1000);
        copystr();
        removestr();
        printf("It's here in cut block!\n");
    }
    else if (!strcmp(command[0], "pastestr"))
    {
        pastestr();
        printf("It's here in paste block\n");
    }
    else if (!strcmp(command[0], "find"))
    {
        find();
        printf("It's here in find block\n");
    }
}

void zero()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            command[i][j] = '\0';
        }
    }
    for (int i = 0; i < inputsize; i++)
    {
        input[i] = '\0';
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
        printf("The file exists!\n");
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
    long line_num = strtol(command[6], &line_address, 10) - 1;
    long char_num = strtol(line_address + 1, &char_address, 10);

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

void cat()
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
    for (int j = 0; j < i; j++)
    {
        printf("%c", str[j]);
    }
}

void removestr()
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
    char *size_address;
    long line_num = strtol(command[4], &line_address, 10) - 1;
    long char_num = strtol(line_address + 1, &char_address, 10);
    long size = strtol(command[6], &size_address, 10);

    FILE *the_file = fopen(command[2], "w");
    int back = 0;
    if (!strcmp(command[7], "-b"))
        back = -1;
    int line_counter = 0;
    int k = 0;
    int counter = 0;
    for (k; line_counter < line_num; k++)
    {
        counter++;
        if (str[k] == '\n')
        {
            line_counter++;
        }
    }
    for (k = 0; k <= counter + char_num + (back * size); k++)
    {
        fputc(str[k], the_file);
    }
    int j = k + size;
    for (j; j < i; j++)
    {
        fputc(str[j], the_file);
    }
    fclose(the_file);
}

void copystr()
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
    char *size_address;
    long line_num = strtol(command[4], &line_address, 10) - 1;
    long char_num = strtol(line_address + 1, &char_address, 10);
    long size = strtol(command[6], &size_address, 10);

    FILE *the_file = fopen(command[2], "w");
    int back = 0;
    if (!strcmp(command[7], "-b"))
        back = -1;
    int line_counter = 0;
    int k = 0;
    int counter = 0;
    for (k; line_counter < line_num; k++)
    {
        counter++;
        if (str[k] == '\n')
        {
            line_counter++;
        }
    }
    for (k = 0; k < i; k++)
    {
        fputc(str[k], the_file);
    }
    // char clipboard[size];
    fclose(the_file);
    int w = 0;
    for (int j = counter + char_num + (back * size) + 1; j < counter + char_num + (back * size) + size + 1; j++)
    {
        clipboard[w] = str[j];
        printf("%c", clipboard[w]);
        w++;
    }
}

void pastestr()
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
    long line_num = strtol(command[4], &line_address, 10) - 1;
    long char_num = strtol(line_address + 1, &char_address, 10);

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
    fputs(clipboard, the_file);

    for (j; j < i; j++)
    {
        fputc(str[j], the_file);
    }
}

void find()
{
    memset(bychar, 0, 100);
    memset(byword, 0, 100);
    int current = 0;
    int i;
    char str[2000];
    char direction[500];
    memset(direction, 0, 500);
    memset(str, 0, 2000);
    strcat(direction, command[4]);
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

    char sub_str[100];
    memset(sub_str, 0, 100);
    strcpy(sub_str, command[2]);
    star_check(sub_str, strlen(sub_str));

    char *sub1 = strtok(sub_str, "*");
    char *sub2 = strtok(NULL, " ");

    if (star == 0)
    {
        int one = 0;
        int space = 1;
        char *temp;
        temp = strstr(str, sub_str);
        if ((temp == NULL) && (one == 0))
        {
            printf("-1");
            return;
        }

        int size = 0, place = 0;
        while (temp != NULL)
        {
            int space = 1;
            int len = 0;
            if (one == 0)
                len = strlen(str);
            else len = strlen(temp);
            temp = strstr(temp + size, sub_str);
            if ((temp == NULL) && (one == 0))
            {
                printf("-1");
                break;
            }else if(temp==NULL){
                break;
            }
            place += len - strlen(temp);
            for (int i = 0; i < place; i++)
            {
                if (str[i] == ' ')
                    space++;
            }
            bychar[current] = place;
            byword[current] = space;
            current++;
            one = 1;
            size = strlen(sub_str);
        }
    }
    else if (star == 1)
    {
        int one = 0;
        char *temp, *temp2;
        temp=strstr(str,sub1);
        int size = 0, place = 0, place2 = 0, last_char = 0, first_char = 0;
        if ((temp == NULL) && (one == 0))
        {
            printf("-1");
        }
        while (temp != NULL)
        {
            int break2=0;
            int space = 1;
            int cond = 0;
            while (cond != 1)
            {
                int len = strlen(temp);
                temp = strstr(temp + size, sub1);
                if ((temp == NULL) && (one == 0))
                {
                    printf("-1");
                    return;
                }
                size = strlen(sub_str);
                place += len - strlen(temp);
                temp2 = strstr(temp + size, sub1);
                if (temp2 == NULL)
                {
                    for (int j = place;; j--)
                    {
                        if (str[j] == ' ')
                        {
                            first_char = j;
                            break2=1;
                            break;
                        }
                        else if (j == 0)
                        {
                            first_char = 0;
                            break2=1;
                            break;
                        }
                    }
                    if(break2==1){
                        break;
                    }
                    for (int i = 0; i < first_char; i++)
                    {
                        if (str[i] == ' ')
                            space++;
                    }
                    bychar[current] = first_char;
                    byword[current] = space;
                    current++;
                    one = 1;
                    break;
                }
                if(break2==1){
                        break;
                    }
                place2 = place + strlen(temp) - strlen(temp2);

                for (int i = place; i < place2; i++)
                {
                    if (str[i] == ' ')
                    {
                        cond = 1;
                        last_char = i;
                        break;
                    }
                }
                for (int j = last_char - 1;; j--)
                {
                    if (str[j] == ' ')
                    {
                        first_char = j;
                        break;
                    }
                    else if (j == 0)
                    {
                        first_char = 0;
                        break;
                    }
                }
                if (cond == 1)
                    break;
            }
            if(break2==1){
                break;
            }
            for (int i = 0; i < first_char; i++)
            {
                if (str[i] == ' ')
                    space++;
            }
            bychar[current] = first_char;
            byword[current] = space;
            current++;
            one = 1;
        }
    }
    else if (star == 2)
    {
        int one = 0;
        int space = 1;
        char *temp;
        temp = strstr(str, sub1);
        if ((temp == NULL) && (one == 0))
        {
            printf("-1");
            return;
        }
        int place = strlen(str) - strlen(temp);
        int size = strlen(sub1);
        for (int i = 0; i < place; i++)
        {
            if (str[i] == ' ')
                space++;
        }
        bychar[current] = place;
        byword[current] = space;
        current++;
        one = 1;
        if ((temp == NULL) && (one == 0))
        {
            printf("-1");
            return;
        }
        while (temp != NULL)
        {
            int space = 1;
            int counter = 0;
            for (int j = place + 1; str[j] != ' ' && j < 1000; j++)
            {
                counter++;
            }
            int len = strlen(temp);
            temp = strstr(temp + size + counter, sub1);
            if (temp == NULL)
            {
                break;
            }
            place += len - strlen(temp);
            for (int i = 0; i < place; i++)
            {
                if (str[i] == ' ')
                    space++;
            }
            bychar[current] = place;
            byword[current] = space;
            current++;
            one = 1;
        }
    }
    else if (star == 3)
    {
        int one = 0;
        int space = 1;
        char *temp1, *temp2;
        temp1 = strstr(str, sub1);
        temp2 = strstr(str, sub2);
        if ((temp1 == NULL) && (one == 0))
        {
            printf("-1");
            return;
        }
        int diff = strlen(temp1) - strlen(temp2);
        int place_star = strlen(str) - strlen(temp1);
        int cond = 1;
        
        for (int j = diff + 1; j < place_star + diff - 1; j++)
        {
            if (str[j] == ' ')
                cond = 0;
        }
        if (cond == 1)
            for (int i = 0; i < place_star; i++)
            {
                if (str[i] == ' ')
                    space++;
            }
        bychar[current] = place_star;
        byword[current] = space;
        current++;
        one = 1;
    }
    if (command[5][0] == '\0')
    {
        printf("%d ", bychar[0]);
    }
    else if ((!strcmp(command[5], "--all")) && (!strcmp(command[6], "--byword")))
    {
        for (int i = 0; i < current; i++)
        {
            printf("%d ", byword[i]);
        }
    }
    else if ((!strcmp(command[6], "--all")) && (!strcmp(command[5], "--byword")))
    {
        for (int i = 0; i < current; i++)
        {
            printf("%d ", byword[i]);
        }
    }
    else if (!strcmp(command[5], "--all"))
    {
        for (int i = 0; i < current; i++)
        {
            printf("%d ", bychar[i]);
        }
    }
    else if (!strcmp(command[5], "--at"))
    {
        char *line_address;
        long line_num = strtol(command[6], &line_address, 10) - 1;
        printf("%d ", bychar[line_num]);
    }
    else if (!strcmp(command[5], "--count"))
    {
        int num = 0;
        for (int i = 0; bychar[i] != 0; i++)
        {
            num++;
        }
        printf("%d ", num);
    }
    else if (!strcmp(command[5], "--byword"))
    {
        printf("%d ", bychar[0]);
    }
    else if ((!strcmp(command[6], "--at")) && (!strcmp(command[5], "--byword")))
    {
        char *line_address;
        long line_num = strtol(command[7], &line_address, 10) - 1;
        printf("%d ", byword[line_num]);
    }
    else if ((!strcmp(command[5], "--at")) && (!strcmp(command[7], "--byword")))
    {
        char *line_address;
        long line_num = strtol(command[6], &line_address, 10) - 1;
        printf("%d ", byword[line_num]);
    }
}

void star_check(char str[], int str_len)
{
    star = 0;
    for (int i = 0; i <= str_len; i++)
    {
        if (str[i] == '*')
            star = 3;
    }
    if (str[str_len - 1] == '*')
        star = 2;
    else if (str[0] == '*')
        star = 1;
}
