/* ======================================== */
/*    程序实例: 2_4b.c                     */
/*    创建pointer数组和输出59到67的内容     */
/* ======================================== */
#include <stdio.h>

int main(int argc, char *argv[])
{
    int score[10] = {76, 85, 90, 67, 59, 79, 82,
                     95, 91, 65}; /* 学生成绩数组     */
    int pointer[101];             /* 指针数组         */
    int index;                    /* 数组索引变量     */
    int i;

    for (i = 0; i < 101; i++)
        pointer[i] = -1;     /* 设置数组初值为-1 */
    for (i = 0; i < 10; i++) /* 遍历成绩数组     */
    {
        index = score[i];
        pointer[index] = i; /* 创建pointer数组  */
    }

    for (i = 59; i < 68; i++) /* 输出阵列内容     */
        printf("数组元素: %d  内容: %d  \n", i, pointer[i]);

    return 0;
}