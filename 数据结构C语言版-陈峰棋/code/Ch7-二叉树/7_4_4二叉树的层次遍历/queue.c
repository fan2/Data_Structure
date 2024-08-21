
/* ======================================== */
/*    程式实例: 5_11.c                       */
/*    使用数组来构建环状队列                    */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/* ---------------------------------------- */
/*  初始化队列空队列                           */
/* ---------------------------------------- */
/*
 1. (front, rear)=(-1,-1):
    1.1. 初始，front=-1，可存满 5 个元素至 rear=4;
    1.2. 取出 1 个，front=0，rear=4，判断不能再存，实际容量衰减为 MAXQUEUE-1
    1.3. 再取 1 个，front=1，rear=4，可再存入 rear=0，然后 rear+1=front，不能再存

如此设计， 以便区分已空和全满这两种情况。

 2. (front, rear)=(0,0): 实际容量始终保持 MAXQUEUE-1
    1.1. 初始，空置rear=0，可存 4 个元素至 rear=4(1,2,3,4);
    1.2. 取出 1 个，front=1，rear=4，判断可再存入 rear=0
    1.3. 判断 rear+1=front，无法再存

如此修改，front空位相当于防止追尾的游标。
 */

void initqueue(struct node_queue *que)
{
    memset(que->nodes, 0, sizeof(que->nodes));
    que->front = 0;
    que->rear = 0;
    que->debug = 0;
}

/* ---------------------------------------- */
/*  启用队列的调试日志输出开关                   */
/* ---------------------------------------- */
void debugqueue(struct node_queue *que, int debug)
{
    que->debug = debug;
}

/* ---------------------------------------- */
/*  判断队列是否为空                           */
/* ---------------------------------------- */
int isemptyqueue(struct node_queue *que)
{
    if (que->front == que->rear)
    {
        /* 检查队列是否是空 */
        return 1;
    }

    return 0;
}

/* ---------------------------------------- */
/*  队列资料的存入(appendNode)                 */
/* ---------------------------------------- */
int enqueue(struct node_queue *que, btree node)
{
    if (que->debug)
        printf("    enqueue[%p]: front=%d, rear=%d.\n", que, que->front, que->rear);

    // if (que->rear + 1 == que->front || /* 检查队列是否全满    */
    //     (que->rear == (MAXNODE - 1) && que->front <= 0))
    if (que->rear == (MAXNODE - 1) && que->front == 0 ||
        que->rear + 1 == que->front /* 环形追尾 */)
    {
        if (que->debug)
            printf("    enqueue[%p]: rear-end collision.\n", que);
        return -1; /* 无法存入           */
    }
    // que->rear++;                  /* 后端指标往前移      */
    // if (que->rear == MAXNODE)     /* 是否超过界限        */
    //     que->rear = 0;            /* 从头开始           */
    que->rear = ((que->rear+1) % MAXNODE);

    que->nodes[que->rear] = node; /* 存入队列           */

    if (que->debug)
        printf("    enqueue[%p] [rear=%d] = %d\n", que, que->rear, node->data);

    return 0; // success
}

/* ---------------------------------------- */
/*  队列资料的取出                            */
/* ---------------------------------------- */
btree dequeue(struct node_queue *que)
{
    if (que->debug)
        printf("    dequeue[%p]: front=%d, rear=%d.\n", que, que->front, que->rear);
    if (que->front == que->rear)
    { /* 检查队列是否是空      */
        if (que->debug)
            printf("    dequeue[%p]: empty.\n", que);
        return NULL; /* 无法取出            */
    }
    // que->front++;              /* 前端指标往前移        */
    // if (que->front == MAXNODE) /* 是否超过界限          */
    //     que->front = 0;        /* 从头开始(maybe que->rear) */
    que->front = ((que->front+1) % MAXNODE);

    btree frontNode = que->nodes[que->front];
    if (que->debug)
        printf("    dequeue[%p] [front=%d] = %d\n", que, que->front, frontNode->data);
    return frontNode; /* 队列取出            */
}

void drainqueue(struct node_queue *que)
{
    if (que->debug)
        printf("drainqueue[%p].\n", que);
    while (dequeue(que))
        ;
}

void movequeue(struct node_queue *dstque, struct node_queue *srcque)
{
    if (dstque->debug)
        printf("<movequeue [%p] to [%p].\n", srcque, dstque);
    drainqueue(dstque);
    // initqueue(dstque);  // reset

    btree node = NULL;
    while ((node = dequeue(srcque)))
    {
        enqueue(dstque, node);
    }

    // initqueue(srcque); // reset
    if (dstque->debug)
        printf(">movequeue [%p] to [%p].\n", srcque, dstque);
}