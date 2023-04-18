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
void shellSort0(int *array, const int size) {
    int offset = size / 2; // 初始间隔
    while (offset > 0) {
        printf("--------------- offset = %d ---------------\n", offset);
        for (int i=offset; i<size; i++) {
            int j=i; // right start
            printf("--------------- right = %d\n", j);
            for (int k=i-offset; k>=0; k-=offset) {
                if (array[j] < array[k]) {
                    swap(&array[j], &array[k]);
                    printf("    swap (%d, %d)\n", j, k);
                } else {
                    printf("    keep (%d, %d)\n", j, k);
                }
                j = k; // set as next right
            }
        }
        offset /= 2;
    }
}

// 基于交换的插入排序法，可以理解为 offset 间隔固定为 1。
// void insertionSort(int *array, const int size) {
//     for (int i=1; i<size; i++) {
//         // 前向比较，逆序交换
//         for (int j=i; j>0 && array[j-1]>array[j]; j--) {
//             printf("    i=%d, j=%d swap backward\n", i, j);
//             swap(&array[j-1], &array[j]);
//         }
//     }
// }

// sort array in place(optimize for-loop)
void shellSort1(int *array, const int size) {
    int offset = size / 2; // 初始间隔
    while (offset > 0) {
        printf("--------------- offset = %d ---------------\n", offset);
        for (int i=offset; i<size; i++) {
            printf("--------------- right = %d\n", i);
            for (int k=i; k>=offset; k-=offset) {
                if (array[k] < array[k-offset]) {
                    swap(&array[k], &array[k-offset]);
                    printf("    swap (%d, %d)\n", k, k-offset);
                } else {
                    printf("    keep (%d, %d)\n", k, k-offset);
                }
            }
        }
        dumpArray("shelled array", array, size);
        offset /= 2;
    }
}

// 测试用例：随机生成序列
void testRandomSort() {
    int nLen = 10, max = 20;
    int *A1 = randomList(nLen, max, 20);
    dumpArray("A1", A1, nLen);
    shellSort1(A1, nLen);
    dumpArray("sorted A1", A1, nLen);
    free(A1);
    printf("----------------------------------------\n");
}

// 测试用例：最左侧、最右侧部分已经排好序。
void testPartiallyOrdered() {
    int A2[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    int nLen = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, nLen);
    shellSort1(A2, nLen);
    dumpArray("sorted A2", A2, nLen);
    printf("----------------------------------------\n");
}

// 测试用例：完全逆序 & 初始有序
void testReverseOrdered() {
    int A3[] = {29, 28, 27, 26, 25, 24, 23, 22, 21, 20};
    int nLen = sizeof(A3)/sizeof(int);
    dumpArray("A3", A3, nLen);
    shellSort1(A3, nLen);
    dumpArray("sorted A3", A3, nLen);
    printf("--------------------\n");
    dumpArray("A3", A3, nLen);
    shellSort1(A3, nLen);
    dumpArray("resorted A3", A3, nLen);
    printf("----------------------------------------\n");
}

int main(int argc, char** argv) {
    // 测试用例1：随机生成10个整数
    // int nLen = 10, max = 10;
    // int *array = randomList(nLen, max, DEFAULT_SEED);
    // dumpArray("array", array, nLen);
    // shellSort1(array, nLen);
    // dumpArray("sorted array", array, nLen);
    // free(array);
    // printf("----------------------------------------\n");

    testRandomSort();
    // testPartiallyOrdered();
    // testReverseOrdered();

    return 0;
}