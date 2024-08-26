/* ======================================== */
/*    程式实例: 2_9_4.c                      */
/*    插入某长度子串                          */
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
/*  插入子串: 将 str2 插入 str1 的索引 pos-1 处 */
/* ---------------------------------------- */
char *strins(char *str1, char *str2, int pos) {
    int s_len; /* 字串str1之长度  */
    int d_len; /* 字串str2之长度  */
    int i, j;

    pos--;                 /* 计算字串的开始  */
    s_len = strlen1(str1); /* 计算字串长度    */
    d_len = strlen1(str2);
    /* 后移 d_len 个元素，腾出 str2 的空间 */
    for (i = s_len + 1; i >= pos; i--) str1[i + d_len] = str1[i];  // see 10_4.C

    /* 用回路填入str2至字串str1 */
    for (j = pos; str2[j - pos] != '\0'; j++) str1[j] = str2[j - pos];
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
/*  主程式: 插入字串於某位置                    */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string1[BUFSIZ / 5];  /* 字串阵列1宣告 */
    char string2[BUFSIZ / 10]; /* 字串阵列2宣告 */
    int pos;                   /* 插入位置     */

    printf("请输入原始字符串 ==> ");
    safe_gets(string1, BUFSIZ / 5); /* 读取字串1     */
    printf("请输入插入字串 ==> ");
    safe_gets(string2, BUFSIZ / 10); /* 读取字串2     */
    printf("请输入插入位置 ==> ");
    scanf("%d", &pos);             /* 读取插入位置   */
    strins(string1, string2, pos); /* 插入子串      */
    printf("插入后的字符串是 %s\n", string1);

    return 0;
}
