/* ======================================== */
/*    程式实例: 7_6.c                        */
/*    二叉树的搜索方式                         */
/* ======================================== */
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
/*  建立二叉树（详细创建日志跟踪参考 7_5）        */
/* ---------------------------------------- */
btree createbtree(int *data, int pos) {
    btree newnode; /* 新节点指标         */

    if (pos > 15 || data[pos] == 0) /* 终止条件       */
        return NULL;
    else {
        /* 建立新节点记忆体 */
        newnode = (btree)malloc(sizeof(treenode));
        if (!newnode) {
            printf("createbtree malloc node for pos[%d] failed!\n", pos);
            exit(EXIT_FAILURE);  // 终止程序
        }
        newnode->data = data[pos]; /* 建立节点内容       */
        /* 建立左子树的递归呼叫 */
        newnode->left = createbtree(data, 2 * pos);
        /* 建立右子树的递归呼叫 */
        newnode->right = createbtree(data, 2 * pos + 1);
        return newnode;
    }
}

/* ---------------------------------------- */
/*  二叉搜索树的搜索                           */
/* ---------------------------------------- */
btree btreefind(btree ptr, int value) {
    puts("btreefind: ignition");
    while (ptr != NULL) {
        if (ptr->data == value) {
            printf("btreefind: found node[%d]\n", ptr->data);
            return ptr; /* 传回节点指标 */
        } else if (ptr->data > value) {
            printf("    step further to node[%d]->left\n", ptr->data);
            ptr = ptr->left; /* 递进左子树 */
        } else {
            printf("    step further to node[%d]->right\n", ptr->data);
            ptr = ptr->right; /* 递进右子树 */
        }
    }
    return NULL; /* 没有找到           */
}

/* ---------------------------------------- */
/*  二叉树遍历搜索                            */
/* ---------------------------------------- */
btree btreesearch(btree ptr, int value) {
    btree ptr1, ptr2;

    if (ptr != NULL) {
        if (ptr->data == value) {
            printf("found node[%d]\n", ptr->data);
            return ptr;
        }

        /* 往左子树找 */
        if (ptr->left) {
            printf("step further to node[%d]->left\n", ptr->data);
            ptr1 = btreesearch(ptr->left, value);
            if (ptr1) {
                // printf("    node[%d] is on node[%d]->left\n", value,
                // ptr->data);
                return ptr1; /* 在左子树 */
            }
            printf("    node[%d] isn't on node[%d]->left\n", value, ptr->data);
        } else
            printf("    node[%d] has no left child\n", ptr->data);

        /* 往右子树找 */
        if (ptr->right) {
            printf("step further to node[%d]->right\n", ptr->data);
            ptr2 = btreesearch(ptr->right, value);
            if (ptr2) {
                // printf("    node[%d] is on node[%d]->right\n", value,
                // ptr->data);
                return ptr2; /* 在右子树 */
            }
            printf("    node[%d] isn't on node[%d]->right\n", value, ptr->data);
        } else
            printf("    node[%d] has no right child\n", ptr->data);

        /* 没有找到：既不在左子树，也不在右子树 */
        return NULL;
    } else {
        // puts("parent is leaf!");
        return NULL; /* 是叶节点           */
    }
}

/* ---------------------------------------- */
/*  主程式: 二叉树搜索方式.                    */
/* ---------------------------------------- */
/*
                5(1)
         4(2)          6(3)
     2(4)                   8(7)
 1(8)    3(9)          7(14)    9(15)
*/
int main(int argc, char *argv[]) {
    btree root = NULL; /* 树根指标           */
    btree ptr = NULL;  /* 树根指标           */
    int value;         /* 节点值             */

    /* 二叉树节点数据 */
    int data[16] = {0, 5, 4, 6, 2, 0, 0, 8, 1, 3, 0, 0, 0, 0, 7, 9};
    puts("数组的节点内容: ");
    for (int i = 1; i < 16; i++)
        printf("[%2d]", data[i]); /* 列印节点内容       */
    printf("\n");
    root = createbtree(data, 1); /* 建立树状结构       */
    printf("请输入寻找节点数据(1 - 9) ==> ");
    scanf("%d", &value);          /* 读取节点数据       */
    ptr = btreefind(root, value); /* 二叉树搜索         */
    if (ptr != NULL)
        printf("二叉搜索树: 节点数据是 [%d]\n", ptr->data);
    else
        printf("二叉搜索树: 没有找到\n");
    ptr = btreesearch(root, value); /* 遍历搜索         */
    if (ptr != NULL)
        printf("遍历搜索: 节点数据是 [%d]\n", ptr->data);
    else
        printf("遍历搜索: 没有找到\n");

    return 0;
}
