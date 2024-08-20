
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
void initqueue(struct node_queue *que)
{
    memset(que->nodes, 0, sizeof(que->nodes));
    que->front = -1;
    que->rear = -1;
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
    if (que->rear == (MAXNODE - 1) && que->front <= 0 ||
        que->rear + 1 == que->front /* 环形追尾 */)
    {
        if (que->debug)
            printf("    enqueue[%p]: rear-end collision.\n", que);
        return -1; /* 无法存入           */
    }
    que->rear++;                  /* 后端指标往前移      */
    if (que->rear == MAXNODE)     /* 是否超过界限        */
        que->rear = 0;            /* 从头开始           */
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
    que->front++;              /* 前端指标往前移        */
    if (que->front == MAXNODE) /* 是否超过界限          */
        que->front = 0;        /* 从头开始(maybe que->rear) */

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