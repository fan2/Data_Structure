
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

2. 双边遍历查找逆序对：

    - 2.1 从左至右（索引范围：left=[low+1, high+1]）查找大值 A[left]，若 left=high+1 溢出表示没找到大值。
    - 2.2 从右至左（索引范围：right=[high, low]）查找小值 A[right]，right=low 抵达左边界表示没找到小值。

3. 交换消除逆序对：若满足 left<right，则意味着相对基准逆序，执行交换 swap(A[left], A[right]) 消除局部相对逆序。

4. 重复2-3：继续从 left++ 向右、从 right-- 向左，向中间压缩推进，查找第二、三、...、M个逆序对并交换。

5. 若 3 中不满足常规逆序条件，即left与right交叉(cross)（left>right），则意味着不再存在相对基准的逆序对，将piovt归位。

    - 执行 swap(A[right], A[p]) 使 pivot 归位（顶替最右小值），完成一趟分治。
    - 本轮分治结果是 `[:p-1], pivot, [p+1:]`，左右相对基准有序，分区尚需继续分治排序。

index    | [:p-1] |   p   | [p+1:]
---------|--------|-------|--------
division | [小值]  | pivot | [大值]

6. 以 pivot index 为支点，将源序列切割成左分区 [:p-1] 和右分区 [p+1:]，再分别对子分区递归执行分治流程（1~5）。

- 传入参数即是递归调用所需的初始化条件: (subarray, low, high)

#### 一趟分治结束条件

初始条件满足 low<high，即至少有两个元素，才需要排序。
固定第一个元素作为枢轴：pivot = A[p] = A[low]。
没有经过试探，一开始无从得知整体是否有序。

1. 如果原本整体有序（[1,2,3,4,5]），则首元素pivot必然最小，双边遍历下来，left=1、right=low（=p=0，抵达左边界）。
2. 如果原本不存在逆序对（[3,1,2,4,5]），则双边遍历下来，left=3、right=2，right即是左侧小值边界（最右小值）。
3. 如果原本存在逆序对，则双边遍历下来 left<right，经过交换消除完逆序对后，下一轮循环回归到情形2。

3->2的过程，是将 left\<right 扭转到 left\>right。left=right 不成立，因为不可能存在同时大于和小于pivot的值。

综上所述，可以将左右游标cross（right<left）作为一趟分治的结束条件。

对于原本整体有序，right=low=p，无需实质交换。对于原本或经过交换后不存在逆序对，right为小值边界。
双边遍历循环结束后，所有的逆序对都已消除，此时需要将pivot归位到应有的位置。
执行 swap(A[p], A[right])，将pivot与最右小值交换即可使其归位。

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
2. left 为左指针，游标范围 [low+1, high+1]，记录从左向右找到的大值索引；
3. right 为右指针，游标范围 [high, low]，记录从右向左找到的小值索引；

---

**一趟分割流程演绎**：

1. 从左low=1向右找到大值 A[left]=A[1]，从右high=6向左抵达到最小索引（right=low）未找到小值。

    - 由于右指针cross左指针（right<left），不存在相对逆序对，执行 swap(A[p], A[right])->swap(A[0], A[0]) 将 pivot 归位，结束本轮分治。
    - 同一索引免交换，初步分割结束: `[], 10, [1:6]`。

2. 左分区为空（size=0）不可再分割，右分区需继续分割。

**二趟分割 1.right 流程演绎**：右分区 A[1:6]=[80,30,90,40,50,70], pivot=A[1]=80

1. 从左low=2向右找到大值 A[left]=A[3]，从右high=6向左找到小值 A[right]=A[6]。

    - 满足left<right，执行交换 swap(A[3], A[6]) 消除逆序。

1  | 2  | 3    | 4  | 5  | 6
---|----|------|----|----|-----
80 | 30 | *70* | 40 | 50 | *90*

2. 继续从left=3向右找到大值 A[left]=A[6]，从right=6向左找到小值 A[right]=A[5]。

    - 由于右指针cross左指针（right<left），不再存在相对逆序对，执行swap(A[p], A[right])->swap(A[1], A[5]) 将 pivot 归位，本轮分割结束：`[50,30,70,40], 80, [90]`。

