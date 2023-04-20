#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_SEED 0

// 生成 n 个取值范围是 [1, max] 的随机数
int *randomList(int n, int max, unsigned seed) {
    /* randomize seed: random initializing of rand() */
    if (seed != DEFAULT_SEED) {
        srand(seed);
    } else { // default
        srand((unsigned)time(NULL));
    }
    int *randoms = (int *)malloc(n * sizeof(int));
    if (!randoms) {
        printf("randomList malloc failed!\n");
        return NULL;
    }
    memset(randoms, 0, n * sizeof(int));
    for (int i=0; i<n; i++) {
        int random = rand() % max + 1;
        randoms[i] = random;
    }

    return randoms; // free by caller
}

void swap(int *a, int *b) {
    int t = *b;
    *b = *a;
    *a = t;
}

void dumpArray(const char* name, const int *array, const int size) {
    if (strlen(name) > 0) {
        printf("%s = ", name);
    }
    printf("{");
    for (int i=0; i<size; i++) {
        printf("%d", array[i]);
        if (i < size-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

// sort array in place
void bubbleSort0(int *array, const int size) {
    int i, j;
    for (i=size-1; i>=1; i--) { // round bubble position
        for (j=1; j<=i; j++) {
            // swap if prev>current in disorder
            if (array[j-1] > array[j]) {
                printf("    swap (%d, %d)\n", j, j-1);
                swap(&array[j-1], &array[j]);
            }
        }
        printf("top = %d, max = %d\n", i, array[j-1]);
    }
}

// optimization for bubbleSort0
void bubbleSort1(int *array, const int size) {
    int i, j;
    int swapped = 0; // sentry/informer
    for (i=size-1; i>=1; i--) { // round bubble position
        swapped = 0;
        for (j=1; j<=i; j++) {
            // swap if prev>current in disorder
            if (array[j-1] > array[j]) {
                printf("    swap (%d, %d)\n", j, j-1);
                swap(&array[j-1], &array[j]);
                swapped = 1;
            } else {
                printf("    keep (%d, %d)\n", j, j-1);
            }
        }
        if (swapped) {
            printf("top = %d, max = %d\n", i, array[i]);
        } else {
            // 如果本轮没有发生交换，则表明已经排好序，退出循环。
            printf("top = %d, no swap and break\n", i);
            break;
        }
    }
}

// bubbleSort1 variant with while-for
void bubbleSort2(int *array, const int size) {
    int done = 0; // sentry/informer
    int top = size-1; // round bubble position
    while (!done && top>=1) {
        done = 1;
        for (int j=1; j<=top; j++) {
            // swap if prev>current in disorder
            if (array[j-1] > array[j]) {
                printf("    swap (%d, %d)\n", j, j-1);
                swap(&array[j-1], &array[j]);
                done = 0;
            } else {
                printf("    keep (%d, %d)\n", j, j-1);
            }
        }
        if (!done) {
            printf("top = %d, max = %d\n", top, array[top]);
            // 本轮最大已经冒泡至末端，缩小右侧索引边界。
            // decrease right endpoint, shrink compare-swap range
            top--;
        } else {
            // 如果本轮没有发生交换，则表明已经排好序，退出循环。
            printf("top = %d, no swap and break\n", top);
            break;
        }
    }
}

// sort array in place, shrink compare-swap boundary
void bubbleSort3(int *array, const int size) {
    int top = size-1; // round bubble position
    int swapTop = 0;
    // 前向比较边界top=1(1,0)，前向比较越界top=0(0,-1)
    while (top > 0) {
        swapTop = 1; // no need next swap
        for (int j=1; j<=top; j++) {
            // swap if prev>current in disorder
            if (array[j-1] > array[j]) {
                printf("    swap (%d, %d)\n", j, j-1);
                swap(&array[j-1], &array[j]);
                // record as next top expectation
                swapTop = j;
            } else {
                printf("    keep (%d, %d)\n", j, j-1);
            }
        }
        // 打印本轮冒泡位置和下一轮冒泡位置
        printf("top = %d, next swapTop = %d\n", top, swapTop-1);
        // 本轮如果没交换swapTop=1；如果有交换，swapTop为本轮冒泡位置，下次冒泡位置缩小到swapTop-1。
        top = swapTop-1; // adjust next top, shrink compare-swap boundary
    }
}

// 对比测试用例：随机生成序列
void testRandomSort() {
    int nLen = 10, max = 20;
    int *A11 = randomList(nLen, max, 20);
    dumpArray("A11", A11, nLen);
    bubbleSort2(A11, nLen);
    dumpArray("sorted A11", A11, nLen);
    free(A11);
    printf("--------------------\n");
    int *A12 = randomList(nLen, max, 20);
    dumpArray("A12", A12, nLen);
    bubbleSort3(A12, nLen);
    dumpArray("sorted A12", A12, nLen);
    free(A12);
    printf("----------------------------------------\n");
}

// 对比测试用例：最左侧、最右侧部分已经排好序。
void testPartiallyOrdered() {
    // 对比测试 bubbleSort2 和 bubbleSort3
    int A21[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    int nLen = sizeof(A21)/sizeof(int);
    dumpArray("A21", A21, nLen);
    bubbleSort2(A21, nLen);
    dumpArray("sorted A21", A21, nLen);
    printf("--------------------\n");
    int A22[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    nLen = sizeof(A22)/sizeof(int);
    dumpArray("A22", A22, nLen);
    bubbleSort3(A22, nLen);
    dumpArray("sorted A22", A22, nLen);
    printf("----------------------------------------\n");
}

// 测试用例：完全逆序 & 初始有序
void testReverseOrdered() {
    int A3[] = {29, 28, 27, 26, 25, 24, 23, 22, 21, 20};
    int nLen = sizeof(A3)/sizeof(int);
    dumpArray("A3", A3, nLen);
    bubbleSort3(A3, nLen);
    dumpArray("sorted A3", A3, nLen);
    printf("--------------------\n");
    dumpArray("A3", A3, nLen);
    bubbleSort3(A3, nLen);
    dumpArray("resorted A3", A3, nLen);
    printf("----------------------------------------\n");
}

int main(int argc, char** argv) {
    // 测试用例1：随机生成10个整数
    // int nLen = 10, max = 10;
    // int *array = randomList(nLen, max, DEFAULT_SEED);
    // dumpArray("array", array, nLen);
    // bubbleSort2(array, nLen);
    // dumpArray("sorted array", array, nLen);
    // free(array);
    // printf("----------------------------------------\n");

    testRandomSort();
    // testPartiallyOrdered();
    // testReverseOrdered();

    return EXIT_SUCCESS;
}