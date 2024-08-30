/* ======================================== */
/*    程式实例: 7_4_4.c                      */
/*    二叉树的层次遍历(level‑order traversal)  */
/*    gcc -x c queue.c 7_4_4.C -o 7_4_4     */
/* ======================================== */
/*
 * createbtree-insertnode 复用 7_3_3
 */
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/* ---------------------------------------- */
/*  插入二叉树的节点                           */
/* ---------------------------------------- */
btree insertnode(btree root, int value) {
    /* 为 value 建立新节点记忆体 */
    btree newnode = (btree)malloc(sizeof(treenode));
    if (!newnode) {
        printf("insertnode malloc node[%d] failed!\n", value);
        exit(EXIT_FAILURE);  // 终止程序
    }
    newnode->data = value; /* 建立节点内容       */
    newnode->left = NULL;  /* 设定指标初值       */
    newnode->right = NULL; /* 设定指标初值       */
    if (root == NULL) {
        /* 首次调用，传回新节点作为根节点 */
        printf("insertnode: root = %d\n", value);
        return newnode;
    } else {
        btree current = root; /* 保留目前树指标     */
        btree back;           /* 挂接父节点指标     */
        // 关键步骤：通过循环比较左右子树，确定挂接的父节点（子树）
        while (current != NULL) {
            back = current;              /* 保留当前父节点 */
            if (current->data > value)   /* 比较节点值    */
                current = current->left; /* 应挂左子树    */
            else
                current = current->right; /* 应挂右子树    */
            // current 迭代为 back->left 或 back->right 为空，
            // 下一轮退出 while 循环，back 记录了应该挂接的父节点。
        }
        // 再次将 value 与 back 的值比较，以确定挂接左子树还是右子树
        if (back->data > value) {
            printf("insertnode: node[%d]->left=%d\n", back->data, value);
            back->left = newnode; /* 挂接到 back 左子树        */
        } else {
            printf("insertnode: node[%d]->right=%d\n", back->data, value);
            back->right = newnode; /* 挂接到 back 右子树        */
        }
    }
    return root; /* 传回挂接 value 后最新的树根指标 */
}

/* ---------------------------------------- */
/*  建立二叉树                                */
/* ---------------------------------------- */
btree createbtree(int *data, int len) {
    btree root = NULL; /* 树根指标           */

    /* 用回路建立树状结构 */
    for (int i = 0; i < len; i++)
        root = insertnode(root, data[i]);
    return root;
}

/* ---------------------------------------- */
/*  二叉树前序遍历                            */
/* ---------------------------------------- */
void preorder(btree root) {
    btree ptr = root;
    if (ptr != NULL) {
        printf("[%2d]\n", ptr->data); /* 列印节点内容     */
        preorder(ptr->left);          /* 左子树          */
        preorder(ptr->right);         /* 右子树          */
    }
    // else /* 隐含终止条件 */
}

/* ---------------------------------------- */
/*  二叉树中序遍历                            */
/* ---------------------------------------- */
void inorder(btree root) {
    btree ptr = root;
    if (ptr != NULL) {
        inorder(ptr->left);           /* 左子树          */
        printf("[%2d]\n", ptr->data); /* 列印节点内容     */
        inorder(ptr->right);          /* 右子树          */
    }
    // else /* 隐含终止条件 */
}

/* ---------------------------------------- */
/*  二叉树后序遍历                            */
/* ---------------------------------------- */
void postorder(btree root) {
    btree ptr = root;
    if (ptr != NULL) {
        postorder(ptr->left);         /* 左子树          */
        postorder(ptr->right);        /* 右子树          */
        printf("[%2d]\n", ptr->data); /* 列印节点内容     */
    }
    // else /* 隐含终止条件 */
}

