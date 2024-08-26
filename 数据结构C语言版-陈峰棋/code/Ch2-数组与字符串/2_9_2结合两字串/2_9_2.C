/* ======================================== */
/*    程式实例: 2_9_2.c                      */
/*    结合两字符串                            */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  结合两字串: 确保str1的长度足够容纳拼接        */
/* ---------------------------------------- */
// char *strcat( char *dest, const char *src );
char *strcat1(char *str1, char *str2) {
    int i, j;

    // 空循环移动前串的游标到尾部
    for (i = 0; str1[i] != '\0'; i++); /* 找字串str1结束 */

    // 前串尾部续接后串
    for (j = 0; str2[j] != '\0'; j++) /* 拷贝字串内容   */
        str1[i + j] = str2[j];

    str1[i + j] = '\0'; /* 设定字串结束   */

    return str1;
}

// 第二种实现
char *strcat2(char *str1, char *str2) {
    char *cp = str1;

    while (*cp++);

    while ((*cp++ = *str2++));

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
/*  主程式: 输入二字串後, 将之结合成一字串.       */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string1[BUFSIZ / 5];  /* 字串阵列1宣告 */
    char string2[BUFSIZ / 10]; /* 字串阵列2宣告 */

    printf("请输入字符串(1) ==> ");
    safe_gets(string1, BUFSIZ / 5); /* 读取字串1     */
    printf("请输入字符串(2) ==> ");
    safe_gets(string2, BUFSIZ / 10); /* 读取字串2     */
    strcat1(string1, string2);       /* 字串结合      */
    printf("合并后的字符串是 %s\n", string1);

    return 0;
}
