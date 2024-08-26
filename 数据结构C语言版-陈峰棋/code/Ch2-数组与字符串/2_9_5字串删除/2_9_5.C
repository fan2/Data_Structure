/* ======================================== */
/*    程式实例: 2_9_5.c                      */
/*    子串删除                               */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  子串删除: str 从索引 pos-1 开始的 len 个元素 */
/* ---------------------------------------- */
char *strdel(char *str, int pos, int len) {
    int i;

    pos--; /* 计算子串的开始 */
    for (i = pos + len; str[i] != '\0'; i++)
        str[i - len] = str[i];  // shrink left
    str[i - len] = '\0';        /* 新的字串结束   */
    return str;
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
/*  主程式                                  */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string[BUFSIZ / 10]; /* 字串阵列宣告 */
    int pos;                  /* 删除位置     */
    int len;                  /* 删除长度     */

    printf("请输入原始字符串 ==> ");
    safe_gets(string, BUFSIZ / 10); /* 读取字串     */
    printf("请输入删除位置 ==> ");
    scanf("%d", &pos); /* 读取位置     */
    printf("请输入删除长度 ==> ");
    scanf("%d", &len);        /* 读取长度     */
    strdel(string, pos, len); /* 删除字串     */
    printf("删除后的字符串是 %s\n", string);

    return 0;
}
