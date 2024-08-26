/* ======================================== */
/*    程式实例: 2_9_3.c                      */
/*    从某位置取代子串                        */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  取代字串                                 */
/* ---------------------------------------- */
char *strrep(char *str1, char *str2, int pos) {
    int i, j;

    pos--; /* 计算字串的开始      */
    i = 0;
    for (j = pos; str1[j] != '\0'; j++) /* 走访字串str1 */
        if (str2[i] != '\0') {
            str1[j] = str2[i]; /* 取代str2至str1      */
            i++;
        } else
            break;

    return str1;
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
/*  主程式: 在字串str1内取代字串str2.           */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string1[BUFSIZ / 5];  /* 字串阵列1宣告 */
    char string2[BUFSIZ / 10]; /* 字串阵列2宣告 */
    int pos;                   /* 取代位置     */

    printf("请输入原始字符串 ==> ");
    safe_gets(string1, BUFSIZ / 5); /* 读取字串1     */
    printf("请输入取代字符串 ==> ");
    safe_gets(string2, BUFSIZ / 10); /* 读取字串2     */
    printf("请输入取代位置 ==> ");
    scanf("%d", &pos);             /* 读取位置      */
    strrep(string1, string2, pos); /* 取代字串      */
    printf("取代后的字符串是 %s\n", string1);

    return 0;
}
