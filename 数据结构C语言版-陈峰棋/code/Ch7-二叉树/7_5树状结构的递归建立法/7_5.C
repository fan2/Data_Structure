/* ======================================== */
/*    程式实例: 7_5.c                        */
/*    树状结构的递归建立法                     */
/* ======================================== */
/*
 * 为了能从数组直接取得二叉树的节点数据，输入使用 7_3_1 中的二叉树数组。
 * 本质就是将数组表示法转换成二叉树表示法。
 */
#include <stdio.h>
#include <stdlib.h>

struct tree /* 树的结构宣告       */
{
    int data;           /* 节点数据          */
    struct tree *left;  /* 指向左子树的指标   */
    struct tree *right; /* 指向右子树的指标   */
};
typedef struct tree treenode; /* 树的结构新型态    */
typedef treenode *btree;      /* 宣告树节点指标型态 */

/* ---------------------------------------- */
/*  建立树状结构(参考 6_3_A 和 7_3_2)          */
/* ---------------------------------------- */
btree createbtree(int *data, int pos) {
    // 4 层二叉树，迭代索引不超过 15，递归基如下：
    // 1. 子层索引超过 15(overflow=-1)，父节点是第4层叶节点。
    // 2. 子层索引不超过 15，但值为 0，表示该左/右子树节点为空。
    if (pos > 15 || data[pos] == 0) {
        // int q = pos / 2; // top index
        int r = pos % 2;  // left(0) or right(1)
        if (pos > 15)
            printf("    top is leaf: ");
        else
            printf("    top->%s=NULL: ", r ? "right" : "left");
        return NULL;
    } else {
        /* 建立新节点记忆体 */
        btree newnode = (btree)malloc(sizeof(treenode));
        if (!newnode) {
            printf("createbtree malloc node for pos[%d] failed!\n", pos);
            exit(EXIT_FAILURE);  // 终止程序
        }
        newnode->data = data[pos]; /* 建立节点内容       */
        printf("createbtree newnode: pos=%d, data=%d\n", pos, data[pos]);
        /* 建立左子树的递归呼叫 */
        newnode->left = createbtree(data, 2 * pos);
        printf("pos=%d, left=%d:%d\n", pos, 2 * pos,
               newnode->left ? data[2 * pos] : (2 * pos > 15 ? -1 : 0));
        /* 建立右子树的递归呼叫 */
        newnode->right = createbtree(data, 2 * pos + 1);
        printf(
            "pos=%d, right=%d:%d\n", pos, 2 * pos + 1,
            newnode->right ? data[2 * pos + 1] : ((2 * pos + 1) > 15 ? -1 : 0));
        printf("    return node: %d:%d\n", pos, data[pos]);
        /* 返回构造好的根节点   */
        return newnode;
    }
}

/* ---------------------------------------- */
/*  二叉树的中序遍历递归列印                    */
/* ---------------------------------------- */
void printbtree(btree ptr) {
    if (ptr != NULL) {
        printbtree(ptr->left);      /* 左子树             */
        printf("[%2d]", ptr->data); /* 列印节点内容        */
        printbtree(ptr->right);     /* 右子树             */
    }
    // else /* 隐含终止条件 */
}

/* ---------------------------------------- */
/*  主程式: 建立链结的二叉树且列印出来.           */
/* ---------------------------------------- */
/*
                5(1)
         4(2)          6(3)
     2(4)                   8(7)
 1(8)    3(9)          7(14)    9(15)
*/
int main(int argc, char *argv[]) {
    /* 4 层二叉树节点数据：7_3_1 的数组表示 */
    int data[16] = {0, 5, 4, 6, 2, 0, 0, 8, 1, 3, 0, 0, 0, 0, 7, 9};
    btree root = createbtree(data, 1); /* 建立树状结构       */
    printf("数组的节点内容 \n");
    for (int i = 1; i < 16; i++)
        printf("[%2d]", data[i]); /* 列印节点内容       */
    printf("\n");
    printf("树的节点内容(inorder) \n");
    printbtree(root); /* 列出节点内容       */
    printf("\n");

    return 0;
}
