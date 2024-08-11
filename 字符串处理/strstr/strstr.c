#include <stdio.h>
#include <string.h>

/*
https://en.cppreference.com/w/c/string/byte/strstr

char *strstr( const char *str, const char *substr );

Parameters
str	-	pointer to the null-terminated byte string to examine
substr	-	pointer to the null-terminated byte string to search for

Return value
Pointer to the first character of the found substring in str, or a null pointer if such substring is not found. If substr points to an empty string, str is returned.
*/

int strindex(const char *str1, const char *str2)
{
    int end, i, j;
    end = strlen(str1)-strlen(str2);

    if (end > 0) {
        for (i=0; i<=end; i++) { // str1 index
            for (j=i; str1[j]==str2[j-i]; j++) {
                if (str2[j-i+1] == 0) {
                    return i;
                }
            }
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    char string[100];
    char substr[20];
    int result;

    puts("请输入字符串 ==> ");
    gets(string);
    puts("请输入要寻找的子字符串 ==> ");
    gets(substr);

    result = strindex(string, substr);
    if (result > 0)
        printf("%s 在 %s 中的位置是 %d\n", substr, string, result);
    else
        printf("在 %s 中没有找到子字符串 %s\n", string, substr);

    return 0;
}