/* ======================================== */
/*    程序实例: 10_2c.c                      */
/*    冒泡排序法(另一种方法)                   */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_2C.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度           */

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  冒泡排序法                                */
/* ---------------------------------------- */
// 优化一下循环次数
void bubble(char *string, int count) {
    int i, j, swapped;
    char temp;

    j = count;  // 优化扫描个数

    swapped = 1; /* 标记是否有交换 */
    while (swapped) {
        swapped = 0; /* 初始本轮尚无交换 */
        j--;

        for (i = 0; i < j; i++)
            if (string[i] > string[i + 1]) {
                /* 相邻元素逆序交换*/
                printf("    swap [%d]:%c<=>[%d]:%c, ", i, string[i], i + 1,
                       string[i + 1]);
                temp = string[i + 1];
                string[i + 1] = string[i];
                string[i] = temp;
                swapped = 1; /* 本次有交换 */
                printf("string=%s\n", string);
            }

        if (swapped) { /* 本轮有交换 */
            // printf("输出结果: [%s]\n", string);
            printf("max[%d] = %c\n", j, string[j]);
        }  // else break; // 可提前结束
    }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串後将字符串排序             */
/* ---------------------------------------- */
// test cases: lkjoab
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要排序的字符串 ==> ");
    safe_gets(string, MAX); /* 读取字符串     */
    count = strlen(string); /* 计算字符串长度  */
    bubble(string, count);  /* 冒泡排序法     */
    /* 输出排序后字符串 */
    printf("\n输出排序结果: [%s]\n", string);

    return 0;
}
