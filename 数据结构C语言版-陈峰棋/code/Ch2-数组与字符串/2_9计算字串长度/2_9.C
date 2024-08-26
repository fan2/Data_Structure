/* ======================================== */
/*    程式实例: 2_9.c                        */
/*    计算字符串长度                          */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  计算字串长度                              */
/* ---------------------------------------- */
int strlen1(char *str) {
    int i;

    for (i = 0; str[i] != '\0'; i++); /* 用回路计算长度 */
    return i;
}

/* ---------------------------------------- */
/*  读取字符串，替代 gets                      */
/* ---------------------------------------- */
// char* gets_s( char* str, rsize_t n );
void safe_gets(char *str, int size) {
    char *ret = fgets(str, size, stdin);
    if (ret) {
        // 移除结尾的回车/换行符
        char *posr = strchr(str, '\r');
        if (posr) *posr = 0;
        char *posn = strchr(str, '\n');
        if (posn) *posn = 0;
    }
}

/* ---------------------------------------- */
/*  主程式: 读入字串後, 印出字串长度             */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string[BUFSIZ / 10]; /* 字串阵列宣告   */
    int len;                  /* 字串长度      */

    printf("请输入字符串 ==> ");
    safe_gets(string, BUFSIZ / 10); /* 读取字串      */
    len = strlen1(string);          /* 计算字串长度   */
    printf("输入字符串长度是 %d\n", len);

    return 0;
}