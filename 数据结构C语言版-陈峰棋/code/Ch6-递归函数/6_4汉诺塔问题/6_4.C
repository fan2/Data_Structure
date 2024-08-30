/* ======================================== */
/*    程式实例: 6_4.c                        */
/*    汉诺塔问题                             */
/* ======================================== */
#include <stdio.h>

/* ---------------------------------------- */
/*  汉诺塔问题的递归函数                       */
/* ---------------------------------------- */
#if 0
void hanoi(int dishs, int peg1, int peg2, int peg3) {
    if (dishs == 1) /* 终止条件：将最后一个盘子从木桩 1 搬到木桩 3 */
        printf("    1: %d -> %d\n", peg1, peg3);
    else {
        /* 第一步骤：将 n-1 个盘子经 peg3 中转，从 peg1 搬到 peg2 */
        hanoi(dishs - 1, peg1, peg3, peg2);
        printf("    2: %d -> %d\n", peg1, peg3);
        /* 第三步骤：将 n-1 个盘子经 peg1 中转，从 pge2 搬到 peg3 */
        hanoi(dishs - 1, peg2, peg1, peg3);
    }
}
#else
void hanoi(int dishes, int peg1, int peg2, int peg3) {
    if (dishes == 1)
        printf("    [1]: %d -> %d\n", peg1, peg3); // should never reach
    else if (dishes == 2) {
        printf("  [1]: %d -> %d\n", peg1, peg2);
        printf("  [2]: %d -> %d\n", peg1, peg3);
        printf("  [1]: %d -> %d\n", peg2, peg3);
    } else {
        /* 第一步骤：将 n-1 个盘子经 peg3 中转，从 peg1 搬到 peg2 */
        printf("<%d>: %d - %d -> %d\n", dishes-1, peg1, peg3, peg2);
        hanoi(dishes - 1, peg1, peg3, peg2);
        printf("</%d>: %d - %d -> %d\n", dishes-1, peg1, peg3, peg2);

        /* 第二步骤：将最底下的大盘子从 peg1 搬到 peg3 */
        printf("[%d]: %d -> %d\n", dishes, peg1, peg3);

        /* 第三步骤：将 n-1 个盘子经 peg1 中转，从 pge2 搬到 peg3 */
        printf("<%d>: %d - %d -> %d\n", dishes-1, peg2, peg1, peg3);
        hanoi(dishes - 1, peg2, peg1, peg3);
        printf("</%d>: %d - %d -> %d\n", dishes-1, peg2, peg1, peg3);
    }
}
#endif

/* ---------------------------------------- */
/*  主程式: 找出汉诺塔问题的解.                 */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    // 将 3 个盘子（大中小）从木桩 1，借助木桩 2，挪动到木桩 3。
    // 最大的盘子在底部，最小的盘子在顶部，类似健身房哑铃铁饼套桩。
    // hanoi(3, 1, 2, 3);
    hanoi(4, 1, 2, 3);

    return 0;
}
