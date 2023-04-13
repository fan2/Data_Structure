
[TOC]

在 Lomuto 分治策略中，通过遍历将相对枢轴的小值都移动聚拢到左侧，然后将枢轴移动到小值右侧（大值左侧），完成一趟分治。

在 Hoare 原始算法流程中，每次通过双边循环找到一对逆序对（右小值和左大值索引）进行交换，直到所有逆序对都交换完毕，最后将 pivot 与最右小值交换归位，完成一趟分治。

本文中摇摆策略中，通过单边双向交换构造围绕基准的有序三元组。重复局部三元交换，直到不再存在相对 pivot 的逆序三元组，完成一趟分治。

- 每次的“三元交换”涉及两次交换：swap(small, pivot), swap(big, pivot)。

## 严蔚敏-左右摇摆

严蔚敏-《数据结构(C语言版）（第2版）》

该分治策略采用的是单边双向摇摆，有点类似鸡尾酒冒泡排序。

通过单边双向摇摆，将小值交换到左边、大值交换到右边，从而生成以pivot为轴心的局部有序（升序）三元组：small<pivot<big。即三元组通过左右两次交换，完成一次局部排序。

三元局部排序后，pivot被移动到新的（索引）位置。以新的pivot索引作为支点，重复这种双向比较交换，直到将所有的小值都移动到pivot左边、所有的大值都移动到pivot右边，完成一趟分治：`[小值],pivot,[大值]`。

### 算法流程

**初始条件**：

待排数组 A[N]，索引下界 low=0, 上界 high=N-1；

#### 流程描述

1. 初始选定第一个元素作为枢轴（基准、支点）：pivot = A[p] = A[low]；

    - 枢轴索引位置p动态更新，但是 pivot 值始终不变（A[p]），按这个参考值进行切割分治。

2. 从右向左(索引范围：right=[high, low])，找到第一个关键字小于枢轴关键字 pivotkey 的记录，将其与当前枢轴记录交换，即 swap(A[r], A[p])。

    - 如果 right>p，即小值在枢轴右边，位置逆序才需交换，并更新pivot索引p=right

3. 再从左向右(索引范围：left=[low, high])，找到第一个关键字大于枢轴关键字 pivotkey 的记录，将其与当前枢轴记录交换，即 swap(A[l], A[p])。

    - 如果 left<p，即大值在枢轴左边，位置逆序才需交换，并更新pivot索引p=left

4. 重复步骤2和3，直至 left 与 right 相等或交叉为止（right<=left）。 此时 p 为枢轴在此趟排序中的最终位置，且左右两部分相对基准就序，完成一趟分治。

    - 本轮分治结果是 `[:p-1], pivot, [p+1:]`，左右相对基准有序，分区尚需继续分治排序。

index    | [:p-1] |   p   | [p+1:]
---------|--------|-------|--------
division | [小值] | pivot | [大值]

5. 以 pivot index 为支点，将源序列切割成左分区 [:p-1] 和右分区 [p+1:]，再分别对子分区递归执行分治流程（1~4）。

- 传入参数即是递归调用所需的初始化条件: (subarray, low, high)

---

对于pivot=A[p]，如果满足 A[b]>pivot 和  A[s]<pivot，那么b和s相对p逆序：

   p  |  b  |  s
------|-----|------
pivot | big | small

通过步骤2和3，将小值交换到左边、大值交换到右边，从而生成以pivot为轴心的局部有序（升序）三元组：s<p<b && small<pivot<big。

   s  |   p   |  b
------|-------|------
small | pivot | big

重复以上步骤将所有的小值都移动到pivot左边，将所有大值都移动到pivot右边，则完成一趟分治。

然后，再对左、右子分区递归分治，即可完成整体排序。

#### 一趟分治结束条件

初始选定第一个元素作为枢轴（基准、支点）：pivot = A[p] = A[low]；

如果两侧或某一侧相对pivot乱序：

1. 先从右向左找到小值，且满足逆序条件（p<right 但 A[p]>A[right]），执行交换 swap(A[p], A[right])，p=right。

2. 再从左向右搜索大值，可能有三种情况：

    - 2.1 在p(right)左侧找到大值（left<p(right)），执行交换 swap(A[p], A[left])，p=left。两步整体相当于将pivot交换到中间，小值交换到左、大值交换到右。
    - 2.2 越过p(right)找到大值（left>right），说明大值都已在右（左边都是小值），结束本轮分治；
    - 2.3 甚至抵达最右侧索引边界high（left=high>right）还是没找到大值，说明pivot本身最大，结束本轮分治。

如果两侧相对pivot已有序：

1. 初始选定第一个元素作为枢轴，若pivot本身最小，从右向左查找小值时，right抵达p(low)也未找到，此时right=p(low)。左侧小值分区为空，右侧已是大值，本轮分治提前结束。

2. 中途枢轴位置更新，若从右向左找到小值时，right穿越到pivot左边，即right<p；从左向右找到大值时，left穿越到pivot右边，即p<left。此时，right<p<left 且 A[right]<A[p]<A[left]，意味着右边不存在小值，左边不存在大值，即相对pivot已然有序。

3. 从左向右搜索大值，见2.2和2.3。

综上所述，可以将游标 cross over （!(left<right) 或 right<=left） 作为一趟分治的结束条件。

- 意味着单边双向摇摆后，围绕pivot不存在逆序对，一趟分治完成。

---

A={13, 38, 27, 49, 49, 76, 65, 97}

1. 选定 pivot=A[3]=49，那么从右往左第一个小值=A[2]=27，从左往右第一个大值是A[5]=76。左边最后一个小值已经在pivot左边，右边第一个大值已经在pivot右边，意味着整体相对基准已经有序，本轮分治完成。

![](https://note.youdao.com/yws/res/95711/WEBRESOURCE7ef7282d0250e3f2419a1a08d7f668d6)

2. 特殊地，选定 pivot=A[0]=13，那么从右往左未找到小值，right=low；从左往右第一个即是大值 A[1]=38。左边没有小值（pivot最小），右边第一个大值已经在pivot右边，意味着整体相对基准已经有序，本轮分治完成。

![](https://note.youdao.com/yws/res/95713/WEBRESOURCE57ecdf8efcb22d89f7458372c94d4f78)

3. 特殊地，选定 pivot=A[7]=97，那么从右往左第一个即是小值，A[6]=65；从左往右未找到大值，left=high。右边没有大值（pivot最大），左边第一个小值已经在pivot左边，意味着整体相对基准已经有序，本轮分治完成。

![](https://note.youdao.com/yws/res/95715/WEBRESOURCEd0c4ac46391f57eda07ab42c50539c53)

#### 递归调用结束条件

算法主体和 Lomuto 一致，仅仅是分区策略（partition）不同。
因此，递归调用结束条件，同 Lomuto 分治策略保持一致。

### 案例演绎

**初始条件**：

A[8] = {49,38,65,97,76,13,27,49}

0  | 1  | 2  | 3  | 4  | 5  | 6  | 7
---|----|----|----|----|----|----|----
49 | 38 | 65 | 97 | 76 | 13 | 27 | 49

1. 选定第一个元素作为基准：pivot = A[p] = A[0] = 49；
2. 初始化索引下界 low=0, 上界 high=N-1；

**一趟分割流程演绎**：

1. 从右high=7向左找到小值 A[right]=A[6]，执行交换 swap(A[r], A[p])->swap(A[6], A[0]) 消除逆序，更新 pivot_index=6。

0  | 1  | 2  | 3  | 4  | 5  | 6  | 7
---|----|----|----|----|----|----|----
**27** | 38 | 65 | 97 | 76 | 13 | **49** | 49

2. 从左low=0向右找到大值 A[left]=A[2]，执行交换 swap(A[l], A[p])->swap(A[2], A[6]) 消除逆序，更新 pivot_index=2。

0  | 1  | 2  | 3  | 4  | 5  | 6  | 7
---|----|----|----|----|----|----|----
27 | 38 | **49** | 97 | 76 | 13 | **65** | 49

通过以上两步交换，得到围绕pivot的有序三元组：A[0]<A[p=2]<A[6]（27<49<65）

![三元交换](https://note.youdao.com/yws/res/95727/WEBRESOURCE4daceed8760ff6a3d59abddfd2669aec)

重复1、2，得到围绕pivot的新有序三元组：A[2]<A[p=3]<A[5]（13<49<97）

0  | 1  | 2  | 3  | 4  | 5  | 6  | 7
---|----|----|----|----|----|----|----
27 | 38 | 13 | **49** | 76 | 97 | 65 | 49

![三元交换](https://note.youdao.com/yws/res/95730/WEBRESOURCEfe9f827f01ed513aa2a0d1dfc8907d9a)

重复1、2，得到 right=2，left=4，右指针cross左指针（right<left），本趟分割结束：`[27,38,13], 49, [76,97,65,49]`

![cross](https://note.youdao.com/yws/res/95732/WEBRESOURCE30457f9d2cd0590414fdc4f1fe6721e8)

**二趟分割 1.left 流程演绎**：A[0:2]=[27,38,13]，pivot=A[0]=27

1. 从右high=2向左找到小值 A[right]=A[2]，执行交换 swap(A[r], A[p])->swap(A[2], A[0]) 消除逆序，更新 pivot_index=2。
2. 从左low=0向右找到大值 A[left]=A[1]，执行交换 swap(A[l], A[p])->swap(A[1], A[2]) 消除逆序，更新 pivot_index=1。

0  | 1  | 2  
---|----|----
13 | **27** | 38 

重复1、2，右指针right抵达最小索引未找到小值，左指针left抵达最大索引未找到大值。右指针cross左指针（right<left），本趟分割结束：`[13], 27, [38]`。

- 由于左分区和右分区都只有一个元素（size=1），故无法再切割分治。

**二趟分割 1.right 流程演绎**：A[4:7]=[76,97,65,49]，pivot=A[4]=76

1. 从右high=7向左找到小值 A[right]=A[7]，执行交换 swap(A[r], A[p])->swap(A[7], A[0]) 消除逆序，更新 pivot_index=7。
2. 从左low=4向右找到大值 A[left]=A[5]，执行交换 swap(A[l], A[p])->swap(A[5], A[7]) 消除逆序，更新 pivot_index=5。

4  | 5  | 6  | 7 
---|----|----|----
49 | 76 | 65 | 97 

3. 从右high=7向左找到小值 A[right]=A[6]，执行交换 swap(A[r], A[p])->swap(A[6], A[5]) 消除逆序，更新 pivot_index=6。

4  | 5  | 6  | 7 
---|----|----|----
49 | 65 | 76 | 97 

4. 从左low=4向右找到大值 A[left]=A[7]。右指针cross左指针（right<left），本趟分割结束：`[49,65], 76, [97]`。

- 右分区只有一个元素，无法再切割分治；左分区需要继续分治。

**三趟分割 2.left 流程演绎**：A[4:5]=[49,65]，pivot=A[4]=49

1. 从右high=5向左，right抵达最小索引low=4未找到小值。
2. 从左low=4向右找到大值 A[left]=A[5]。右指针cross左指针（right<left），本趟分割结束：`[], 49, [65]`。

- 左分区为空，右分区只有一个元素，无法再切割分治。

---

由于该分治策略也是 In-place Swap 的，故所有分区最终分割到 base case（分区为空或只有一个元素）无法再分割时，即整体结束合体时，原始数组即已交换排好序。

将二趟分割 1.left 和 二趟分割 1.right 还原到一趟分割由分到合的最终排序结果序列如下：

0  | 1  | 2  | 3  | 4  | 5  | 6  | 7
---|----|----|----|----|----|----|----
13 | 27 | 38 | **49** | 49 | 65 | 76 | 97

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

quickSort_Cocktail 和 quickSort_Lomuto 的主体结构完全一样，区别在于 partition 分治实现。

```C
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
```

### C

```C
int *randomList(int n, int max);
void swap(int *a, int *b);
void dumpArray(const char* name, const int *array, const int size);
void dumpSubArray(const char* name, const int *array, const int low, const int high);

// 对子数组 A[l:h] 进行切割，返回pivot分治索引
// 该分治策略采用的是单边双向摇摆，有点类似鸡尾酒冒泡排序。
// 三元组通过左右两次交换，将小值交换到左边、大值交换到右边，
// 从而生成以pivot为轴心的局部有序（升序）三元组：small<pivot<big。
int partition_Cocktail(int *array, const int low, const int high) {
    // 打印调试信息
    char szName[128];
    sprintf(szName, "array[%d:%d]", low, high);
    dumpSubArray(szName, array, low, high);
    // 选择第一个元素作为基准元素，本轮切割中pivot基准值保持不变，但其索引会动态更新。
    int p = low, pivot = array[p];
    // 初始化索引下界 left=low, 上界 right=high
    int left = low, right = high;
    while (left < right) {
        // 每轮循环，for初始化复位左右游标
        // 1.1 从右向左查找小值
        for (right=high; right>=low; right--)
            if (array[right] < pivot)
                break;
        // 1.2 找到右边小值，与基准交换
        if (right > p) {
            swap(&array[right], &array[p]);
            p = right; // 更新基准索引
        }
        // else {
        //     // pivot 最小，无需再从左向右查找大值，可提前结束
        //     // 但 right 已到最左，会满足 while 退出条件
        //     break;
        // }
        // 2.1 从左向右查找大值
        for (left=low; left<=high; left++)
            if (array[left] > pivot)
                break;
        // 2.2 找到左边大值，与基准交换（右边大值，符合顺序，无需交换）。
        if (left < p) {
            swap(&array[left], &array[p]);
            p = left; // 更新基准索引
        }
        // else {
        //     // 左边没有大值（都是小值），大值都在右边，可提前结束
        //     // 但 left 已穿越到p右侧，会满足 while 退出条件
        //     break;
        // }

        // left>=right: 重叠（overlap）或交叉（cross），while循环退出
    }
    //////////////////////////////////////////
    // for 循环改为 while 循环
    //////////////////////////////////////////
    // while (left < right) {
    //     // 每轮循环，复位索引下界 left=low, 上界 right=high
    //     left = low, right = high;
    //     // 1.1 从右向左查找小值
    //     while (right>low && array[right]>=pivot)
    //         right--;
    //     // 1.2 找到右边小值，与基准交换
    //     if (right > p) {
    //         swap(&array[right], &array[p]);
    //         p = right; // 更新基准索引
    //     }
    //     // 2.1 从左向右查找大值
    //     while (left<=high && array[left]<=pivot)
    //         left++;
    //     // 2.2 找到左边大值，与基准交换（右边大值，符合顺序，无需交换）。
    //     if (left < p) {
    //         swap(&array[left], &array[p]);
    //         p = left; // 更新基准索引
    //     }
    //     // left>=right: 重叠（overlap）或交叉（cross），while循环退出
    // }
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
    int *array = randomList(nLen, max);
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
```

### Python

注意：Python 中 list 切片返回的是原数据的副本，如果 qsort_Lomuto 中传切片副本 A[:p]、A[p+1:]，需要返回拼接！

```Python
# 6.4-快速排序(Quick Sort)-cocktail

import random

# 对子数组 A[l:h] 进行切割，返回pivot分治索引
# 该分治策略采用的是单边双向摇摆，有点类似鸡尾酒冒泡排序。
# 三元组通过左右两次交换，将小值交换到左边、大值交换到右边，
# 从而生成以pivot为轴心的局部有序（升序）三元组：small<pivot<big。
def partition_Cocktail(A: list, low: int, high: int) -> int:
    # 选择第一个元素作为基准元素
    p = low; pivot = A[p]
    # 打印调试信息
    print('A[{}:{}]={}, pivot={}'.format(low, high, A[low:high+1], p))
    # 初始化索引下界 left=low, 上界 right=high
    left = low; right = high
    while left < right:
        # 每轮循环，复位索引下界 left=low, 上界 right=high
        left = low; right = high
        # 1.1 从右向左查找小值
        while right>=low and A[right]>=pivot:
            right -= 1
        # 1.2 找到右边小值，与基准交换
        if right > p:
            A[right],A[p] = A[p], A[right]
            p = right; # 更新基准索引
        # 2.1 从左向右查找大值
        while left<=high and A[left]<=pivot:
            left += 1
        # 2.2 找到左边大值，与基准交换（右边大值，符合顺序，无需交换）。
        if left < p:
            A[left],A[p] = A[p], A[left]
            p = left; # 更新基准索引
        # left>=right: 重叠（overlap）或交叉（cross），while循环退出

    # 本轮分治完成：[小值],pivot,[大值]
    # 打印调试信息
    print('A[{}:{}]={}, homing pivot={}'.format(low, high, A[low:high+1], p))
    # 返回 pivot 索引
    return p

# 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
def qsort_Cocktail(A: list, low: int, high: int):
    # base case 1: overlap: low=high，只有一个元素
    # base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if low >= high:
        return
    # in-place compare and swap
    p = partition_Cocktail(A, low, high)
    # recursion for left small part
    qsort_Cocktail(A, low, p-1)
    # recursion for right big part
    qsort_Cocktail(A, p+1, high)

if __name__ == "__main__":
    # 在 [1,10] 之间随机挑选6个数
    n = 6; left = 1; right = 10
    iList = random.sample(range(left,right+1), n)
    print('iList =', iList)
    qsort_Cocktail(iList, 0, len(iList)-1)
    print('sorted iList =', iList)
    print('-'*40)
    # 重复部分元素
    cList = random.sample(iList, k=10, counts=[1,2,3,1,2,1])
    print('cList =', cList)
    qsort_Cocktail(cList, 0, len(cList)-1)
    print('sorted cList =', cList)
    print('-'*40)
    # 测试用例：最左侧、最右侧部分已经排好序。
    A = [2, 3, 5, 9, 4, 6, 8, 9, 10, 10]
    print('A =', A)
    qsort_Cocktail(A, 0, len(A)-1)
    print('sorted A =', A)
    print('-'*40)
    # 测试用例：来源于 严蔚敏-《数据结构(C语言版）（第2版）》
    A2 = [49, 38, 65, 97, 76, 13, 27, 49]
    print('A2 =', A2)
    qsort_Cocktail(A2, 0, len(A2)-1)
    print('sorted A2 =', A2)
    print('-'*40)
    # 测试用例：完全逆序。
    A3 = list(range(20,30))
    A3.reverse()
    print('A3 =', A3)
    qsort_Cocktail(A3, 0, len(A3)-1)
    print('sorted A3 =', A3)
    print('-'*40)
    # 测试用例：初始有序。
    print('A3 =', A3)
    qsort_Cocktail(A3, 0, len(A3)-1)
    print('sorted2 A3 =', A3)
```
