/* ======================================== */
/*    程式实例: 2_8c.c                     */
/*    使用字元阵列来储存格式字串            */
/* ======================================== */
/* 字符串本质上是以零结束的字符数组 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char format[] = {'T', 'h', 'e', ' ', 's', 'c', 'o',
                     'r', 'e', ' ', 'i', 's', ' ', '%',
                     'd', '\n', '\0'};
    int score; /* 成绩         */

    score = 100;                        /* 设定成绩内容 */
    printf("使用正常的格式化字符串\n"); /* 印出结果     */
    printf("The score is %d\n", score);
    printf("使用字符数组的格式化字符串\n");
    printf(format, score);

    return 0;
}