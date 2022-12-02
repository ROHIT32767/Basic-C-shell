#include "headers.h"
INT str_tok_whitespaces(char *tokens[], char *input)
{
    long long int Token_count = 0;
    tokens[Token_count] = strtok(input, " \t");
    while (tokens[Token_count] != NULL)
    {
        Token_count++;
        tokens[Token_count] = strtok(NULL, " \t");
    }
    return Token_count;
}
void process_command(char *string, char *relative, char *correct, char *previous, INT len, INT last, List *LIST)
{
    char *token[1000];
    INT num_tokens = str_tok_whitespaces(token, string);
    if ((token[0] != NULL) || (len == 0))
    {
        if (strcmp(token[0], "cd") == 0)
        {
            if (&token[1] != NULL)
            {
                cd_func(&token[1], num_tokens - 1, relative, correct, previous);
                INT len = strlen(previous);
                previous[len] = '\0';
            }
            else
            {
                perror("syntax error");
                return;
            }
        }
        else if (strcmp(token[0], "pwd") == 0)
        {
            pwd_func(num_tokens - 1);
        }
        else if (strcmp(token[0], "echo") == 0)
        {
            echo_func(&token[1], num_tokens - 1);
        }
        else if (strcmp(token[0], "ls") == 0)
        {
            ls_func(&token[1], correct, num_tokens - 1);
        }
        else if (strcmp(token[0], "history") == 0)
        {
            if (num_tokens == 1)
            {
                print_history();
            }
            else
            {
                perror("Too many arguments for history");
                return;
            }
        }
        else if (strcmp(token[0], "discover") == 0)
        {

            discover_func(&token[1], correct, num_tokens - 1);
        }
        else if (strcmp(token[0], "pinfo") == 0)
        {
            if (num_tokens <= 2)
            {
                pinfo(&token[1], num_tokens - 1, correct);
            }
            else
            {
                perror("Too many arguments for command pinfo");
                return;
            }
        }
        else
        {
            if ((strlen(token[0]) != 0))
            {
                spec4_func(&token[0],correct, last, LIST,num_tokens);
            }
            else
            {
                perror("syntax error");
                return;
            }
        }
    }
}
