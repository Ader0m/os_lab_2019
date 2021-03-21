#include "revert_string.h"
#include "stdio.h"
#include <string.h>

void RevertString(char *str)
{
	int i = strlen(str);
    for (int j = 0; j < i/2; j++)
    {
        char temp = str[i-j-1];
        str[i-j-1] = str[j];
        str[j] = temp;
    }
}
