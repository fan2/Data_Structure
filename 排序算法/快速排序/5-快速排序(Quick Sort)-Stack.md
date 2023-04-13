
[TOC]

## 栈机制

用栈代替递归，用栈记录待治理的分区索引，初始压栈 tuple(0, len(A)-1)，代表整个序列。

读取栈顶分区，执行 Lomuto partition scheme 分治策略，根据返回的支点位置，调整分治分区：

1. 新支点左右分区大小均超过1，当前区间一分为二，删除当前分区，新增两个左右分区
2. 抵达base case：两元素（pivot左或右）或三元素（pivot居中），分区分治完成，移除当前分区
3. 新支点左/右侧为空或单元素，裁剪左/右侧base case，缩小更新当前分区

当待治理的分区栈被清空，意味着整个分治流程完成。

---

本质上，就是使用栈结合当前分治结果，基于新支点裁决，来不断裂变、收缩、移除当前分区。

1. **裂变**：支点在中间，一分为二，继续二路分治（先右后左）
2. **衰减**：支点在末端（某一侧为空）或某一侧只有一个元素，抹掉支点末端（侧），缩小当前分区
3. **衰亡**：执行partition后分治完成，移除当前分区

    - 当前分区只有两元素；
    - 当前分区有三个元素，返回的pivot居中；

## Python代码

Python 提供的列表（list）可以模拟栈，另外也可单向访问双端队列（collections.deque）用作栈。

- 尾部压栈：list.append(e)
- 访问尾部：list[len-1]
- 尾部出栈：list.pop()
- 替换：先读取按需修改，再 pop 后 append

