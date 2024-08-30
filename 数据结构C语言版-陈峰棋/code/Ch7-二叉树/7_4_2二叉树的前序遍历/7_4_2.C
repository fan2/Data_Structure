/* ======================================== */
/*    程式实例: 7_4_2.c                      */
/*    二叉树的前序遍历(Preorder Traversal)     */
/* ======================================== */
/*
 * createbtree-insertnode 复用 7_3_3
 */
#include <stdio.h>
#include <stdlib.h>

struct tree /* 树的结构宣告       */
{
    int data;           /* 节点数据          */
    struct tree *left;  /* 指向左子树的指标   */
    struct tree *right; /* 指向右子树的指标   */
};
typedef struct tree treenode; /* 树的结构新型态     */
typedef treenode *btree;      /* 宣告树节点指标型态  */

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
void preorder(btree ptr) {
    if (ptr != NULL) {
        printf("[%2d]\n", ptr->data); /* 列印节点内容     */
        preorder(ptr->left);          /* 左子树          */
        preorder(ptr->right);         /* 右子树          */
    }
    // else /* 隐含终止条件 */
}

/*
          5
        4   6
      2       8
    1   3   7   9
*/
void test1() {
    /* 二叉树节点数据 */
    int data[9] = {5, 6, 4, 8, 2, 3, 7, 1, 9};
    btree root = createbtree(data, 9);
    printf("树的节点内容(preorder)：\n");
    preorder(root);
}

/*
                        8
             4                       12
       2          6           10            14
    1     3    5     7     9      11    13      15
*/
void test2() {
    /* 满二叉树: 第 4 层 8 个结点 */
    int data[15] = {8, 4, 2, 6, 1, 3, 5, 7, 12, 10, 14, 9, 11, 13, 15};
    btree root = createbtree(data, 15);
    printf("树的节点内容(preorder)：\n");
    preorder(root);
}

/* ---------------------------------------- */
/*  主程式: 建立二叉树且用前序遍历列印出来.       */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    test1();
    test2();

    return 0;
}