/* ---------------------------------------- */
/*  二叉树层次遍历(基于两个队列实现)             */
/* ---------------------------------------- */
void levelorder(btree root) {
    btree ptr = root;
    if (ptr != NULL) /* 终止条件           */
    {
        int index = 0;
        int data[15] = {0};  // 4 层满二叉树结点数=2^4-1

        struct node_queue curLayerQueue;
        initqueue(&curLayerQueue);
        // debugqueue(&curLayerQueue, 1);
        printf("> levelorder: init current layer with root node = %d\n",
               ptr->data);
        enqueue(&curLayerQueue, ptr);  // 根节点先入队列

        struct node_queue nextLayerQueue;
        initqueue(&nextLayerQueue);
        // debugqueue(&nextLayerQueue, 1);

        while (1) {
            // 遍历当前层
            if (!isemptyqueue(&curLayerQueue)) {
                puts(">> levelorder: dequeue current node");
                btree node = dequeue(&curLayerQueue);
                data[index++] = node->data;
                printf(">> levelorder: current node = %d\n", node->data);
                // 统计下一层
                if (node->left) {
                    printf(">>> levelorder: enqueue left node = %d\n",
                           node->left->data);
                    enqueue(&nextLayerQueue, node->left);
                }
                if (node->right) {
                    printf(">>> levelorder: enqueue right node = %d\n",
                           node->right->data);
                    enqueue(&nextLayerQueue, node->right);
                }
            } else {
                // 进入下一层
                if (isemptyqueue(&nextLayerQueue)) {
                    // 下一层为空
                    puts(">> levelorder: next layer is empty.");
                    break;
                } else {
                    // 迭代下一层
                    puts(">> levelorder: iterate next layer.");
                    movequeue(&curLayerQueue, &nextLayerQueue);
                }
            }
        }

        puts("levelorder:");
        for (int i = 0; i < index; i++) {
            printf("[%2d]\n", data[i]);
        }
    }
}

/* ---------------------------------------- */
/*  二叉树层次遍历(优化为基于一个队列实现)        */
/* ---------------------------------------- */
void levelorder1(btree root) {
    btree ptr = root;
    if (ptr != NULL) /* 终止条件           */
    {
        int index = 0;
        int data[15] = {0};  // 4 层满二叉树结点数=2^4-1

        struct node_queue curLayerQueue;
        initqueue(&curLayerQueue);
        debugqueue(&curLayerQueue, 1);
        printf("> levelorder: init current layer with root node = %d\n",
               ptr->data);
        enqueue(&curLayerQueue, ptr);  // 根节点先入队列

        while (!isemptyqueue(&curLayerQueue)) {
            puts(">> levelorder: dequeue current node");
            btree node = dequeue(&curLayerQueue);
            data[index++] = node->data;
            printf(">> levelorder: current node = %d\n", node->data);
            // 统计下一层，下一层的左右子树总是追加到本层队尾，实现层序遍历
            if (node->left) {
                printf(">>> levelorder: enqueue left node = %d\n",
                       node->left->data);
                enqueue(&curLayerQueue, node->left);
            }
            if (node->right) {
                printf(">>> levelorder: enqueue right node = %d\n",
                       node->right->data);
                enqueue(&curLayerQueue, node->right);
            }
        }

        puts("levelorder:");
        for (int i = 0; i < index; i++) {
            printf("[%2d]\n", data[i]);
        }
    }
}

/*
          5
        4   6
      2       8
    1   3   7   9
*/
void test1() {
    /* 二叉树节点数据: 第 4 层 4 个结点，设置 MAXNODE (4+1) */
    int data[9] = {5, 6, 4, 8, 2, 3, 7, 1, 9};
    btree root = createbtree(data, 9);
    puts("preorder:");
    preorder(root);
    puts("inorder:");
    inorder(root);
    puts("postorder:");
    postorder(root);
    /* 层次遍历二叉树 */
    levelorder1(root);
}

/*
                        8
             4                       12
       2          6           10            14
    1     3    5     7     9      11    13      15
*/
void test2() {
    /* 满二叉树: 第 4 层 8 个结点，设置 MAXNODE (8+1) */
    int data[15] = {8, 4, 2, 6, 1, 3, 5, 7, 12, 10, 14, 9, 11, 13, 15};
    btree root = createbtree(data, 15);
    puts("preorder:");
    preorder(root);
    puts("inorder:");
    inorder(root);
    puts("postorder:");
    postorder(root);
    /* 层次遍历二叉树 */
    levelorder1(root);
}

/* ---------------------------------------- */
/*  主程式: 建立二叉树且用层次遍历列印出来.        */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    // test1();
    test2();

    return 0;
}
