#include <stdio.h>

int main()
{
    char *str = "123456789";
    str[0] = '0';
    printf("%s\n", str);
}