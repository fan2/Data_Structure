/* ======================================== */
/*    程式实例: 3_7.c                        */
/*    链结串列的节点插入                       */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

struct llist /* 串列结构宣告      */
{
    int num;            /* 邮寄编号          */
    struct llist *next; /* 指向下一标签      */
};
typedef struct llist node; /* 定义新型态       */
typedef node *llink;       /* 定义新型态指标    */

/* ---------------------------------------- */
/*  链结串列的列印                            */
/* ---------------------------------------- */
void printllist(llink ptr)
{
    while (ptr != NULL) /* 串列走访回路      */
    {
        printf("[%d]", ptr->num); /* 列印节点资料      */
        ptr = ptr->next;          /* 指向下一节点      */
    }
    printf("\n"); /* 换行              */
}

/* ---------------------------------------- */
/*  链结串列的建立                            */
/* ---------------------------------------- */
llink createllist(int *array, int len)
{
    llink head; /* 串列的开始指标    */
    llink ptr, ptr1;
    int i;

    /* 建立第一个节点 */
    head = (llink)malloc(sizeof(node)); /* 配置记忆体 */
    if (!head)                          /* 检查指标   */
        return NULL;
    head->num = array[0];     /* 建立节点内容      */
    head->next = NULL;        /* 设定指标初值      */
    ptr = head;               /* 将ptr指向串列开始 */
    for (i = 1; i < len; i++) /* 建立其它节点回路   */
    {
        ptr1 = (llink)malloc(sizeof(node));
        if (!ptr1)
            return NULL;
        ptr1->num = array[i]; /* 建立节点内容      */
        ptr1->next = NULL;    /* 设定指标初值      */
        ptr->next = ptr1;     /* 连结节点         */
        ptr = ptr->next;      /* 指向下一节点      */
    }
    return head;
}

/* ---------------------------------------- */
/*  链结串列的节点走访                         */
/* ---------------------------------------- */
llink findnode(llink head, int num)
{
    llink ptr;

    ptr = head;         /* 指向串列起始      */
    while (ptr != NULL) /* 走访串列         */
    {
        if (ptr->num == num) /* 找寻编号        */
            return ptr;
        ptr = ptr->next; /* 指向下一节点      */
    }

    return ptr;
}

/* ---------------------------------------- */
/*  链结串列的节点插入                         */
/* ---------------------------------------- */
llink insertnode(llink head, llink ptr, int value)
{
    llink newNode; /* 新节点指标变数    */

    newNode = (llink)malloc(sizeof(node)); /* 建立新节点 */
    if (!newNode)
        return NULL;
    newNode->num = value; /* 建立节点内容      */
    newNode->next = NULL; /* 设定指标初值      */

    if (ptr == NULL) /* 指标ptr是否是NULL */
    {
        /* 第一种情况: 插入第一个节点 */
        newNode->next = head; /* 新节点成为串列开始 */
        return newNode;
    }
    else
    {
        if (ptr->next == NULL) /* 是否是串列结束    */
            /* 第二种情况: 插入最後一个节点 */
            ptr->next = newNode; /* 最後指向新节点    */
        else
        {
            /* 第三种情况: 插入成为中间节点 */
            newNode->next = ptr->next; /* 新节点指向下一节点 */
            ptr->next = newNode;       /* 节点ptr指向新节点 */
        }

        // 第二、三种情况，可省略判断简化为：
        // newNode->next = ptr->next;
        // ptr->next = newNode;
    }

    return head;
}

/* ---------------------------------------- */
/*  链结串列的记忆体释回                       */
/* ---------------------------------------- */
void freellist(llink head)
{
    llink ptr;

    while (head != NULL) /* 走访串列回路      */
    {
        ptr = head;
        head = head->next; /* 指向下一节点     */
        free(ptr);         /* 释回节点记忆体    */
    }
}

/* ---------------------------------------- */
/*  主程式: 找到邮寄编号後, 将之插入串列.         */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    int llist1[6] = {1, 2, 3, 4, 5, 6}; /* 阵列内容    */
    llink head;                         /* 指向串列开始 */
    llink ptr;
    int num;   /* 邮寄编号变数      */
    int value; /* 新插入邮寄编号    */

    head = createllist(llist1, 6); /* 建立串列    */
    if (!head)
    {
        printf("记忆体配置失败! \n");
        exit(1);
    }
    printf("原来的链表: ");
    printllist(head); /* 列印原来串列      */
    while (1)
    {
        printf("请输入要插入其后的邮寄编号 ==> ");
        scanf("%d", &num); /* 读取邮寄编号      */
        if (num != -1)
        {
            ptr = findnode(head, num); /* 找寻邮寄编号    */
            printf("请输入新插入的邮寄编号 ==> ");
            scanf("%d", &value); /* 读取新邮寄编号    */
            /* 插入新节点至节点ptr之後,如果没找到邮寄编号则 */
            /* 插入成为串列的开始. 因指标ptr是NULL.      */
            head = insertnode(head, ptr, value);
            if (!head)
            {
                printf("记忆体配置失败! \n");
                exit(1);
            }
            printf("插入后的链表: ");
            printllist(head); /* 列印插入後串列    */
        }
        else
            exit(1); /* 结束离开          */
    }

    freellist(head); /* 释回串列记忆体    */

    return 0;
}