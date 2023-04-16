
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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

// find minIndex from rightside range [start, size-1]
int minIndexOfArray (int * const array, const int size, int start) {
    if (start < 0 || start > size-1) {
        assert(start >=0 && start <= size-1);
        return -1;
    }
    int minIndex = start; // 当前最小位置索引
    for (int i=start+1; i<size; i++) {
        if (array[i] < array[minIndex]) {
            minIndex = i;
        }
    }

    return minIndex;
}

// sort array in place
void selectionSort0(int *array, const int size) {
    for (int i=0; i<size-1; i++) { // round index
        int minIndex = minIndexOfArray(array, size, i);
        if (minIndex != i) { // swap min to rank i
            printf("minPos=%d, minIndex=%d\n", i, minIndex);
            swap(&array[i], &array[minIndex]);
        }
    }
}

// sort array in place
void selectionSort(int *array, const int size) {
    // minPos: round smallest index
    for (int i=0; i<size-1; i++) {
        int minIndex = i;
        for (int j=i+1; j<size; j++)
            if (array[j] < array[minIndex])
                minIndex = j;
        // swap minIndex to rank/minPos
        if (minIndex != i) {
            printf("swap(%d, %d)\n", minIndex, i);
            swap(&array[i], &array[minIndex]);
        } else {
            printf("keep %d as min\n", i);
        }
    }
}

// 测试用例：随机生成序列
void testRandomSort() {
    int nLen = 10, max = 20;
    int *A1 = randomList(nLen, max, 20);
    dumpArray("A1", A1, nLen);
    selectionSort(A1, nLen);
    dumpArray("sorted A1", A1, nLen);
    free(A1);
    printf("----------------------------------------\n");
}

// 测试用例：最左侧、最右侧部分已经排好序。
void testPartiallyOrdered() {
    int A2[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    int nLen = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, nLen);
    selectionSort(A2, nLen);
    dumpArray("sorted A2", A2, nLen);
    printf("----------------------------------------\n");
}

// 测试用例：完全逆序 & 初始有序
void testReverseOrdered() {
    int A3[] = {29, 28, 27, 26, 25, 24, 23, 22, 21, 20};
    int nLen = sizeof(A3)/sizeof(int);
    dumpArray("A3", A3, nLen);
    selectionSort(A3, nLen);
    dumpArray("sorted A3", A3, nLen);
    printf("--------------------\n");
    dumpArray("A3", A3, nLen);
    selectionSort(A3, nLen);
    dumpArray("resorted A3", A3, nLen);
    printf("----------------------------------------\n");
}

int main(int argc, char** argv) {
    // 测试用例1：随机生成10个整数
    // int nLen = 10, max = 10;
    // int *array = randomList(nLen, max, DEFAULT_SEED);
    // dumpArray("array", array, nLen);
    // selectionSort(array, nLen);
    // dumpArray("sorted array", array, nLen);
    // free(array);
    // printf("----------------------------------------\n");

    // testRandomSort();
    // testPartiallyOrdered();
    testReverseOrdered();

    return 0;
}