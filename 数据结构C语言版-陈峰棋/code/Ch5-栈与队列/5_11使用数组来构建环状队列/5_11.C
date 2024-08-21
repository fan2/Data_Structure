/* ======================================== */
/*    程式实例: 5_11.c                       */
/*    使用数组来构建环状队列                    */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE (4+1) /* 队列的实际有效容量: MAXQUEUE-1 */

int queue[MAXQUEUE]; /* 队列的数组宣告 */

/*
 1. (front, rear)=(-1,-1):
    1.1. 初始，front=-1，可存满 5 个元素至 rear=4;
    1.2. 取出 1 个，front=0，rear=4，判断不能再存，实际容量衰减为 MAXQUEUE-1
    1.3. 再取 1 个，front=1，rear=4，可再存入 rear=0，然后 rear+1=front，不能再存

如此设计， 以便区分已空和全满这两种情况。
 */
// int front = -1;      /* 队列的前端, 已读位置, de(++f) */
// int rear = -1;       /* 队列的后端, 已写位置, en(++r) */

/*
 2. (front, rear)=(0,0): 实际容量始终保持 MAXQUEUE-1
    1.1. 初始，空置rear=0，可存 4 个元素至 rear=4(1,2,3,4);
    1.2. 取出 1 个，front=1，rear=4，判断可再存入 rear=0
    1.3. 判断 rear+1=front，无法再存

如此修改，front空位相当于防止追尾的游标。
 */
int front = 0;      /* 队列的前端, 已读位置, de(++f) */
int rear = 0;       /* 队列的后端, 已写位置, en(++r) */

/* ---------------------------------------- */
/*  队列资料的存入                             */
/* ---------------------------------------- */
int enqueue(int value)
{
    printf("    enqueue: front=%d, rear=%d.\n", front, rear);
    // if (rear + 1 == front || /* 检查队列是否全满    */
    //     (rear == (MAXQUEUE - 1) && front <= 0))
    if (rear == (MAXQUEUE - 1) && front == 0 ||
        rear + 1 == front /* 环形追尾 */)
    {
        printf("    enqueue: rear-end collision.\n");
        return -1; /* 无法存入           */
    }
    // rear++;               /* 后端指标往前移      */
    // if (rear == MAXQUEUE) /* 是否超过界限        */
    //     rear = 0;         /* 从头开始           */
    rear = ((rear+1) % MAXQUEUE);

    queue[rear] = value;  /* 存入队列           */
    printf("    enqueue[rear=%d] = %d\n", rear, value);

    return 0; // success
}

/* ---------------------------------------- */
/*  队列资料的取出                            */
/* ---------------------------------------- */
int dequeue()
{
    printf("    dequeue: front=%d, rear=%d.\n", front, rear);
    if (front == rear)
    { /* 检查队列是否是空      */
        printf("    dequeue: empty.\n");
        return -1; /* 无法取出            */
    }
    // front++;               /* 前端指标往前移        */
    // if (front == MAXQUEUE) /* 是否超过界限          */
    //     front = 0;         /* 从头开始(maybe rear) */
    front = ((front+1) % MAXQUEUE);

    printf("    dequeue[front=%d] = %d\n", front, queue[front]);
    return queue[front]; /* 队列取出            */
}

/* ---------------------------------------- */
/*  主程式: 模拟队列操作                       */
/*  输出输入的内容都会储存於数组中, 接着列        */
/*  印出数组内容来看其结果.                     */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    int input[100];  /* 储存输入的元素      */
    int output[100]; /* 储存取出的元素      */
    int select;      /* 选择项1,2,或3      */
    int i_count = 0; /* 数组input的索引    */
    int o_count = 0; /* 数组output的索引   */
    int loop = 1;    /* 回路控制           */
    int i, temp;
    while (loop) /* 主回路开始         */
    {
        /* 选项内容 */
        printf("[1]输入 [2]取出 [3]列出全部内容 ==> ");
        scanf("%d", &select); /* 读入选项 */
        switch (select)
        {
        /* 输入值后将之存入队列 */
        case 1:
            printf("请输入存入队列的值(%d) ==> ",
                   i_count + 1);
            scanf("%d", &temp);
            if (enqueue(temp) == -1)
                printf("队列全满.\n");
            else
                input[i_count++] = temp;
            break;
        /* 取出队列的内容 */
        case 2:
            if ((temp = dequeue()) == -1)
                printf("队列是空的.\n");
            else
            {
                printf("取出队列元素: %d\n", temp);
                output[o_count++] = temp;
            }
            break;
        /* 离开回路 */
        case 3:
            loop = 0; /* 设定loop为零 */
            break;
        }
    }
    printf("输入队列的元素: ");   /* 输出结果       */
    for (i = 0; i < i_count; i++) /* 列印回路       */
        printf("[%d]", input[i]);
    printf("\n取出队列的元素: ");
    for (i = 0; i < o_count; i++) /* 列印回路       */
        printf("[%d]", output[i]);
    printf("\n剩下队列的元素: ");
    while ((temp = dequeue()) != -1) /*取出剩下队列元素*/
        printf("[%d]", temp);
    printf("\n"); /* 换行 */

    return 0;
}
