#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_SEED 0

#define PARTITION_SCHEME_LOMUTO     0
#define PARTITION_SCHEME_HOARE      1
#define PARTITION_SCHEME_COCKTAIL   2
#define PARTITION_SCHEME_DEFAULT    PARTITION_SCHEME_LOMUTO

typedef enum {
    PIVOT_HEAD,     // 选择第一个元素作为基准
    PIVOT_TAIL,     // 选择最后一个元素作为基准
    PIVOT_MEDIAN,   // 选择中间元素作为基准
} PIVOT_POSITION;

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
    if (*a == *b) { // 值相同，免交换
        return;
    }
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

void dumpSubArray(const char* name, const int *array, const int low, const int high) {
    if (strlen(name) > 0) {
        printf("%s = ", name);
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

// 对子数组 A[l:h] 进行切割，返回pivot分治索引
// 如果没有发生交换，说明[l:h]已经就序，但为了保障递归条件，
// 即使每一条分治最终都抵达 base case，这里不进行特殊判断。
int partition_Lomuto(int *array, const int low, const int high, const PIVOT_POSITION pivotPos) {
    // 打印调试信息
    char szName[128];
    sprintf(szName, "array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    // 最右小值索引（小于基准元素的区域边界）
    int i = -1;
    if (pivotPos == PIVOT_HEAD) {
        // 初始虚设小值位置为枢轴自身
        i = low;
        // 遍历将右侧的小值移到左边
        for (int j=low+1; j<=high; j++) {
            if (array[j] < array[low]) // < pivot
                // 如果j=i+1，即小值A[j]已在其位，可判断不交换
                swap(&array[j], &array[++i]);
        }
        // 如果i=low，for循环未找到小值，即pivot最小，已经在左边，可判断不交换
        // 如果i=high，for循环全都是小值，即pivot最大，交换到最左边
        // 将首pivot交换到最右小值位置，本轮分治完成：[小值],pivot,[大值]
        swap(&array[low], &array[i]);
    } else if (pivotPos == PIVOT_TAIL) {
        // 初始虚设小值位置在遍历的首元素之前，下一个小值为++i=0
        i = low-1;
        // 遍历将右侧的小值移到左边
        for (int j=low; j<high; j++) {
            if (array[j] < array[high]) // < pivot
                // 如果j=i+1，即小值A[j]已在其位，可判断不交换
                swap(&array[j], &array[++i]);
        }
        // 如果i=low，for循环未找到小值，即pivot最小，交换到最左边
        // 如果i=high，for循环前面的都是小值，即pivot最大，已经在右边，可判断不交换
        // 将尾pivot交换归位到最右小值右边，本轮分治完成：[小值],pivot,[大值]
        swap(&array[high], &array[++i]);
    }
    // 打印调试信息
    sprintf(szName, "Lomuto array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    printf("pivot_index = %d\n", i);
    // 返回 pivot 索引
    return i;
}

// sort array in place
// 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
void quickSort_Lomuto(int *array, const int low, const int high) {
    // base case 1: overlap: low=high，只有一个元素
    // base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if (low >= high)
        return;
    // in-place compare and swap
    int pivot_index = partition_Lomuto(array, low, high, PIVOT_HEAD);
    // recursion for left small part
    quickSort_Lomuto(array, low, pivot_index-1);
    // recursion for right big part
    quickSort_Lomuto(array, pivot_index+1, high);
}

void test_qsort_Lomuto() {
    int nLen = 10, max = 10;
    int *array = randomList(nLen, max, DEFAULT_SEED);
    dumpArray("array", array, nLen);
    quickSort_Lomuto(array, 0, nLen-1);
    dumpArray("sorted array", array, nLen);
    free(array);
    printf("----------------------------------------\n");

    // 测试用例：最左侧、最右侧部分已经排好序。
    int A1[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    nLen = sizeof(A1)/sizeof(int);
    dumpArray("A1", A1, nLen);
    quickSort_Lomuto(A1, 0, nLen-1);
    dumpArray("sorted A1", A1, nLen);
    printf("----------------------------------------\n");

    // 测试用例：来源于 geeksforgeeks
    int A2[] = {10, 80, 30, 90, 40, 50, 70};
    nLen = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, nLen);
    quickSort_Lomuto(A2, 0, nLen-1);
    dumpArray("sorted A2", A2, nLen);
}

// 1. 如果原本整体有序（[1,2,3,4,5]），则首元素pivot必然最小，双边遍历下来，left=1、right=low（=p=0，抵达左边界）。
// 2. 如果原本不存在逆序对（[3,1,2,4,5]），则双边遍历下来，left=3、right=2，right即是左侧小值边界（最右小值）。
// 3. 如果原本存在逆序对，则双边遍历下来 left<right，经过交换消除完逆序对后，下一轮循环回归到情形2。
// 最后，将pivot与最右小值（right）交换使其归位。
int partition_Hoare(int *array, const int low, const int high, PIVOT_POSITION pivotPos) {
    // 打印调试信息
    char szName[128];
    sprintf(szName, "array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    // 初始化基准（支点、枢轴）
    int p = 0, pivot = 0;
    if (pivotPos == PIVOT_HEAD) {
        p = low, pivot = array[p];
        // 初始化左右游标
        int left = low+1, right = high;
        while (left <= right) { // 至少两个元素
            // 从左向右查找大值索引
            while (left<=high && array[left]<=pivot)
                left++; // 没找到大值时，left=high+1
            // 从右向左查找小值索引
            while (right>low && array[right]>=pivot)
                right--; // 没找到小值时，right=low
            // 逆序分布两边，交换消除逆序对
            if (left < right)
                swap(&array[left], &array[right]);
        }

        if (p != right) { // 排除1-原本整体有序
            // 在2中，right是左侧小值边界（最右小值），将pivot与right交换即可使其归位。
            swap(&array[right], &array[p]);
            p = right; // 更新基准索引
        }
    } else if (pivotPos == PIVOT_TAIL) {
        // 固定第一个元素作为基准元素
        p = high, pivot = array[p];
        // 初始化左右游标
        int left = low, right = high-1;
        while (left <= right) { // 至少两个元素
            // 从左向右查找大值索引
            while (left<high && array[left]<=pivot)
                left++; // 没找到大值时，left=high
            // 从右向左查找小值索引
            while (right>=low && array[right]>=pivot)
                right--; // 没找到小值时，right=low-1
            // 逆序分布两边，交换消除逆序对
            if (left < right)
                swap(&array[left], &array[right]);
        }

        if (p != left) { // 排除1-原本整体有序
            // 在2中，left是右侧大值边界（最左小值），将pivot与right交换即可使其归位。
            swap(&array[left], &array[p]);
            p = left; // 更新基准索引
        }
    }

    // 本轮分治完成：[小值],pivot,[大值]
    // 打印调试信息
    sprintf(szName, "Hoare array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    printf("pivot_index = %d\n", p);

    // 返回 pivot 索引
    return p;
}

// sort array in place
// 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
void quickSort_Hoare(int *array, const int low, const int high) {
    // base case 1: overlap: low=high，只有一个元素
    // base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if (low >= high)
        return;
    // in-place compare and swap
    int pivot_index = partition_Hoare(array, low, high, PIVOT_TAIL);
    // recursion for left small part
    quickSort_Hoare(array, low, pivot_index-1);
    // recursion for right big part
    quickSort_Hoare(array, pivot_index+1, high);
}

void test_qsort_Hoare() {
    int nLen = 10, max = 10;
    int *array = randomList(nLen, max, DEFAULT_SEED);
    dumpArray("array", array, nLen);
    quickSort_Hoare(array, 0, nLen-1);
    dumpArray("sorted array", array, nLen);
    free(array);
    printf("----------------------------------------\n");

    // 测试用例：最左侧、最右侧部分已经排好序。
    int A1[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    nLen = sizeof(A1)/sizeof(int);
    dumpArray("A1", A1, nLen);
    quickSort_Hoare(A1, 0, nLen-1);
    dumpArray("sorted A1", A1, nLen);
    printf("----------------------------------------\n");

    // 测试用例：https://en.wikipedia.org/wiki/File:Quicksort-example.gif
    int A2[] = {6, 5, 3, 1, 8, 7, 2, 4};
    nLen = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, nLen);
    quickSort_Hoare(A2, 0, nLen-1);
    dumpArray("sorted A2", A2, nLen);
    printf("----------------------------------------\n");

    // int A3[] = {'d', 'e', 'a', 'c', 'f', 'b', 'h', 'g'};
    int A3[] = {100, 101, 97, 99, 102, 98, 104, 103};
    nLen = sizeof(A3)/sizeof(int);
    dumpArray("A3", A3, nLen);
    quickSort_Hoare(A3, 0, nLen-1);
    dumpArray("sorted A3", A3, nLen);
}

// 对子数组 A[l:h] 进行切割，返回pivot分治索引
// 该分治策略采用的是单边双向摇摆，有点类似鸡尾酒冒泡排序。
// 三元组通过左右两次交换，将小值交换到左边、大值交换到右边，
// 从而生成以pivot为轴心的局部有序（升序）三元组：small<pivot<big。
int partition_Cocktail_0(int *array, const int low, const int high) {
    // 打印调试信息
    char szName[128];
    sprintf(szName, "array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    // 选择第一个元素作为基准，本轮切割中pivot基准值保持不变，但其索引会动态更新。
    int p = low, pivot = array[p];
    // 初始化左右游标
    int left = low, right = high;
    while (left < right) {
        // 每轮循环，复位左右游标，重新从两端向中间扫描逆序对
        // 1.1 从右向左查找小值，找不到=low-1
        for (right=high; right>=low && array[right]>=pivot; right--);
        // 1.2 找到右边小值，与基准交换
        if (right > p) {
            swap(&array[right], &array[p]);
            p = right; // 更新基准索引
        }
        // 2.1 从左向右查找大值，找不到=high+1
        for (left=low; left<=high && array[left]<=pivot; left++);
        // 2.2 找到左边大值，与基准交换（右边大值，符合顺序，无需交换）。
        if (left < p) {
            swap(&array[left], &array[p]);
            p = left; // 更新基准索引
        }
        // left>=right: 重叠（overlap）或交叉（cross），while循环退出
    }

    // 本轮分治完成：[小值],pivot,[大值]
    // 打印调试信息
    sprintf(szName, "Cocktail array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    printf("pivot_index = %d\n", p);
    // 返回 pivot 索引
    return p;
}

// partition_Cocktail_0 两次交换实现有序三元，消除完逆序对，pivot已就位。
// 这里每轮while不复位左右游标，继续从上一次的游标位置向中间压缩推进。
// 两次赋值半交换，实现大小值交换位置，记录下pivot位置，最终归位。
int partition_Cocktail(int *array, const int low, const int high) {
    // 打印调试信息
    char szName[128];
    sprintf(szName, "array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    // 选择第一个元素作为基准，本轮切割中pivot基准值保持不变，但其索引会动态更新。
    int p = low, pivot = array[p];
    // 初始化左右游标
    int left = low+1, right = high;
    while (left <= right) { // 至少两个元素
        // 1.1 从右向左查找小值
        while(right>low && array[right]>=pivot)
            right--; // 没找到小值时，right=low
        // 1.2 找到右边小值，挪到左边
        if (right > p) {
            array[p] = array[right];
            p = right; // 暂存基准索引
        }
        // 2.1 从左向右查找大值，找不到=high+1
        while(left<=high && array[left]<=pivot)
            left++;
        // 2.2 找到左边大值，挪到右边
        if (left < p) {
            array[right] = array[left];
            p = left; // 暂存基准索引
        }
        // left>right: 交叉（cross），while循环退出
    }

    // 右、左摇摆消除逆序对后，pivot归位
    array[p] = pivot;

    // 本轮分治完成：[小值],pivot,[大值]
    // 打印调试信息
    sprintf(szName, "Cocktail array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    printf("pivot_index = %d\n", p);
    // 返回 pivot 索引
    return p;
}

// sort array in place
// 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
void quickSort_Cocktail(int *array, const int low, const int high) {
    // base case 1: overlap: low=high，只有一个元素
    // base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if (low >= high)
        return;
    // in-place compare and swap
    int pivot_index = partition_Cocktail(array, low, high);
    // recursion for left small part
    quickSort_Cocktail(array, low, pivot_index-1);
    // recursion for right big part
    quickSort_Cocktail(array, pivot_index+1, high);
}

void test_qsort_Cocktail() {
    int nLen = 10, max = 10;
    int *array = randomList(nLen, max, DEFAULT_SEED);
    dumpArray("array", array, nLen);
    quickSort_Cocktail(array, 0, nLen-1);
    dumpArray("sorted array", array, nLen);
    free(array);
    printf("----------------------------------------\n");

    // 测试用例：最左侧、最右侧部分已经排好序。
    int A1[] = {2, 3, 5, 9, 4, 6, 8, 9, 10, 10};
    nLen = sizeof(A1)/sizeof(int);
    dumpArray("A1", A1, nLen);
    quickSort_Cocktail(A1, 0, nLen-1);
    dumpArray("sorted A1", A1, nLen);
    printf("----------------------------------------\n");

    // 测试用例：来源于 严蔚敏-《数据结构(C语言版）（第2版）》
    int A2[] = {49, 38, 65, 97, 76, 13, 27, 49};
    nLen = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, nLen);
    quickSort_Cocktail(A2, 0, nLen-1);
    dumpArray("sorted A2", A2, nLen);
}

void test_qsort(int scheme) {
    switch (scheme) {
        case PARTITION_SCHEME_LOMUTO:
            test_qsort_Lomuto();
            break;
        case PARTITION_SCHEME_HOARE:
            test_qsort_Hoare();
            break;
        case PARTITION_SCHEME_COCKTAIL:
            test_qsort_Cocktail();
            break;
    }
}

int main(int argc, char** argv) {
    int scheme = PARTITION_SCHEME_LOMUTO;
    test_qsort(scheme);

    return 0;
}