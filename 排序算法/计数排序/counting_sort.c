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

int minOfArray(int *const array, const int size)
{
    int i = 0;
    int min = array[0];
    for (i = 1; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
    return min;
}

int maxOfArray(int *const array, const int size)
{
    int i = 0;
    int max = array[0];
    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int *countingSortLoop(int *const array, const int size)
{
    int min = minOfArray(array, size); // 对应索引0, value offest=min
    int max = maxOfArray(array, size); // 对应索引 bucketLen-1
    // 根据数值范围计算桶的个数
    int bucketCount = max - min + 1;
    printf("min = %d, max = %d, bucketCount=%d\n", min, max, bucketCount);
    int *buckets = (int *)malloc(sizeof(array[0]) * bucketCount);
    if (!buckets) {
        printf("countingSortLoop malloc failed!\n");
        return NULL;
    }
    memset(buckets, 0, bucketCount * sizeof(int));
    int i = 0;
    // 统计每个值的个数
    for (i = 0; i < size; i++)
    {
        buckets[array[i] - min]++; // 注意偏移量为min
    }
    dumpArray("bucketes", buckets, bucketCount);
    // 分配与原始数组容量相同的结果数组
    int *sortedArray = (int *)malloc(size * sizeof(array[0]));
    if (!sortedArray) {
        printf("countingSortLoop malloc failed!\n");
        return NULL;
    }
    memset(sortedArray, 0, size * sizeof(int));
    int j = 0;
    // 依次遍历桶，索引为原始元素，值为次数
    for (i = 0; i < bucketCount; i++)
    {
        while (buckets[i]--)
        {
            sortedArray[j++] = i + min; // 注意偏移量为min
        }
    }
    free(buckets);
    return sortedArray;
}

int *countingSortIndex(int *const array, const int size)
{
    int min = minOfArray(array, size); // 对应索引0, value offest=min
    int max = maxOfArray(array, size); // 对应索引 bucketLen-1
    // 根据数值范围计算桶的个数
    int bucketCount = max - min + 1;
    printf("min = %d, max = %d, bucketCount=%d\n", min, max, bucketCount);
    int *buckets = (int *)malloc(sizeof(array[0]) * bucketCount);
    if (!buckets) {
        printf("countingSortIndex malloc failed!\n");
        return NULL;
    }
    memset(buckets, 0, bucketCount * sizeof(int));
    int i = 0, j = 0, k = 0;
    // 1. 统计每个元素的个数
    for (i = 0; i < size; i++)
    {
        buckets[array[i] - min]++; // 注意偏移量为min
    }
    dumpArray("count buckets", buckets, bucketCount);
    // 2. 累计计数（即排名）
    for (j = 1; j < bucketCount; j++)
    {
        buckets[j] += buckets[j - 1];
    }
    dumpArray("cumulative buckets", buckets, bucketCount);
    // 分配与原始数组容量相同的结果数组
    int *sortedArray = (int *)malloc(size * sizeof(array[0]));
    if (!sortedArray) {
        printf("countingSortIndex malloc failed!\n");
        return NULL;
    }
    memset(sortedArray, 0, size * sizeof(int));
    // 3. 根据排名定排序索引
    // 依次遍历原始元素，依据其累计计数（即排名）确定其索引
    for (j = size - 1; j >= 0; j--)
    {
        k = --buckets[array[j] - min]; // 注意偏移量为min
        printf("e = %d, k = %d\n", array[j], k);
        sortedArray[k] = array[j];
    }
    free(buckets);
    return sortedArray;
}

int main(int argc, char **argv)
{
    // int array[] = {8,2,1,5,9,7,5,2,8,7};
    int nLen = 10, max = 10;
    int *array = randomList(nLen, max, DEFAULT_SEED);

    dumpArray("array", array, nLen);
    int *sortedArray = countingSortLoop(array, nLen);
    dumpArray("sorted array", sortedArray, nLen);
    free(sortedArray);

    printf("----------------------------------------\n");

    dumpArray("array", array, nLen);
    sortedArray = countingSortIndex(array, nLen);
    dumpArray("sorted array", sortedArray, nLen);
    free(sortedArray);

    free(array);

    return EXIT_SUCCESS;
}
