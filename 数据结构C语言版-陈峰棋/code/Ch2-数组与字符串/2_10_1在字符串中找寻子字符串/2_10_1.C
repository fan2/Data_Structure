/* ======================================== */
/*    程式实例: 2_10_1.c                     */
/*    在字符串中找寻子字符串                    */
/* ======================================== */
#include <stdio.h>
#include <string.h>

/* ---------------------------------------- */
/*  计算字符串长度                            */
/* ---------------------------------------- */
int strlen1(char *str) {
    int i;

    for (i = 0; str[i] != '\0'; i++); /* 用回路计算长度 */
    return i;
}

/* ---------------------------------------- */
/*  在字符串中找寻子字符串                      */
/* ---------------------------------------- */
int strindex(char *str1, char *str2) {
    int end, i, j;
    end = strlen1(str1) - strlen1(str2); /* 计算结束位置   */
    if (end > 0)                         /* 子字符串小於字符串 */
    {
        for (i = 0; i <= end; i++) /* 用回路比较各字元 */
            for (j = i; str1[j] == str2[j - i]; j++)
                /* 子字符串字结束，0前面所有的都相同，比较结束 */
                if (str2[j - i + 1] == '\0') return i; /* 找到了子字符串 */
    }
    return -1;
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
/*  主程式: 在字符串中找寻子字符串出现位置.       */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    char string[BUFSIZ / 10];    /* 字符串阵列宣告   */
    char substring[BUFSIZ / 10]; /* 子字符串阵列宣告 */
    int result;                  /* 找寻结果        */
    printf("请输入字符串 ==> ");
    safe_gets(string, BUFSIZ / 10); /* 读取字符串 */
    printf("请输入要搜索的子字符串 ==> ");
    safe_gets(substring, BUFSIZ / 10);    /* 读取子字符串 */
    result = strindex(string, substring); /* 搜寻子字符串 */
    if (result > 0)
        printf("子字符串 %s 在 %s 中的位置索引为 %d\n", substring, string,
               result);
    else
        printf("没有找到子字符串 %s\n", substring);

    return 0;
}
