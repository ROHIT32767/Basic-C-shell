#include "headers.h"

void cd_func(char *string[], INT num, char *relative, char *correct, char *previous)
{
    if (num > 1)
    {
        perror("Incorrect number of arguments supplied for command cd");
        return;
    }
    else if (num == 1)
    {
        INT dir_ret;
        if (string[0][0] == '~')
        {
            char *modify_path = (char *)calloc(600, sizeof(char));
            strcpy(modify_path, correct);
            strcat(modify_path, &string[0][1]);
            dir_ret = chdir(modify_path);
        }
        else if (string[0][0] == '-')
        {
            if (previous[0] == '#')
            {
                perror("OLDPWD NOT SET");
                return;
            }
            else
            {
                char *modify_path = (char *)calloc(600, sizeof(char));
                if (previous[0] == '~')
                {
                    char *modify_path1 = (char *)calloc(600, sizeof(char));
                    strcpy(modify_path1, correct);
                    strcat(modify_path1, &previous[1]);
                    dir_ret = chdir(modify_path1);
                    printf("%s\n",modify_path1);
                }
                else
                {
                    strcpy(modify_path, previous);
                    dir_ret = chdir(modify_path);
                    printf("%s\n",modify_path);
                }
            }
        }
        else
        {
            dir_ret = chdir(string[0]);
        }
        INT Z = 1;
        if (dir_ret == -1)
        {
            perror(NULL);
            return;
        }
        else
        {
            strcpy(previous, relative);
            char *dir_absolute;
            dir_absolute = getcwd(NULL, 300);
            if(dir_absolute==NULL)
            {
                perror(NULL);
                return;
            }
            char *p = strstr(dir_absolute, correct);
            if (p)
            {
                INT len1 = strlen(dir_absolute);
                INT len2 = strlen(correct);
                char *curr_dir1 = (char *)calloc(len1 - len2 + 2, sizeof(char));
                curr_dir1[0] = '~';
                INT i = 1;
                for (i = 1; i <= len1 - len2; i++)
                {
                    curr_dir1[i] = dir_absolute[len2 + i - 1];
                }
                curr_dir1[i] = '\0';
                strcpy(relative, curr_dir1);
            }
            else
            {
                strcpy(relative, dir_absolute);
            }
        }
    }
    else if (num == 0)
    {

        INT dir_ret;
        char *modify_path = (char *)calloc(600, sizeof(char));
        strcpy(modify_path, correct);

        dir_ret = chdir(modify_path);
        if (dir_ret == -1)
        {
            perror(NULL);
            return;
        }
        else
        {
            
            strcpy(previous, relative);
            char *dir_absolute;
            dir_absolute = getcwd(NULL, 300);
            if(dir_absolute==NULL)
            {
                perror(NULL);
                return;
            }
            char *p = strstr(dir_absolute, correct);
            if (p)
            {
                INT len1 = strlen(dir_absolute);
                INT len2 = strlen(correct);
                char *curr_dir1 = (char *)calloc(len1 - len2 + 2, sizeof(char));
                curr_dir1[0] = '~';
                INT i = 1;
                for (i = 1; i <= len1 - len2; i++)
                {
                    curr_dir1[i] = dir_absolute[len2 + i - 1];
                }
                curr_dir1[i] = '\0';
                strcpy(relative, curr_dir1);
            }
            else
            {
                strcpy(relative, dir_absolute);
            }
        }
    }
}

