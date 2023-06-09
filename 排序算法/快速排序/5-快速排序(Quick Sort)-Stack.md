
[TOC]

## 栈实现机制

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
    - 当前分区有三个元素，且返回的pivot居中；

## Python代码

Python 提供的列表（list）可以模拟栈，另外也可单向访问双端队列（collections.deque）用作栈。

- 尾部压栈：list.append(e)
- 访问尾部：list[len-1]
- 尾部出栈：list.pop()
- 替换：先读取按需修改，再 pop 后 append

具体 Python 实现代码，见 [quick_sort.ipynb](./quick_sort.ipynb)。

1. 初始化分治索引范围栈 slice_range_stack=tuple(0, len(A)-1)，代表整个序列亟待分治。
2. 主体是一个 while 大循环，循环条件是 slice_range_stack 非空，即分治尚未结束。
3. 伴随着分治的进行，局部无序逐步消除，同时栈上分区逐渐裂变、衰减。

    - 每当分治抵达base case，分治完成，移除分区。

4. 当 slice_range_stack 被排空时，循环结束，分治完成。
