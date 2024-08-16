/* ======================================== */
/*    程序实例: 1_2_3b.c                    */
/*    应用数组结构来模拟结构指针            */
/* ======================================== */
#include <stdio.h>

#define NUL -1

int main(int argc, char *argv[])
{
    int node[10] = {67, 80, 85, 83, 5, 65, 75, 91, 88, NUL};
    int begin;

    begin = 0; /* 第一位学生的索引 */

    printf("  id    math     english    computer \n");
    while (begin != NUL) /* 输出学生成绩     */
    {
        printf("  %c      %d         %d         %d    \n",
               node[begin], node[begin + 1], node[begin + 2],
               node[begin + 3]); /*A,C的ASCII码分别是65，67*/
        begin = node[begin + 4]; /* 下一个学生 ？      */
    }

    return 0;
}
