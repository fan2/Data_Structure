/* ======================================== */
/*    程式实例: 5_10.c                       */
/*    使用数组来构建队列                       */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE 10 /* 队列的最大容量   */

int queue[MAXQUEUE]; /* 队列的数组宣告               */
int front = -1;      /* 队列的前端, 已读位置, de(++f) */
int rear = -1;       /* 队列的后端, 已写位置, en(++r) */

/* ---------------------------------------- */
/*  队列资料的存入                            */
/* ---------------------------------------- */
int enqueue(int value) {
    printf("    enqueue: front=%d, rear=%d.\n", front, rear);
    // if (rear >= MAXQUEUE) /* 检查队列是否全满  */
    if (rear + 1 >= MAXQUEUE) { /* +1 fix overflow */
        printf("    enqueue: rear-end.\n");
        return -1; /* 无法存入        */
    }
    // queue[++rear] = value;
    rear++;              /* 后端指标往前移   */
    queue[rear] = value; /* 存入队列        */
    printf("    enqueue[rear=%d] = %d\n", rear, value);

    return 0;  // success
}

/* ---------------------------------------- */
/*  队列资料的取出                            */
/* ---------------------------------------- */
int dequeue() {
    printf("    dequeue: front=%d, rear=%d.\n", front, rear);
    if (front == rear) { /* 检查队列是否是空  */
        printf("    dequeue: empty.\n");
        return -1; /* 无法取出        */
    }
    // return queue[++front];
    front++; /* 前端指标往前移   */
    printf("    dequeue[front=%d] = %d\n", front, queue[front]);
    return queue[front]; /* 队列取出        */
}

/* ---------------------------------------- */
/*  主程式: 模拟队列操作                       */
/*  输出输入的内容都会储存於数组中, 接着列        */
/*  印出数组内容来看其结果.                     */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    int input[100];  /* 储存输入的元素    */
    int output[100]; /* 储存取出的元素    */
    int select;      /* 选择项1,2,或3    */
    int i_count = 0; /* 数组input的索引  */
    int o_count = 0; /* 数组output的索引 */
    int loop = 1;    /* 回路控制         */
    int i, temp;

    while (loop) /* 主回路开始       */
    {
        /* 选项内容 */
        printf("[1]输入 [2]取出 [3]列出全部内容 ==> ");
        scanf("%d", &select); /* 读入选项         */
        switch (select) {
            /* 输入值后将之存入队列 */
            case 1:
                printf("请输入存入队列的值(%d) ==> ", i_count + 1);
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
                else {
                    printf("取出队列元素: %d\n", temp);
                    output[o_count++] = temp;
                }
                break;
            /* 离开回路 */
            case 3:
                loop = 0; /* 设定loop为零     */
                break;
        }
    }
    printf("输入队列的元素: ");   /* 输出结果    */
    for (i = 0; i < i_count; i++) /* 列印回路    */
        printf("[%d]", input[i]);
    printf("\n取出队列的元素: ");
    for (i = 0; i < o_count; i++) /* 列印回路    */
        printf("[%d]", output[i]);
    printf("\n剩下队列的元素: ");
    while ((temp = dequeue()) != -1) /*取出剩下队列元素*/
        printf("[%d]", temp);
    printf("\n"); /* 换行 */

    return 0;
}
