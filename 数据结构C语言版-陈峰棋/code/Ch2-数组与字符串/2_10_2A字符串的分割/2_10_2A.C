/* ======================================== */
/*    程式实例: 2_10_2a.c                    */
/*    字符串的分割                            */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  以空格符分割字符串                         */
/* ---------------------------------------- */
// char *strtok( char *str, const char *delim );
int token(char *str1, char *str2, int pos) {
    int i, j;

    i = pos;               /* 从分割位置开始   */
    while (str1[i] == ' ') /* 跳过之前空白字元 */
        i++;
    if (str1[i] != '\0') /* 是不是字符串结束   */
    {
        j = 0; /* 找下一个空白字元 */
        while (str1[i] != '\0' && str1[i] != ' ') {
            str2[j] = str1[i]; /* 拷贝非空白字元 */
            i++;
            j++;
        }
        str2[j] = '\0'; /* 分割字符串结束字元 */
        return i;       /* 传回目前位置      */
    } else
        return -1; /* 分割结束        */
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
/*  主程式                                   */
/* ---------------------------------------- */
// test case: "This is a book."
int main(int argc, char *argv[]) {
    char string[BUFSIZ / 10];       /* 字符串阵列宣告     */
    char token_string[BUFSIZ / 50]; /* 分割字符串宣告     */
    int pos;                        /* 分割位置         */

    printf("请输入字符串 ==> ");
    safe_gets(string, BUFSIZ / 10); /* 读取字符串      */
    pos = 0;                        /* 设定分割位置初值 */
    printf("分割结果:\n");
    /* 分割字符串直到字符串结束 */
    while ((pos = token(string, token_string, pos)) != -1)
        printf("%s\n", token_string); /* 印出各分割字符串 */

    return 0;
}
