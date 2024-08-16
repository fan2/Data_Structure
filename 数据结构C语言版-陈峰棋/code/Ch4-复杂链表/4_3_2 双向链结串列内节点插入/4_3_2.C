/* ======================================== */
/*    程序实例: 4_3_2.c                      */
/*    双向链表内结点插入                       */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

struct dlist /* 双向串列结构宣告   */
{
    int data;            /* 节点资料          */
    struct dlist *front; /* 指向下一节点的指标  */
    struct dlist *back;  /* 指向前一节点的指标  */
};
typedef struct dlist dnode; /* 双向串列新型态     */
typedef dnode *dlink;       /* 双向串列指标新型态  */

/* ---------------------------------------- */
/* 双向链表的输出                             */
/* ---------------------------------------- */
void printdlist(dlink head)
{
    while (head != NULL) /* 链表遍历循环 */
    {
        printf("[%d]", head->data); /* 输出结点数据   */
        head = head->front;         /* 指向下一个结点 */
    }
    printf("\n"); /* 换行         */
}

/* ---------------------------------------- */
/* 双向链表的结点插入                          */
/* ---------------------------------------- */
dlink insertnode(dlink head, dlink ptr, int value)
{
    dlink new_node; /* 新结点的指针 */

    /* 创建新结点，分配结点内存 */
    new_node = (dlink)malloc(sizeof(dnode));
    if (!new_node) /* 检查内存指针 */
        return NULL;
    new_node->data = value; /* 创建结点内容 */
    new_node->front = NULL; /* 设置指针初值 */
    new_node->back = NULL;  /* 设置指针初值 */

    if (head == NULL)    /* 如果链表是空的  */
        return new_node; /* 返回新结点指针  */

    if (ptr == NULL)
    {
        /* 第一种情况：插在第一个结点之前，成为链表开始 */
        new_node->front = head; /* 新结点指向链表开始 */
        head->back = new_node;  /* 原结点指向新结点   */
        head = new_node;        /* 新结点成为链表开始 */
    }
    else
    {
        if (ptr->front == NULL) /* 是否有下一个结点  */
        {
            /* 第二种情况：插在链表的最后 */
            ptr->front = new_node; /* 最后结点指向新结点 */
            new_node->back = ptr;  /* 新结点指回最后结点 */
        }
        else
        {
            /* 第三种情况：插入结点至链表中间结点内(ptr 之后) */
            ptr->front->back = new_node;  /* 下一结点指回新结点 */
            new_node->front = ptr->front; /* 新结点指向下一结点 */
            new_node->back = ptr;         /* 新结点指回插入结点 */
            ptr->front = new_node;        /* 插入结点指回新结点 */
        }
    }
    return head; /* 返回链表起始指针 */
}

/* ---------------------------------------- */
/*  主程序:                                  */
/*  使用插入结点的方式创建链表，完成后将链表内容输出 */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    dlink head = NULL;                /* 循环链表指针   */
    dlink tail = NULL;                /* 链表最后的指针 */
    int list[6] = {1, 2, 3, 4, 5, 6}; /* 数组内容      */
    int i;

    head = insertnode(head, head, list[0]); /* 创建第一个结点 */
    printdlist(head);                       /* 输出列表      */
    tail = head;                            /* 保留链表最后指针 */
    /* 第一种情况：插在第一个结点之前 */
    head = insertnode(head, NULL, list[1]);
    printdlist(head); /* 输出链表 */
    /* 第二种情况：插在链表的最后 */
    head = insertnode(head, tail, list[2]);
    printdlist(head);       /* 输出链表 */
    for (i = 3; i < 6; i++) /* 创建链表结点 */
    {
        /* 第三种情况：插入结点至链表中间结点内（head 之后） */
        head = insertnode(head, head, list[i]);
        printdlist(head); /* 输出链表 */
    }

    return 0;
}
