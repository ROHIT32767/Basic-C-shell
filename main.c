#include "headers.h"
INT num_bg_processes;
time_t start_seconds;
typedef long long int INT;
List *LIST;
char *correct_path;
char *previous_path;
char *relative_path;
char *absolute_path;
char *user_name;
char *system_name;
char *H[20];
char *history_path;
INT total_commands = 0;
#define NAME_MAX1 300
INT prompt_wait;
int main(int argc, char *argv[])
{
    absolute_path = (char *)calloc(300, sizeof(char));
    relative_path = (char *)calloc(300, sizeof(char));
    previous_path = (char *)calloc(300, sizeof(char));
    correct_path = (char *)calloc(300, sizeof(char));
    user_name = (char *)calloc(200, sizeof(char));
    system_name = (char *)calloc(200, sizeof(char));
    char *Time = (char *)calloc(300, sizeof(char));
    history_path = (char *)calloc(625, sizeof(char));
    Time[0] = '\0';
    LIST = (List *)malloc(sizeof(List));
    LIST->root = NULL;
    LIST->tail = NULL;
    previous_path[0] = '#';
    previous_path[1] = '\0';
    for (INT i = 0; i < 20; i++)
    {
        H[i] = (char *)calloc(NAME_MAX1, sizeof(char));
    }
    getcwd(absolute_path, 300);
    getcwd(correct_path, 300);
    user_name = getlogin();
    gethostname(system_name, 200);
    relative_path[0] = '~';
    relative_path[1] = '\0';
    char *input = (char *)calloc(1000, sizeof(char));
    char *ptr = input;
    num_bg_processes = 0;
    strcat(history_path, correct_path);
    strcat(history_path, "/history.txt");
    INT D = strlen(history_path);
    history_path[D] = '\0';
    total_commands = readfromhistory();
    prompt_wait = 0;
    while (1)
    {
        size_t size = 100;
        prompt(Time);
        char *tokens[1000];
        prompt_wait = 1;
        INT Y = getline(&ptr, &size, stdin);
        prompt_wait = 0;
        time(&start_seconds);
        input[Y - 1] = '\0';
        INT flag6 = 1;
        INT flag7 = 0;
        for (INT i = 0; i < Y - 1; i++)
        {
            for (INT j = i + 1; j < Y - 1; j++)
            {
                if ((input[i] == ';') && (input[j] == ';'))
                {
                    flag7=1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
                else if ((input[i] == ';') && (input[j] == '&'))
                {
                    flag7=1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
                else if ((input[i] == '&') && (input[j] == ';'))
                {
                    flag7=1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
                else if ((input[i] == '&') && (input[j] == '&'))
                {
                    flag7=1;
                    for (INT k = i + 1; k < j; k++)
                    {
                        if ((input[k] != '\t') && (input[k] != ' ') && (input[k] != '\n'))
                        {
                            flag6 = 0;
                            break;
                        }
                    }
                    if (!flag6)
                    {
                        break;
                    }
                }
            }
            if (!flag6)
            {
                break;
            }
        }
        writetohistory(&H[0], input);
        INT token_count = 0;
        if (flag6&&flag7)
        {
            perror("invalid syntax given as input");
            continue;
        }
        char *p = strstr(input, ";;");
        if (p)
        {
            perror("syntax error near unexpected token `;;'");
            continue;
        }
        else
        {
            tokens[token_count] = strtok(input, ";");
            INT length = strlen(input);
            while (tokens[token_count] != NULL)
            {
                token_count++;
                tokens[token_count] = strtok(NULL, ";");
            }
            for (INT i = 0; i < token_count; i++)
            {
                str_tok_and(tokens[i], relative_path, correct_path, previous_path, length, LIST);
            }
        }
        prompt_wait = 1;
        num_bg_processes = 0;
        time_t end_time;
        time(&end_time);
        long int U = end_time - start_seconds;
        if (U >= 1)
        {
            Time[0] = '\0';
            sprintf(Time, "took %lds", U);
        }
        else
        {
            Time[0] = '\0';
        }
    }
    free(absolute_path);
    free(relative_path);
    free(history_path);
    free(user_name);
    free(previous_path);
    free(correct_path);
    free(system_name);
    free(Time);
}