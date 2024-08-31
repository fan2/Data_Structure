/* ======================================== */
/*    程序实例: 10_3.c                       */
/*    选择排序法                             */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_3.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度         */

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  选择排序法                                */
/* ---------------------------------------- */
void select(char *string, int count) {
    int min_idx;    // 当前最小字符位置
    char min_char;  // 当前最小字符值

    for (int i = 0; i < count - 1; i++) {
        min_idx = i;
        min_char = string[min_idx];
        /* 查找后缀 [i+1,count) 中最小的字符 */
        for (int j = i + 1; j < count; j++)
            if (string[j] < min_char) {
                /* 更新最小字符 */
                min_idx = j;
                min_char = string[j];
            }
        /* 交换本轮最小字符到标的位置(i) */
        if (min_idx != i) {
            printf("swap min [%d]:%c to target [%d]:%c, ", min_idx, min_char, i,
                   string[i]);
            string[min_idx] = string[i];
            string[i] = min_char;
            printf("string=%s\n", string);
        }  // 后缀没有更小
    }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序             */
/* ---------------------------------------- */
// test cases: lkjoab
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要排序的字符串 ==> ");
    safe_gets(string, MAX); /* 读取字符串           */
    count = strlen(string); /* 计算字符串长度        */
    select(string, count);  /* 选择排序法           */
    /* 输出排序后字符串 */
    printf("\n输出排序结果: [%s]\n", string);

    return 0;
}
