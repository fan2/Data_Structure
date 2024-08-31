/* ======================================== */
/*    程序实例: 10_5a.c                      */
/*    希尔排序法（源于插入排序）                */
/* ======================================== */
/*  排序策略：
 *    将待排序的元素根据指定的间隔分成数个集合，集合内插入排序；
 *    然后逐渐减少这个间隔，直到间隔为 1，最后一趟排序完成。
 */
// gcc -xc ../../utilities/safe_gets.c 10_5A.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度       */

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  希尔排序法                                */
/* ---------------------------------------- */
void shell(char *string, int count) {
    int gap;     // 每轮间隔量
    int base;    // 间隔集合后向基准元素索引
    char bench;  // 间隔集合内待插席位字符
    int pre;     // 间隔集合前向处理元素索引(base-N*gap)

    gap = count / 2;    // 初始间隔一半
    while (gap != 0) {  // 无可再分
        printf("gap = %d\n", gap);
        for (base = gap; base < count; base++) {
            // 以下为本轮间隔集合 [base, base-gap, base-2*gap, ..., ]
            // 内的插入排序
            bench = string[base];
            printf("  bench = [%d]:%c\n", base, bench);
            pre = base - gap;  // 第一个前向处理位置
            while (pre >= 0 && bench < string[pre]) {
                string[pre + gap] = string[pre];  // 向后挪动
                printf("    move %d:%c forward to %d:\n", pre, string[pre],
                       pre + gap);
                pre = pre - gap;  // 下一个前向处理位置
            }
            if (pre + gap != base) {
                string[pre + gap] = bench;  // 插入合适位置
                printf("    insert pos = %d, result = %s\n", pre + gap, string);
            }  // 已经就位，无需插入
        }
        gap = gap / 2;  // 间隔再缩小一半
    }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序              */
/* ---------------------------------------- */
// test cases: agdfshck
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要排序的字符串 ==> ");
    safe_gets(string, MAX); /* 读取字符串         */
    count = strlen(string); /* 计算字符串长度      */
    shell(string, count);   /* 希尔排序法         */
    /* 输出排序后字符串 */
    printf("\n输出排序结果: [%s]\n", string);

    return 0;
}