1  | 2  | 3  | 4  | 5      | 6
---|----|----|----|--------|---
50 | 30 | 70 | 40 | **80** | 90

3. 右分区只有一个元素（size=1）不可再分割，左分区需继续分割。

**三趟分割 2.left 流程演绎**：左分区 A[1:4]=[50,30,70,40], pivot=A[1]=50

1. 从左low=2向右找到大值 A[left]=A[3]，从右right=4向左找到小值 A[right]=A[4]。

    - 满足left<right，执行交换 swap(A[3], A[4]) 消除逆序。

 1  | 2  | 3  | 4  
----|----|----|----
 50 | 30 | 40 | 70

2. 继续从left=3向右找到大值 A[4]，从right=4向左找到小值 A[3]。

    - 由于右指针cross左指针（right<left），不再存在相对逆序对，执行swap(A[p], A[right])->swap(A[1], A[3]) 将 pivot 归位，本轮分割结束：`[40,30], 50, [70]`。

1  | 2  | 3      | 4
---|----|--------|---
40 | 30 | **50** | 70

3. 右分区只有一个元素（size=1）不可再分割，左分区需继续分割。

**四趟分割 3.left 流程演绎**：左分区 A[1:2]=[40,30], pivot=A[1]=40

1. 从左low=2向右未找到大值，溢出最大索引left=high+1；从右high=2向左找到小值 A[right]=A[2]。

    - 由于右指针cross左指针（right<left），不再存在相对逆序对，执行swap(A[p], A[right])->swap(A[1], A[2]) 将 pivot 归位，本轮分割结束：`[30], 40, []`。

 1  | 2  
----|----
 30 | **40**

2. 左分区只有一个元素（size=1）不可再分割，右分区为空（size=0）不可再分割。

---

由于 Hoare 原始分治策略是 In-place Swap 的，故所有分区最终分割到 base case（分区为空或只有一个元素）无法再分割时，即整体结束合体时，原始数组即已交换排好序。

这里，再人工直观演绎一下由分到合的流程：

将四趟分割还原到三趟分割左：

1  | 2  | 3      | 4
---|----|--------|---
30 | 40 | **50** | 70

将三趟分割还原到二趟分割左：

1  | 2  | 3  | 4  | 5      | 6
---|----|----|----|--------|---
30 | 40 | 50 | 70 | **80** | 90

将二趟分割还原到一趟分割右，得到最终排序结果：

0      | 1  | 2  | 3  | 4  | 5  | 6
-------|----|----|----|----|----|---
**10** | 30 | 40 | 50 | 70 | 80 | 90

## 代码实现

基于递归的分治算法，主体由三部分构成：

1. base case: recursion terminator

    - base case 1: 只有一个元素: low=high
    - base case 2: pivot居两端: high<low，居左左空(low,low-1)，居右右空(high+1,high)

2. partition: in-place compare and swap

    - return pivot position

3. recursion for sub-arrays splitted by pivot

    - left small part: [low, p-1]
    - right big part: [p+1, high]

quickSort_Hoare 和 quickSort_Cocktail、quickSort_Lomuto 的主体结构完全一样，区别在于 partition 分治实现。

```C
// 对子数组 A[l:h] 进行快速排序，返回pivot分治索引
void quickSort_Hoare(int *array, const int low, const int high) {
    // base case 1: 只有一个元素: low=high
    // base case 2: pivot居两端: high<low，居左左空(low,low-1)，居右右空(high+1,high)
    if (low >= high)
        return;
    // in-place compare and swap
    int pivot_index = partition_Hoare(array, low, high);
    // recursion for left small part
    quickSort_Hoare(array, low, pivot_index-1);
    // recursion for right big part
    quickSort_Hoare(array, pivot_index+1, high);
}
```

**注意**：Python 中 list 切片返回的是原数据的副本，如果 qsort_Hoare 中传切片副本 A[:p]、A[p+1:]，需要返回拼接！
