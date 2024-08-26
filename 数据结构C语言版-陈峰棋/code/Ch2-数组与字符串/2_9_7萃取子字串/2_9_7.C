/* ======================================== */
/*    程式实例: 2_9_7.c                      */
/*    萃取子串                               */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  萃取子字串                                */
/* ---------------------------------------- */
char *substr(char *str, int pos, int len) {
    static char str1[BUFSIZ / 10]; /* 子字串宣告 */
    int i, j, end;

    pos--;               /* 计算字串的开始 */
    end = pos + len - 1; /* 计算结束位置   */
    for (i = pos, j = 0; i <= end; i++, j++)
        str1[j] = str[i]; /* 拷贝字串内容   */
    str1[len] = '\0';     /* 设定字串结束   */
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
/*  主程式: 从字串内萃取出子字串                 */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string[BUFSIZ / 10]; /* 字串阵列宣告     */
    char *substring;          /* 结果字串指标宣告 */
    int pos;                  /* 起始位置        */
    int len;                  /* 子字串长度      */

    printf("请输入字符串 ==> ");
    safe_gets(string, BUFSIZ / 10); /* 读取字串 */
    printf("请输入起始位置 ==> ");
    scanf("%d", &pos); /* 读取位置 */
    printf("请输入子字符串长度 ==> ");
    scanf("%d", &len);                    /* 读取长度    */
    substring = substr(string, pos, len); /* 萃取子字串  */
    printf("子字符串 %s\n", substring);

    return 0;
}