```Python
import random
from enum import Enum

class PivotPosition (Enum):
      Head=1 # 选择第一个元素作为基准元素
      Tail=2 # 选择最后一个元素作为基准元素

# 对子数组 A[l:h] 进行切割，返回pivot分治索引
# 如果没有发生交换，说明[l:h]已经就序，但为了保障递归条件，
# 即使每一条分治最终都抵达 base case，这里不进行特殊判断。
def partition_Lomuto(A: list, low: int, high: int, pivot_pos: PivotPosition=PivotPosition.Head) -> int:
    i = None
    if pivot_pos == PivotPosition.Head:
        i = low
        for j in range(low+1, high+1): # [low+1, high]
            if A[j] < A[low]:
                # swap current small to i
                i += 1
                # 如果j=i，即小值A[j]已在其位，可判断不交换
                A[j],A[i] = A[i],A[j]
        # 将首pivot交换到最右小值位置
        # 本轮分治完成：[小值],pivot,[大值]
        A[low],A[i] = A[i],A[low]
    elif pivot_pos == PivotPosition.Tail:
        # 初始化最右小值索引
        i = low-1
        for j in range(low, high): # [low, high-1]
            if A[j] < A[high]:
                # swap current small to i
                i += 1
                # 如果j=i，即小值A[j]已在其位，可判断不交换
                A[j],A[i] = A[i],A[j]
        # 将尾pivot交换归位到最右小值右边
        # 本轮分治完成：[小值],pivot,[大值]
        i+= 1
        A[high],A[i] = A[i],A[high]

    #A 打印调试信息
    print('A[{}:{}]={}, pivot={}'.format(low, high, A[low:high+1], i))
    # 返回 pivot 索引
    return i

# 用栈代替递归，用栈记录待治理的分区索引，初始压栈 tuple(0, len(A)-1)，代表整个序列。
# 执行 Lomuto partition scheme 对栈顶分区进行分治，根据返回的支点，重新划分子分区：
# 1. 新支点左右分区大小均超过1，当前区间一分为二，删除当前分区，新增两个左右分区
# 2. 抵达base case：两元素（pivot左或右）或三元素（pivot居中），分区分治完成，移除当前分区
# 3. 新支点左/右侧为空或单元素，裁剪左/右侧base case，缩小更新当前分区
# 当待治理的分区栈被清空，意味着整个分治流程完成。
def qsort_Stack(A: list):
    # base case 1: overlap: low=high，只有一个元素
    # base case 2: cross: high<low，左空(0,-1)，右空(h+1, h)
    if len(A) <= 1:
        return
    # 分区索引范围栈（slice index range tuple list）
    slice_range_stack = [(0, len(A)-1)]
    while slice_range_stack: # 非空
        slice_range = slice_range_stack[len(slice_range_stack)-1] # tail
        low = slice_range[0]; high = slice_range[1] # start, stop
        pivot = partition_Lomuto(A, low, high)
        # 左右分区大小均超过1，当前区间一分为二
        if pivot-low>1 and high-pivot>1:
            left_range = (low, pivot-1)
            right_range = (pivot+1, high)
            e = slice_range_stack.pop() # pop tail
            slice_range_stack.append(left_range) # 新增左分区
            slice_range_stack.append(right_range) # 新增右分区
            print('    {} -> {} + {} + {}'.format(e, left_range, pivot, right_range))
        else: # 单边就序
            # base case：两元素（pivot左或右）或三元素（pivot居中）
            if pivot-low<=1 and high-pivot<=1:
                e = slice_range_stack.pop() # pop tail
                print('    pivot={}, pop {}'.format(pivot, e))
            elif pivot-low<=1: # 左侧为空或单元素，shrink左侧
                slice_range = (pivot+1, high) # 缩小分区
                e = slice_range_stack.pop() # pop tail
                slice_range_stack.append(slice_range)
                print('    pivot={}, shrink left: {} -> {}'.format(pivot, e, slice_range))
            elif high-pivot<=1: # 右侧为空或单元素，shrink右侧
                slice_range = (low, pivot-1) # 缩小分区
                e = slice_range_stack.pop() # pop tail
                slice_range_stack.append(slice_range)
                print('    pivot={}, shrink right: {} -> {}'.format(pivot, e, slice_range))

if __name__ == "__main__":
    # 在 [1,10] 之间随机挑选6个数
    n = 6; left = 1; right = 10
    iList = random.sample(range(left,right+1), n)
    print('iList =', iList)
    qsort_Stack(iList)
    print('sorted iList =', iList)
    print('-'*40)
    # 重复部分元素
    cList = random.sample(iList, k=10, counts=[1,2,3,1,2,1])
    print('cList =', cList)
    qsort_Stack(cList)
    print('sorted cList =', cList)
    print('-'*40)
    # 测试用例：最左侧、最右侧部分已经排好序。
    A = [2, 3, 5, 9, 4, 6, 8, 9, 10, 10]
    print('A =', A)
    qsort_Stack(A)
    print('sorted A =', A)
    print('-'*40)

    # 测试用例：https://en.wikipedia.org/wiki/File:Quicksort-example.gif
    A2 = [6, 5, 3, 1, 8, 7, 2, 4]
    # 测试用例：来源于 geeksforgeeks
    # A2 = [10, 80, 30, 90, 40, 50, 70]
    # 测试用例：来自陈峰棋《数据结构C语言版》
    # A2 = ['d', 'e', 'a', 'c', 'f', 'b', 'h', 'g']
    # A2 = [100, 101, 97, 99, 102, 98, 104, 103]
    # 测试用例：来源于 严蔚敏-《数据结构(C语言版）（第2版）》
    # A2 = [49, 38, 65, 97, 76, 13, 27, 49]
    print('A2 =', A2)
    qsort_Stack(A2)
    print('sorted A2 =', A2)
    print('-'*40)

    # 测试用例：完全逆序。
    A3 = list(range(20,30))
    A3.reverse()
    print('A3 =', A3)
    qsort_Stack(A3)
    print('sorted A3 =', A3)
    print('-'*40)
    # 测试用例：初始有序。
    print('A3 =', A3)
    qsort_Stack(A3)
    print('sorted2 A3 =', A3)
```
