#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  读取字符串，替代 gets                      */
/* ---------------------------------------- */
// char* gets_s( char* str, rsize_t n );
void safe_gets(char *str, int size) {
    char *ret = fgets(str, size, stdin);
    if (ret) {
        // 移除结尾的回车/换行符
        char *posr = strchr(str, '\r');
        if (posr)
            *posr = 0;
        char *posn = strchr(str, '\n');
        if (posn)
            *posn = 0;
    }
}