/* ======================================== */
/*    程式实例: 6_3a.c                       */
/*    递归的链表建立和列印                     */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

struct list /* 链表结构宣告 */
{
    int data;          /* 节点资料         */
    struct list *next; /* 指向下一节点      */
};
typedef struct list node; /* 定义新型态       */
typedef node *link;       /* 定义新型态指标    */

/* ---------------------------------------- */
/*  递归链表列印函数                           */
/* ---------------------------------------- */
void print_list(link ptr) {
    if (ptr != NULL) {
        printf("[%d]", ptr->data);
        /* 递归链表列印函数调用 */
        print_list(ptr->next);
    }
    // else /* 隐含终止条件 */
}

/* ---------------------------------------- */
/*  递归链表建立函数                           */
/* ---------------------------------------- */
link create_list(int *array, int len, int pos) {
    link head; /* 链表节点的指标 */

    if (pos == len) /* 终止条件 */
        return NULL;
    else {
        /* 建立节点记忆体 */
        head = (link)malloc(sizeof(node));
        if (!head) return NULL;
        head->data = array[pos]; /* 建立节点内容     */
        head->next = create_list(array, len, pos + 1);
        return head;
    }
}

/* ---------------------------------------- */
/*  主程式: 建立链表后将内容印出.                */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    int list[6] = {1, 2, 3, 4, 5, 6};
    link head;

    head = create_list(list, 6, 0);
    if (!head) {
        printf("记忆体配置失败! \n");
        exit(1);
    }
    printf("链表的内容:\n");
    print_list(head);
    printf("\n");

    return 0;
}
