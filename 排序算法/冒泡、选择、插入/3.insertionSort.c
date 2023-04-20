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
    if (*a != *b) {
        int t = *b;
        *b = *a;
        *a = t;
    }
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

void dumpSubArray(const char* name, const int *array, const int low, const int high) {
    if (strlen(name) > 0) {
        printf("%s[%d:%d] = ", name, low, high);
    }
    printf("{");
    for (int i=low; i<=high; i++) {
        printf("%d", array[i]);
        if (i < high) {
            printf(", ");
        }
    }
    printf("}\n");
}

// 折半查找元素e在有序数组array[low,high]中的预期插入位置
int bSearch(int *array, int low, int high, const int e) {
    // 三个及以上，收缩到两个
    while (high-low > 1) {
        int mid = (low+high)/2;
        if (e < array[mid]) {
            high = mid;
        } else {
            low = mid;
        }
    }
    int pos = 0;
    // 原本一/两个或收缩到两个
    if (e < array[low])
        pos = low; // 放左边，需后移腾位
    else if (e > array[high])
        pos = high+1; // 放右边（保持原位）
    else
        pos = high; // 放中间，需后移腾位
    printf("bSearch e=%d, low=%d, high=%d, pos=%d\n", e, low, high, pos);
    return pos;
}

// sort array in place
// 通过交换消除逆序，逐步将新元素移动到合适位置。
// 尽管代码简洁，但由于一次交换需要三次赋值，故性能最差。
void insertionSort0(int *array, const int size) {
    for (int i=1; i<size; i++) {
        printf("----------i=%d--------\n", i);
        // 前向比较，逆序交换
        for (int j=i; j>0 && array[j-1]>array[j]; j--) {
            printf("    i=%d, j=%d swap backward\n", i, j);
            swap(&array[j-1], &array[j]);
        }
    }
}

// sort array in place
void insertionSort1(int *array, const int size) {
    int current = 0;
    for (int i=1; i<size; i++) {
        current = array[i]; // 待插基数
        int j = i; // 待插位置
        // 顺序遍历基数前的有序数列，寻找合适插入位置
        // for (j=0; j<i&&current>array[j]; j++);
        // 折半查找插入位置
        j = bSearch(array, 0, i-1, current);
        printf("i=%d, e=%d, j=%d\n", i, current, j);
        // 如果j=i，代表i刚好在正确的位置上，可判断if(j < i)省掉等位赋值。
        // 将 [j, i-1] 整体右移一位到 [j+1, i]
        for (int k=i-1; k>=j; k--) {
            array[k+1] = array[k];
        }
        // 将基数插入合适位置，相同元素左插
        array[j] = current;
        dumpArray("insertion array", array, size);
        printf("--------------------\n");
    }
}

// sort array in place
// 逆序 [i-1, 0]，方便后移碎步腾挪
void insertionSort2(int *array, const int size) {
    for (int i=1; i<size; i++) {
        int current = array[i]; // 待插基数
        printf("----------------------------------------\n");
        // 逆序遍历基数前的有序数列，寻找合适插入位置
        int j = i-1;
        for (; j>=0; j--) {
            if (current < array[j]) {
                printf("    i=%d, j=%d move forward\n", i, j);
                array[j+1] = array[j]; // array[j]向后移动
            } else {
                break; // terminate
            }
        }
        if (j+1 != i) {
            printf("i=%d, e=%d, move to j+1=%d\n", i, current, j+1);
            array[j+1] = current; // 插入到索引j后
        } else { // 保持不变
            printf("i=%d, e=%d, keep still\n", i, current);
        }
    }
}

// sort array in place
// optimize the for-loop
void insertionSort3(int *array, const int size) {
    int j;
    for (int i=1; i<size; i++) {
        int current = array[i]; // 待插基数
        printf("----------------------------------------\n");
        //逆序遍历基数前的有序数列，寻找合适插入位置
        for (j=i-1; j>=0 && current<array[j]; j--) {
            printf("    i=%d, j=%d move forward\n", i, j);
            array[j+1] = array[j]; // array[j]向后移动
        }
        if (j+1 != i) {
            printf("i=%d, e=%d, move to j+1=%d\n", i, current, j+1);
            array[j+1] = current; // 插入到索引j后
        } else { // 保持不变
            printf("i=%d, e=%d, keep still\n", i, current);
        }
    }
}

// sort array in place
// for-else-break 改为 while
void insertionSort4(int *array, const int size) {
    for (int i=1; i<size; i++) {
        int current = array[i]; // 待插基数
        printf("----------------------------------------\n");
        //逆序遍历基数前的有序数列，寻找合适插入位置
        int j = i-1;
        while (j>=0 && current<array[j]) {
            printf("    i=%d, j=%d move forward\n", i, j);
            array[j+1] = array[j]; // array[j]向后移动
            j--;
        }
        if (j+1 != i) {
            printf("i=%d, e=%d, move to j+1=%d\n", i, current, j+1);
            array[j+1] = current; // 插入到索引j后
        } else { // 保持不变
            printf("i=%d, e=%d, keep still\n", i, current);
        }
    }
}

// 测试用例：随机生成序列
void testRandomSort() {
    int nLen = 10, max = 20;
    int *A1 = randomList(nLen, max, 20);
    dumpArray("A1", A1, nLen);
    insertionSort3(A1, nLen);
    dumpArray("sorted A1", A1, nLen);
    free(A1);
    printf("----------------------------------------\n");
}

// 测试用例：最左侧、最右侧部分已经排好序。
void testPartiallyOrdered() {
    int A2[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    int nLen = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, nLen);
    insertionSort3(A2, nLen);
    dumpArray("sorted A2", A2, nLen);
    printf("----------------------------------------\n");
}

// 测试用例：完全逆序 & 初始有序
void testReverseOrdered() {
    int A3[] = {29, 28, 27, 26, 25, 24, 23, 22, 21, 20};
    int nLen = sizeof(A3)/sizeof(int);
    dumpArray("A3", A3, nLen);
    insertionSort3(A3, nLen);
    dumpArray("sorted A3", A3, nLen);
    printf("--------------------\n");
    dumpArray("A3", A3, nLen);
    insertionSort3(A3, nLen);
    dumpArray("resorted A3", A3, nLen);
    printf("----------------------------------------\n");
}

int main(int argc, char** argv) {
    // 测试用例1：随机生成10个整数
    int nLen = 10, max = 10;
    int *array = randomList(nLen, max, DEFAULT_SEED);
    dumpArray("array", array, nLen);
    insertionSort1(array, nLen);
    dumpArray("sorted array", array, nLen);
    free(array);
    printf("----------------------------------------\n");

    // testRandomSort();
    // testPartiallyOrdered();
    // testReverseOrdered();

    return EXIT_SUCCESS;
}