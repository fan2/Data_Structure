
[TOC]

在 Lomuto 分治策略中，通过遍历将相对枢轴的小值都移动聚拢到左侧，然后将枢轴移动归位到小值右侧（大值左侧），完成一趟分治。

在 Hoare 原始算法流程中，每次通过双边循环找到一对逆序对（右小值和左大值索引）进行交换，直到所有逆序对都交换完毕，最后将 pivot 与最右小值交换归位，完成一趟分治。

## Hoare partition scheme

wiki - [QuickSort](https://en.wikipedia.org/wiki/Quicksort)

The original partition scheme described by Tony Hoare uses two pointers (indices into the range) that **start at both ends** of the array being partitioned, then move toward each other, until they detect an inversion: a pair of elements, one greater than the bound (Hoare's terms for the pivot value) at the first pointer, and one less than the bound at the second pointer; if at this point the first pointer is still before the second, these elements are in the *wrong* order relative to each other, and they are then **exchanged**. 

After this the pointers are moved inwards, and the search for an inversion is repeated; when eventually the pointers **cross** (the first points after the second), no exchange is performed; a valid partition is found, with the point of division between the crossed pointers (any entries that might be strictly between the crossed pointers are equal to the pivot and can be excluded from both sub-ranges formed). With this formulation it is possible that one sub-range turns out to be the whole original range, which would prevent the algorithm from advancing. Hoare therefore stipulates that at the end, the sub-range containing the pivot element (which still is at its original position) can be decreased in size by excluding that pivot, after (if necessary) exchanging it with the sub-range element ***closest*** to the separation; thus, termination of quicksort is ensured.

Tony Hoare 分治策略的核心思想：通过双边循环，先从右向左找到一个小值，再从左向右找到一个大值，将小值和大值交换，实现相对基准值有序。当所有小值都移到左边、所有大值都移到右边时，将基准值 pivot 插入最右小值右边，即完成一趟分治：`[小值],pivot,[大值]`。

### 算法流程

**初始条件**：

待排数组 A[N]，索引范围 low=0, high=N-1；

#### 流程描述

1. 固定第一个元素作为基准：pivot = A[p] = A[low]

2. 双边遍历：

    - 从左至右（索引范围：left=[low+1, high]）查找大值 A[left]
    - 从右至左（索引范围：right=[high, low+1]）查找小值 A[right]
    - 若 left<right，则意味着相对基准逆序，执行 swap(A[left], A[right])，消除局部相对逆序。

3. 重复2：继续从 left++ 至右、从 right-- 至左，查找第二个逆序对并交换。

4. 若 left 与 right 重叠（overlap）或交叉（cross），即 right<=left，意味着相对pivot已经不存在逆序对，此时right为最右小值（left为最左大值）。

    - 执行 swap(A[right], A[p]) 使 pivot 归位（顶替最右小值），这样 pivot 左边都是小值，pivot 右边都是大值，完成一趟分治。
    - 本轮分治结果是 `[:p-1], pivot, [p+1:]`，左右相对基准有序，分区尚需继续分治排序。

index    | [:p-1] |   p   | [p+1:]
---------|--------|-------|--------
division | [小值] | pivot | [大值]

5. 以 pivot index 为支点，将源序列切割成左分区 [:p-1] 和右分区 [p+1:]，再分别对子分区递归执行分治流程（1~4）。

- 传入参数即是递归调用所需的初始化条件: (subarray, low, high)

#### 一趟分治结束条件

固定第一个元素作为枢轴：pivot = A[p] = A[low]

如果两侧或某一侧相对pivot乱序，执行双边遍历时，可能有三种情况：

1. 从左至右查找到大值 A[left] 且满足 p<left，从右至左查找到小值 A[right] 且满足 left<right，大值、小值逆序分布两侧。

    - 执行交换 swap(A[left], A[right]) 消除局部相对逆序。

2. 从左至右未查找到大值，left（穿越p）抵达high，意味着pivot本身最大。此时，从右至左查找到小值 A[right]=A[high]，left=right。

    - 执行交换 swap(A[p], A[right]) 以使 pivot 归位（最大值挪到最右），本轮分治结束。

如果两侧相对pivot已有序：

- 从左至右查找到大值 A[left] 且满足 p<left，从右至左未查找到小值，right（穿越p）抵达low，意味着pivot本身最小，已满足参考分治要求（right<left），结束本轮分治。

    - 尽管pivot已归位（最小且已在最左边），但为了代码的统一性，可对齐上面的2执行交换操作（内部优化无实质交换）。

综上所述，可以将游标 overlap（right==left） 或 cross over（right<left） 作为一趟分治的结束条件。

- 意味着经历双边查找后，围绕pivot不存在逆序对，一趟分治完成。

#### 递归调用结束条件

算法主体和 Lomuto 一致，仅仅是分区策略（partition）不同。
因此，递归调用结束条件，同 Lomuto 分治策略保持一致。

### 案例演绎

**初始条件**：

A[7] = {10, 80, 30, 90, 40, 50, 70}

0  | 1  | 2  | 3  | 4  | 5  | 6
---|----|----|----|----|----|----
10 | 80 | 30 | 90 | 40 | 50 | 70

1. 固定第一个元素作为基准：pivot = A[p] = A[0]；
2. left 为左指针，游标范围 [low+1, high]，记录从左向右找到的大值索引；
3. right 为右指针，游标范围 [high, low+1]，记录从右向左找到的小值索引；

---

**一趟分割流程演绎**：

1. 从左low=0向右找到大值  A[left]=A[1]，从右high=6向左抵达到最小索引（right=low）未找到小值。

    - 由于右指针cross左指针（right<left），不再存在相对逆序对，执行 swap(A[p], A[right])->swap(A[0], A[0]) 将 pivot 归位，结束本轮分治。
    - 同一索引免交换，初步分割结束: `[], 10, [1:6]`。

2. 左分区为空（size=0）不可再分割，右分区需继续分割。

**二趟分割 1.right 流程演绎**：右分区 A[1:6]=[80,30,90,40,50,70], pivot=A[1]=80

1. 从左low=1向右找到大值 A[left]=A[3]，从右high=6向左找到小值 A[right]=A[6]。

    - 满足left<right，执行交换 swap(A[3], A[6]) 消除逆序。

 1  | 2  | 3  | 4  | 5  | 6
----|----|----|----|----|----
 80 | 30 | *70* | 40 | 50 | *90*

2. 继续从left=3向右找到大值 A[left]=A[6]，从high=6向左找到小值 A[right]=A[5]。

    - 由于右指针cross左指针（right<left），不再存在相对逆序对，执行swap(A[p], A[right])->swap(A[1], A[5]) 将 pivot 归位，本轮分割结束：`[50,30,70,40], 80, [90]`。

 1  | 2  | 3  | 4  | 5  | 6
----|----|----|----|----|----
 50 | 30 | 70 | 40 | **80** | 90

3. 右分区只有一个元素（size=1）不可再分割，左分区需继续分割。

**三趟分割 2.left 流程演绎**：左分区 A[1:4]=[50,30,70,40], pivot=A[1]=50

1. 从左low=1向右找到大值 A[left]=A[3]，从右high=4向左找到小值 A[right]=A[4]。

    - 满足left<right，执行交换 swap(A[3], A[4]) 消除逆序。

 1  | 2  | 3  | 4  
----|----|----|----
 50 | 30 | 40 | 70

2. 继续从left=3向右找到大值 A[4]，从right=4向左找到小值 A[3]。

    - 由于右指针cross左指针（right<left），不再存在相对逆序对，执行swap(A[p], A[right])->swap(A[1], A[3]) 将 pivot 归位，本轮分割结束：`[40,30], 50, [70]`。

1  | 2  | 3  | 4  
----|----|----|----
40 | 30 | **50** | 70

3. 右分区只有一个元素（size=1）不可再分割，左分区需继续分割。

**四趟分割 3.left 流程演绎**：左分区 A[1:2]=[40,30], pivot=A[1]=40

1. 从左low=1向右抵达最大索引（left=high）未找到大值，从右high=2向左找到小值 A[right]=A[2]。

    - 由于右指针overlap左指针（right=left），不再存在相对逆序对，执行swap(A[p], A[right])->swap(A[1], A[2]) 将 pivot 归位，本轮分割结束：`[30], 40, []`。

 1  | 2  
----|----
 30 | **40**

2. 左分区只有一个元素（size=1）不可再分割，右分区为空（size=0）不可再分割。

---

由于 Hoare 原始分治策略是 In-place Swap 的，故所有分区最终分割到 base case（分区为空或只有一个元素）无法再分割时，即整体结束合体时，原始数组即已交换排好序。

这里，再人工直观演绎一下由分到合的流程：

将四趟分割还原到三趟分割左：

 1  | 2  | 3  | 4  
----|----|----|----
 30 | 40 | **50** | 70

将三趟分割还原到二趟分割左：

 1  | 2  | 3  | 4  | 5  | 6
----|----|----|----|----|----
 30 | 40 | 50 | 70 | **80** | 90

将二趟分割还原到一趟分割右，得到最终排序结果：

0  | 1  | 2  | 3  | 4  | 5  | 6
---|----|----|----|----|----|----
**10** | 30 | 40 | 50 | 70 | 80 | 90

## 代码实现

基于递归的分治算法，主体由三部分构成：

1. base case: recursion terminator

    - base case 1: overlap: low=high，只有一个元素
    - base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)

2. partition: in-place compare and swap

    - return pivot position

3. recursion for sub-arrays splitted by pivot

    - left small part: [low, p-1]
    - right big part: [p+1, high]

quickSort_Hoare 和 quickSort_Cocktail、quickSort_Lomuto 的主体结构完全一样，区别在于 partition 分治实现。

```C
// 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
void quickSort_Lomuto(int *array, const int low, const int high) {
    // base case 1: overlap: low=high，只有一个元素
    // base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if (low >= high)
        return;
    // in-place compare and swap
    int pivot_index = partition_Lomuto(array, low, high);
    // recursion for left small part
    quickSort_Lomuto(array, low, pivot_index-1);
    // recursion for right big part
    quickSort_Lomuto(array, pivot_index+1, high);
}
```

### C

```C
int *randomList(int n, int max);
void swap(int *a, int *b);
void dumpArray(const char* name, const int *array, const int size);
void dumpSubArray(const char* name, const int *array, const int low, const int high);

// 对子数组 A[l:h] 进行切割，返回pivot分治索引
// 通过双边循环每次找到右小值和左大值进行交换，
// 最后将基准值 pivot 插入最右小值右边，完成一趟分治。
int partition_Hoare(int *array, const int low, const int high) {
    // 打印调试信息
    char szName[128];
    sprintf(szName, "array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    // 选择第一个元素作为基准元素
    int p = low, pivot = array[p];
    // 初始化左右索引游标（left也可赋值low+1？）
    int left = low, right = high;
    while (left < right) { // 至少两个元素
        // 从左向右查找大值索引
        while (left<=high && array[left]<=pivot)
            left++;
        // 从右向左查找小值索引
        while (right>low && array[right]>=pivot)
            right--;
        // 逆序分布两边，交换调整顺序
        if (left < right)
            swap(&array[left], &array[right]);
        else { // 基准归位
            // left>=right: 重叠（overlap）或交叉（cross），此时right为最右小值。
            // 将最右小值A[r]与pivot交换，从而实现pivot中间基准值归位。
            swap(&array[right], &array[p]);
            p = right; // 更新基准索引
            // 本轮分治完成，while循环退出
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
    int pivot_index = partition_Hoare(array, low, high);
    // recursion for left small part
    quickSort_Hoare(array, low, pivot_index-1);
    // recursion for right big part
    quickSort_Hoare(array, pivot_index+1, high);
}

void test_qsort_Hoare() {
    int nLen = 10, max = 10;
    int *array = randomList(nLen, max);
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

    // 测试用例：来自陈峰棋《数据结构C语言版》
    // int A3[] = {'d', 'e', 'a', 'c', 'f', 'b', 'h', 'g'};
    int A3[] = {100, 101, 97, 99, 102, 98, 104, 103};
    nLen = sizeof(A3)/sizeof(int);
    dumpArray("A3", A3, nLen);
    quickSort_Hoare(A3, 0, nLen-1);
    dumpArray("sorted A3", A3, nLen);
}
```

### Python

注意：Python 中 list 切片返回的是原数据的副本，如果 qsort_Lomuto 中传切片副本 A[:p]、A[p+1:]，需要返回拼接！

```Python
import random

# 对子数组 A[l:h] 进行切割，返回pivot分治索引
# 通过双边循环每次找到右小值和左大值进行交换，
# 最后将基准值 pivot 插入最右小值右边，完成一趟分治。
def partition_Hoare(A: list, low: int, high: int) -> int:
    # 选择第一个元素作为基准元素
    p = low; pivot = A[p]
    # 打印调试信息
    print('A[{}:{}]={}, pivot={}'.format(low, high, A[low:high+1], p))
    # 初始化索引左游标 left=low, 右游标 right=high
    left = low; right = high
    while left < right:
        # 从左向右查找大值索引
        while left<=high and A[left]<=pivot:
            left += 1
        # 从右向左查找小值索引
        while right>low and A[right]>=pivot:
            right -= 1
        # 逆序分布两边，交换调整顺序
        if left < right:
            A[left],A[right] = A[right],A[left]
        else: # 基准归位
            # left>=right: 重叠（overlap）或交叉（cross），此时right为最右小值。
            # 将最右小值A[r]与pivot交换，从而实现pivot中间基准值归位。
            A[right],A[p] = A[p],A[right]
            p = right # 更新基准索引
            # 本轮分治完成，while循环退出

    # 本轮分治完成：[小值],pivot,[大值]
    # 打印调试信息
    print('A[{}:{}]={}, homing pivot={}'.format(low, high, A[low:high+1], p))
    # 返回 pivot 索引
    return p

# 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
def qsort_Hoare(A: list, low: int, high: int):
    # base case 1: overlap: low=high，只有一个元素
    # base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if low >= high:
        return
    # in-place compare and swap
    p = partition_Hoare(A, low, high)
    # recursion for left small part
    qsort_Hoare(A, low, p-1)
    # recursion for right big part
    qsort_Hoare(A, p+1, high)

if __name__ == "__main__":
    # 在 [1,10] 之间随机挑选6个数
    n = 6; left = 1; right = 10
    iList = random.sample(range(left,right+1), n)
    print('iList =', iList)
    qsort_Hoare(iList, 0, len(iList)-1)
    print('sorted iList =', iList)
    print('-'*40)
    # 重复部分元素
    cList = random.sample(iList, k=10, counts=[1,2,3,1,2,1])
    print('cList =', cList)
    qsort_Hoare(cList, 0, len(cList)-1)
    print('sorted cList =', cList)
    print('-'*40)
    # 测试用例：最左侧、最右侧部分已经排好序。
    A = [2, 3, 5, 9, 4, 6, 8, 9, 10, 10]
    print('A =', A)
    qsort_Hoare(A, 0, len(A)-1)
    print('sorted A =', A)
    print('-'*40)
    # 测试用例：https://en.wikipedia.org/wiki/File:Quicksort-example.gif
    A2 = [6, 5, 3, 1, 8, 7, 2, 4]
    print('A2 =', A2)
    qsort_Hoare(A2, 0, len(A2)-1)
    print('sorted A2 =', A2)
    print('-'*40)
    # 测试用例：来自陈峰棋《数据结构C语言版》
    # A3 = ['d', 'e', 'a', 'c', 'f', 'b', 'h', 'g']
    A3 = [100, 101, 97, 99, 102, 98, 104, 103]
    print('A3 =', A3)
    qsort_Hoare(A3, 0, len(A3)-1)
    print('sorted A3 =', A3)
    print('-'*40)
    # 测试用例：完全逆序。
    A3 = list(range(20,30))
    A3.reverse()
    print('A3 =', A3)
    qsort_Hoare(A3, 0, len(A3)-1)
    print('sorted A3 =', A3)
    print('-'*40)
    # 测试用例：初始有序。
    print('A3 =', A3)
    qsort_Hoare(A3, 0, len(A3)-1)
    print('sorted2 A3 =', A3)
```