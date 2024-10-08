/* ======================================== */
/*    程式实例: 2_8a.c                     */
/*    输入字串且将之印出                    */
/* ======================================== */
/* 纯字符数组 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char string[100]; /* 字串阵列宣告     */
    char ch;          /* 输入字元        */
    int i;

    for (i = 0; i < 100; i++) /* 清除字串阵列内容 */
        string[i] = ' ';

    putchar('?'); /* 列出提示输入讯息 */
    i = 0;
    while ((ch = getchar()) != '\n')    /* 输入字元   */
    {
        string[i] = ch;                 /* 存入字串内 */
        i++;
    }

    for (i = 0; i < 100; i++)   /* 印出字串内容 */
        putchar(string[i]);
    putchar('\n');              /* 换行       */

    return 0;
}