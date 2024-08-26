/* ======================================== */
/*    程式实例: 5_1b.c                       */
/*    使用数组来构建栈                        */
/* ======================================== */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>  // wchar_t, wprintf

#define MAXSTACK 100 /* 最大栈容量     */

int stack[MAXSTACK]; /* 栈的数组宣告   */
int top = -1;        /* 栈的顶端      */

/* ---------------------------------------- */
/*  栈资料的存入                              */
/* ---------------------------------------- */
int push(int value) {
    if (top >= MAXSTACK) /* 是否超过容量     */
    {
        printf("栈内容全满\n");
        return -1; /* 存入失败        */
    }
    top++;              /* 栈指标加一      */
    stack[top] = value; /* 存入栈         */

    return 0;  // success
}

/* ---------------------------------------- */
/*  栈资料的取出                              */
/* ---------------------------------------- */
int pop() {
    int temp;

    if (top < 0) /* 是否栈是空     */
    {
        printf("栈内容是空的\n");
        return -1; /* 取出失败         */
    }
    temp = stack[top]; /* 取出资料       */
    top--;             /* 栈指标减一     */
    return temp;       /* 栈取出        */
}

/* ---------------------------------------- */
/*  检查栈是否是空的                           */
/* ---------------------------------------- */
int empty() {
    if (top == -1) /* 是否是空         */
        return 1;  /* 空的            */
    else
        return 0; /* 不是空的         */
}

/* ---------------------------------------- */
/*  扑克牌四种花色                            */
/* ---------------------------------------- */
const wchar_t suits[] = {
    L'\u2665',  // L'♥', // Hearts
    L'\u2666',  // L'♦', // Diamonds
    L'\u2663',  // L'♣', // Clubs
    L'\u2660',  // L'♠', // Spades
};

/* ---------------------------------------- */
/*  洗牌（5 张，不包含大小王）                  */
/* ---------------------------------------- */
void shuffle() {
    int card[52]; /* 朴克牌数组       */
    int pos;      /* 牌代码          */
    int i;
    long temptime;
    srand(time(&temptime) % 60);          /* 使用时间初始乱数 */
    for (i = 0; i < 52; i++) card[i] = 0; /* 清除朴克牌数组   */
    i = 0;
    while (i != 5) /* 洗5张牌回路      */
    {
        pos = rand() % 52;  /* 乱数取值 0-51   */
        if (card[pos] == 0) /* 是否是未洗牌     */
        {
            push(pos);     /* 存此张牌进栈    */
            card[pos] = 1; /* 设定此张牌洗过  */
            i++;           /* 下一张牌       */
        }
    }
}

void dealcard() {
    // We set locale which is the same as the environmental variable
    // "LANG=en_US.UTF-8".
    setlocale(LC_ALL, "en_US.UTF-8");

    while (!empty()) /* 发完栈全部的牌 */
    {
        int temp = pop(); /* 取出栈资料     */
        // printf(" [%c%2d] ", temp / 13 + 3, temp % 13 + 1);
        int suit = temp / 13; /* 花色：0,1,2,3 */
        wprintf(L"[%lc", suits[suit]);
        int rank = temp % 13 + 1; /* 大小：1~13 */
        printf("%2d] ", rank);
    }
    printf("\n"); /* 换行 */
}

/* ---------------------------------------- */
/*  主程式: 运用empty()检查牌是否发完.         */
/*     红心: 数组  0 - 12                   */
/*     方块: 数组 13 - 25                   */
/*     梅花: 数组 26 - 38                   */
/*     黑桃: 数组 39 - 51                   */
/* ---------------------------------------- */
int main(int argc, char *argv[]) {
    shuffle();
    dealcard();

    return 0;
}
