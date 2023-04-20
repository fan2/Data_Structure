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

// 输入两个有序数组，归并排序。
int *mergeSortedArrays(const int *a1, const int size1, const int *a2, const int size2) {
    // 至少各自有一个元素，才需要归并。
    // assert(size1>=1 && size2>=1);
    if (size1<1 || size2<1) {
        return NULL;
    }
    int *a = (int *)malloc((size1 + size2) * sizeof(int));
    if (!a) {
        printf("mergeSortedArrays malloc failed!\n");
        return NULL;
    }
    memset(a, 0, (size1 + size2) * sizeof(int));
    const int *p1 = a1;
    const int *p2 = a2;
    int i = 0;
    while (p1<=&a1[size1-1] && p2<=&a2[size2-1]) {
        if (*p1 < *p2)
            a[i++] = *p1++;
        else
            a[i++] = *p2++;
    }
    // 剩余A1
    while (p1<=&a1[size1-1]) {
        a[i++] = *p1++;
    }
    // 剩余A2
    while (p2<=&a2[size2-1]) {
        a[i++] = *p2++;
    }
    return a; // free by caller
}

// 对数组的两部分进行归并排序：a1[low:mid], a2[mid+1:high]
// 注意：array的索引范围[low,high]，temp的索引范围为[0, high-low-1]
// temp拷贝array作为数据源，array存放排序结果，实现In-place排序效果。
void merge(int *array, const int low, const int mid, const int high) {
    // 先将array拷贝出来，作为操作数据源
    int size = high-low+1;
    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        printf("merge malloc failed!\n");
        return;
    }
    // 注意索引必须从零开始，否则越界
    for (int i=low; i<=high; i++)
        temp[i-low] = array[i];
    // set two pointers
    int *p1 = &temp[low-low];   // end &temp[mid-low]
    int *p2 = &temp[mid+1-low]; // end &temp[high-low]
    int i = low; // array起始索引从low开始
    // 结果存放在array
    while (p1<=&temp[mid-low] && p2<=&temp[high-low]) {
        if (*p1 < *p2)
            array[i++] = *p1++;
        else
            array[i++] = *p2++;
    }
    // 剩余左侧
    while (p1<=&temp[mid-low]) {
        array[i++] = *p1++;
    }
    // 剩余右侧
    while (p2<=&temp[high-low]) {
        array[i++] = *p2++;
    }
    // dump two halves
    char szName[128];
    sprintf(szName, "a1=[%d:%d]", low, mid);
    dumpSubArray(szName, temp, low-low, mid-low);
    sprintf(szName, "a2=[%d:%d]", mid+1, high);
    dumpSubArray(szName, temp, mid+1-low, high-low);
    // dump result
    sprintf(szName, "    merged=[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    free(temp);
    temp = NULL;
}

// 就地对数组 A[l:h] 进行归并排序
void mergeSort(int *array, const int low, const int high) {
    // base case: 只有一个元素，直接返回。
    if (low >= high)
        return;
    int mid = (low+high)/2; // median
    mergeSort(array, low, mid); // left-half
    mergeSort(array, mid+1, high); // right-half
    merge(array, low, mid, high); // merge [low, mid] and [mid+1, high] in place
}

void testMergeSort() {
    // int nLen = 10, max = 10;
    // int *array = randomList(nLen, max, DEFAULT_SEED);
    // dumpArray("array", array, nLen);
    // mergeSort(array, 0, nLen-1);
    // dumpArray("sorted array", array, nLen);
    // free(array);
    // printf("----------------------------------------\n");

    // 测试用例：最左侧、最右侧部分已经排好序。
    int A1[] = {1,5,6,9,10};
    int l1 = sizeof(A1)/sizeof(int);
    dumpArray("A1", A1, l1);
    int A2[] = {2,3,4,7,8};
    int l2 = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, l2);
    int *A = mergeSortedArrays(A1, l1, A2, l2);
    dumpArray("A", A, l1+l2);
    free(A);
}

int main(int argc, char** argv) {
    // testMergeSort();

    // 测试用例：wiki Merge_sort_algorithm_diagram.svg
    int A1[] = {38, 27, 43, 3, 9, 82, 10};
    int l1 = sizeof(A1)/sizeof(int);
    dumpArray("A1", A1, l1);
    mergeSort(A1, 0, l1-1);
    dumpArray("sorted A1", A1, l1);
    printf("----------------------------------------\n");
    // 测试用例：来源于 严蔚敏-《数据结构(C语言版）（第2版）》
    int A2[] = {49, 38, 65, 97, 76, 13, 27};
    int l2 = sizeof(A2)/sizeof(int);
    dumpArray("A2", A2, l2);
    mergeSort(A2, 0, l2-1);
    dumpArray("sorted A2", A2, l2);
    printf("----------------------------------------\n");

    return EXIT_SUCCESS;
}