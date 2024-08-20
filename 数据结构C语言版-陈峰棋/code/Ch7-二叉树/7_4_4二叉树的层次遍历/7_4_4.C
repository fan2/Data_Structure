/* ======================================== */
/*    程式实例: 7_4_4.c                      */
/*    二叉树的层次遍历                         */
/*    gcc -x c queue.c 7_4_4.C -o 7_4_4     */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* ---------------------------------------- */
/*  插入二叉树的节点                           */
/* ---------------------------------------- */
btree insertnode(btree root, int value)
{
    btree newnode; /* 树根指标           */
    btree current; /* 目前树节点指标      */
    btree back;    /* 父节点指标         */

    /* 建立新节点记忆体 */
    newnode = (btree)malloc(sizeof(treenode));
    newnode->data = value; /* 建立节点内容       */
    newnode->left = NULL;  /* 设定指标初值       */
    newnode->right = NULL; /* 设定指标初值       */
    if (root == NULL)      /* 是否是根节点       */
    {
        return newnode; /* 传回新节点位置     */
    }
    else
    {
        current = root; /* 保留目前树指标     */
        while (current != NULL)
        {
            back = current;              /* 保留父节点指标  */
            if (current->data > value)   /* 比较节点值     */
                current = current->left; /* 左子树        */
            else
                current = current->right; /* 右子树        */
        }
        if (back->data > value)   /* 接起父子的链结     */
            back->left = newnode; /* 左子树           */
        else
            back->right = newnode; /* 右子树            */
    }
    return root; /* 传回树根指标       */
}

/* ---------------------------------------- */
/*  建立二叉树                                */
/* ---------------------------------------- */
btree createbtree(int *data, int len)
{
    btree root = NULL; /* 树根指标           */
    int i;

    for (i = 0; i < len; i++) /* 用回路建立树状结构 */
        root = insertnode(root, data[i]);
    return root;
}

/* ---------------------------------------- */
/*  二叉树层次遍历                            */
/* ---------------------------------------- */
void levelorder(btree ptr)
{
    if (ptr != NULL) /* 终止条件           */
    {
        int index = 0;
        int data[MAXNODE] = {0};

        struct node_queue curLayerQueue;
        initqueue(&curLayerQueue);
        // debugqueue(&curLayerQueue, 1);
        printf("> levelorder: init current layer with root node = %d\n", ptr->data);
        enqueue(&curLayerQueue, ptr); // 根节点先入队列

        struct node_queue nextLayerQueue;
        initqueue(&nextLayerQueue);
        // debugqueue(&nextLayerQueue, 1);

        while (1)
        {
            // 遍历当前层
            if (!isemptyqueue(&curLayerQueue))
            {
                puts(">> levelorder: dequeue current node");
                btree node = dequeue(&curLayerQueue);
                data[index++] = node->data;
                printf(">> levelorder: current node = %d\n", node->data);
                // 统计下一层
                if (node->left)
                {
                    printf(">>> levelorder: enqueue left node = %d\n", node->left->data);
                    enqueue(&nextLayerQueue, node->left);
                }
                if (node->right)
                {
                    printf(">>> levelorder: enqueue right node = %d\n", node->right->data);
                    enqueue(&nextLayerQueue, node->right);
                }
            }
            else
            {
                // 进入下一层
                if (isemptyqueue(&nextLayerQueue))
                {
                    // 下一层为空
                    puts(">> levelorder: next layer is empty.");
                    break;
                }
                else
                {
                    // 迭代下一层
                    puts(">> levelorder: iterate next layer.");
                    movequeue(&curLayerQueue, &nextLayerQueue);
                }
            }
        }

        puts("levelorder:");
        for (int i = 0; i < index; i++)
        {
            printf("%d\n", data[i]);
        }
    }
}

/* ---------------------------------------- */
/*  主程式: 建立二叉树且用层次遍历列印出来.        */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    btree root = NULL; /* 树根指标           */

    /* 二叉树节点数据 */
    int data[9] = {5, 6, 4, 8, 2, 3, 7, 1, 9};
    root = createbtree(data, 9); /* 建立二叉树         */
    levelorder(root);            /* 前序遍历二叉树     */

    return 0;
}
