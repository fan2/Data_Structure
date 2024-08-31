/* ======================================== */
/*    程序实例: 10_5b.c                      */
/*    希尔排序法(自定增量)                     */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_5B.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度       */
#define GAP_SCALE 6

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  希尔排序法                                */
/* ---------------------------------------- */
void shell(char *string, int count) {
    int shrink_gap[GAP_SCALE] = {11, 7, 5, 3, 2, 1};
    int gap;     // 每轮间隔量
    int base;    // 间隔集合后向基准元素索引
    char bench;  // 间隔集合内待插席位字符
    int pre;     // 间隔集合前向处理元素索引(base-N*gap)

    for (int i = 0; i < GAP_SCALE; i++) {
        gap = shrink_gap[i];  // 本轮 gap
        printf("gap[%d] = %d\n", i, gap);
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
                pre = pre - gap; /* 下一个处理位置     */
            }
            if (pre + gap != base) {
                string[pre + gap] = bench;  // 插入合适位置
                printf("    insert pos = %d, result = %s\n", pre + gap, string);
            }  // 已经就位，无需插入
        }
    }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序             */
/* ---------------------------------------- */
// test cases: polkjhnbvdsa
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要排序的字符串 ==> ");
    safe_gets(string, MAX); /* 读取字符串           */
    count = strlen(string); /* 计算字符串长度       */
    shell(string, count);   /* 希尔排序法         */
    /* 输出排序后字符串 */
    printf("\n输出排序结果: [%s]\n", string);

    return 0;
}
