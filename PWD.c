#include "headers.h"
void pwd_func(INT arguments)
{
    char* PWD=(char*)calloc(400,sizeof(char));
    getcwd(PWD,400);
    printf("%s%s\033[0m\n",KYEL,PWD);
    free(PWD);
}