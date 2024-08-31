/* ======================================== */
/*    程序实例: 10_2b.c                      */
/*    冒泡排序法                             */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_2B.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度           */

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  冒泡排序法                                */
/* ---------------------------------------- */
void bubble(char *string, int count) {
    char temp;

    /* j 为每轮右侧冒泡标的/位置：最大，次大，...，大，次小，最小*/
    for (int j = count - 1; j > 0; j--) {
        for (int i = 0; i < j; i++)
            if (string[i] > string[i + 1]) {
                /* 相邻元素逆序交换*/
                printf("    swap [%d]:%c<=>[%d]:%c, ", i, string[i], i + 1,
                    string[i + 1]);
                temp = string[i + 1];
                string[i + 1] = string[i];
                string[i] = temp;
                printf("string=%s\n", string);
            }

        /* 输出本轮交换后的字符串  */
        // printf("输出结果: [%s]\n", string);
        printf("max[%d] = %c\n", j, string[j]);
    }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序             */
/* ---------------------------------------- */
// test cases: fedcba; lkjoab
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
