#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
https://en.cppreference.com/w/c/string/byte/strtok

char *strtok( char *str, const char *delim );

Parameters
str	-	pointer to the null-terminated byte string to tokenize
delim	-	pointer to the null-terminated byte string identifying delimiters

Return value
Returns pointer to the beginning of the next token or a null pointer if there are no more tokens.
*/

// 在 str1 中从 pos 中开始查找空格分割的子串，并填充到 str2 中。
// 返回下一个查找位置 pos，以便外部 while 循环。
int strtoken(char *str1, char *str2, int pos)
{
    int i = pos;
    // trim leading spaces
    while (isspace(str1[i]))
        i++; // non-space start pos for str1
    if (str1[i] != 0)
    {
        printf("strtoken i = %d\n", i);

        int j = 0; // start pos for str2
        while (!isspace(str1[i]) && str1[i]!=0)
            str2[j++] = str1[i++];

        // str1[i] is space or nul
        printf("strtoken j2 = %d\n", j);
        str2[j] = 0;
        return i; // next pos
    }

    return -1;
}

// strtoken 的逆序版本，返回 next rpos
int reverve_strtoken(char *str1, char *str2, int rpos)
{
    int i = rpos;
    // trim tail spaces
    while (isspace(str1[i]))
        i--; // non-space end pos

    if (i != 0)
    {
        printf("reverve_strtoken i = %d\n", i);

        int j = i; // record end pos
        while (!isspace(str1[i]) && i!=0)
            i--;

        // str1[i] is neareast left space or first letter

        // calc start pos
        int k = (i==0 ? 0 : i+1);

        printf("reverve_strtoken k = %d\n", k);

        int m;
        for (m=k; m<=j; m++)
            str2[m-k] = str1[m];
        str2[m-k] = 0; // end nul

        return i; // next rpos(0 or space)
    }

    return -1;
}

int main(int argc, char* argv[])
{
    char string[100] = "This is a book";
    char substr[20];
    int pos = 0; // initial start pos

    // while ((pos = strtoken(string, substr, pos)) != -1)
    // {
    //     printf("substr = %s, next pos = %d\n", substr, pos);
    // }

    pos = strlen(string)-1;
    while ((pos = reverve_strtoken(string, substr, pos)) != -1)
    {
        printf("substr = %s, next rpos = %d\n", substr, pos);
    }

    return 0;
}