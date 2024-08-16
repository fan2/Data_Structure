/* ======================================== */
/*    程式实例: 5_13_1.c                     */
/*    使用数组来构建输入限制性双队列             */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE 10  /* 队列的最大容量     */

int queue[MAXQUEUE]; /* 队列的数组宣告       */
int front = -1;      /* 队列的前端, de(++f) */
int rear = -1;       /* 队列的后端, en(++r) */

/* ---------------------------------------- */
/*  队列资料的存入(rear append)               */
/* ---------------------------------------- */
int enqueue(int value)
{
    printf("    enqueue: front=%d, rear=%d.\n", front, rear);
    // if (rear + 1 == front || /* 检查队列是否全满   */
    //     (rear == (MAXQUEUE - 1) && front <= 0))
    if (rear == (MAXQUEUE - 1) && front <= 0 ||
        rear + 1 == front /* 环形追尾 */)
    {
        printf("    enqueue: rear-end collision.\n");
        return -1; /* 无法存入           */
    }
    rear++;               /* 后端指标往前移     */
    if (rear == MAXQUEUE) /* 是否超过界限       */
        rear = 0;         /* 从头开始          */
    queue[rear] = value;  /* 存入队列          */

    return 0; // success
}

/* ---------------------------------------- */
/*  队列资料的取出(从后端)                     */
/* ---------------------------------------- */
int dequeue_rear()
{
    printf("    dequeue_rear: front=%d, rear=%d.\n", front, rear);
    if (front == rear)
    { /* 检查队列是否是空      */
        printf("    dequeue_rear: empty.\n");
        return -1; /* 无法取出            */
    }

    int temp = queue[rear];
    printf("    dequeue_rear[%d] = %d\n", rear, temp);

    rear--;                      /* 后端指标往前移     */
    if (rear < 0 && front != -1) /* 是否超过界限       */
        rear = MAXQUEUE - 1;     /* 从最大值开始       */

    return temp;                 /* 队列取出          */
}

/* ---------------------------------------- */
/*  队列资料的取出(从前端)                     */
/* ---------------------------------------- */
int dequeue_front()
{
    printf("    dequeue_front: front=%d, rear=%d.\n", front, rear);
    if (front == rear)
    { /* 检查队列是否是空      */
        printf("    dequeue_front: empty.\n");
        return -1; /* 无法取出            */
    }
    front++;               /* 前端指标往前移         */
    if (front == MAXQUEUE) /* 是否超过界限          */
        front = 0;         /* 从头开始(maybe rear) */

    printf("    dequeue_front[%d] = %d\n", front, queue[front]);
    return queue[front];   /* 队列取出          */
}

/* ---------------------------------------- */
/*  主程式: 模拟双队列操作                     */
/*  输出输入的内容都会储存於数组中, 模拟双        */
/*  队列取出, 接着列印出数组内容来看其结果.       */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    int input_list[6] = /* 储存输入的元素     */
        {1, 2, 3, 4, 5, 6};
    int output_list[6]; /* 储存取出的元素     */
    int select;         /* 选择项1,2,或3      */
    int i, temp, pos = 0;

    for (i = 0; i < 6; i++) /* 将数组存入队列     */
        enqueue(input_list[i]);
    while (front != rear) /* 主回路开始         */
    {
        /* 选项内容 */
        printf("[1]从后取出 [2]从前取出 ==> ");
        scanf("%d", &select); /* 读入选项           */
        switch (select)
        {
        /* 从后端取出队列的内容 */
        case 1:
            temp = dequeue_rear();
            output_list[pos++] = temp;
            break;
        /* 从前端取出队列的内容 */
        case 2:
            temp = dequeue_front();
            output_list[pos++] = temp;
            break;
        }
    }
    printf("原来数组的顺序: "); /* 输出结果           */
    for (i = 0; i < 6; i++)     /* 列印回路           */
        printf("[%d]", input_list[i]);
    printf("\n队列取出的顺序: ");
    for (i = 0; i < 6; i++) /* 列印回路           */
        printf("[%d]", output_list[i]);
    printf("\n"); /* 换行 */

    return 0;
}
