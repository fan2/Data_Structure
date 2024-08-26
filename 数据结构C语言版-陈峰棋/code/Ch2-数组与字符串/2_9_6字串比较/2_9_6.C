/* ======================================== */
/*    程式实例: 2_9_6.c                      */
/*    字符串比较                             */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  字串比较                                 */
/* ---------------------------------------- */
int strcmp1(char *str1, char *str2) {
    int i, j;

    for (i = 0; str1[i] == str2[i]; i++) /* 字串1等於字串2 */
        if (str1[i] == '\0' && str2[i] == '\0') return 0;

    if (str1[i] < str2[i]) /* 字串1小於字串2 */
        return -1;

    return 1; /* 字串1大於字串2 */
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
/*  主程式: 输入两字串, 比较其内容.              */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string1[BUFSIZ / 10]; /* 字串阵列1宣告  */
    char string2[BUFSIZ / 10]; /* 字串阵列2宣告  */
    int result;                /* 比较结果      */

    printf("请输入字符串(1) ==> ");
    safe_gets(string1, BUFSIZ / 10); /* 读取字串1 */
    printf("请输入字符串(2) ==> ");
    safe_gets(string2, BUFSIZ / 10);    /* 读取字串2 */
    result = strcmp1(string1, string2); /* 字串比较  */
    switch (result) {
        case 0:
            printf("字符串(1)等于字符串(2)\n");
            break;
        case 1:
            printf("字符串(1)大於字串(2)\n");
            break;
        case -1:
            printf("字符串(1)小於字符串(2)\n");
            break;
    }

    return 0;
}
