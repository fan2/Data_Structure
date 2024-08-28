/* ======================================== */
/*    程式实例: 5_4_2.c                      */
/*    中序四则表达式的值（参考 5_7, 增加括号处理） */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_node /* 栈的结构宣告     */
{
    int data;                /* 栈资料            */
    struct stack_node *next; /* 指向下一节点       */
};
typedef struct stack_node stack_list; /* 串列新型态    */
typedef stack_list *link;             /* 串列指标新型态 */

link stack_operator = NULL; /* 运算子栈指标     */
link stack_operand = NULL;  /* 运算元栈指标     */

/* ---------------------------------------- */
/*  栈资料的存入                              */
/* ---------------------------------------- */
link push(link stack, int value) {
    link new_node; /* 新节点指标         */

    /* 配置节点记忆体 */
    new_node = (link)malloc(sizeof(stack_list));
    if (!new_node) {
        printf("记忆体配置失败! \n");
        return NULL; /* 存入失败           */
    }
    new_node->data = value; /* 建立节点内容    */
    new_node->next = stack; /* 新节点指向原开始 */
    stack = new_node;       /* 新节点成为栈开始 */

    return stack;
}

/* ---------------------------------------- */
/*  栈资料的取出                              */
/* ---------------------------------------- */
link pop(link stack, int *value) {
    link top; /* 指向栈顶端       */

    if (stack != NULL) {
        top = stack;         /* 指向栈顶端       */
        stack = stack->next; /* 栈指标指向下节点  */
        *value = top->data;  /* 取出资料         */
        free(top);           /* 释回节点记忆体    */
        return stack;        /* 传回栈指标       */
    } else
        *value = -1;

    return stack;
}

/* ---------------------------------------- */
/*  检查栈是否是空的                           */
/* ---------------------------------------- */
int empty(link stack) {
    if (stack == NULL) /* 是否是空           */
        return 1;      /* 空的              */
    else
        return 0; /* 不是空的           */
}

/* ---------------------------------------- */
/* 判断运算子（新增括号：左括号入栈，右括号匹配）   */
/* ---------------------------------------- */
int isoperator(char op) {
    switch (op) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            return 1; /* 是运算子           */

        default:
            return 0; /* 不是运算子         */
    }
}

/* ---------------------------------------- */
/* 运算子的优先权（强插左括号最低，括号内表达式最高）*/
/* ---------------------------------------- */
int priority(char op) {
    switch (op) {
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
            return 1;
        default:
            return 0;
    }
}

/* ---------------------------------------- */
/*  计算二元表达式的值                         */
/* ---------------------------------------- */
int get_value(int op, int operand1, int operand2) {
    switch ((char)op) {
        case '*':
            return (operand2 * operand1);
        case '/':
            return (operand2 / operand1);
        case '+':
            return (operand2 + operand1);
        case '-':
            return (operand2 - operand1);
    }

    return -1;  // should never reach here
}

/* ---------------------------------------- */
/*  读取字符串，替代 gets                      */
/* ---------------------------------------- */
// char* gets_s( char* str, rsize_t n );
void safe_gets(char *str, int size) {
    char *ret = fgets(str, size, stdin);
    if (ret) {
        // 移除结尾的回车/换行符
        char *posr = strchr(str, '\r');
        if (posr) *posr = 0;
        char *posn = strchr(str, '\n');
        if (posn) *posn = 0;
    }
}

/* ---------------------------------------- */
/*  主程式: 输入中序表达式后, 计算其值.          */
/* ---------------------------------------- */
// 这里只针对单字母ASCII值运算，对于多位数无法进行
/* test cases:
      | exp               | expr              | result |
      |-------------------|-------------------|--------|
   1. | a+b               | 4+8               | 12     |
   2. | a+b*c             | 4+8*3             | 28     |
   3. | a*b-c             | 4*8-3             | 29     |
   4. | a+b*c-d           | 4+8*3-7           | 21     |
   5. | a*b-c*d           | 4*8-3*7           | 11     |
   6. | a*(b+c)           | 4*(8+3)           | 44     |
   7. | (a+b)/c           | (4+8)/3           | 4      |
   8. | (a+b)*(c-d)       | (4+8)*(7-3)       | 48     |
   9. | a+b*(c-d)         | 4+8*(7-3)         | 36     |
   A. | a*b+c*(d-e)/f     | 4*8+9*(7-5)/3     | 38     |
   B. | a*b+c*(d*e-f)/g   | 4*8+9*(7*2-5)/3   | 59     |
   C. | a*b+c*(d-e*f)/g   | 4*8+9*(7-1*2)/3   | 47     |
   D. | a*b+c*(d-(e+f))/g | 4*8+5*(9-(1+2))/3 | 42     |
 */
int main(int argc, char *argv[]) {
    char exp[BUFSIZ / 10]; /* 表达式字符串变数    */
    int op = 0;            /* 运算子变数         */
    int operand1 = 0;      /* 前运算元变数       */
    int operand2 = 0;      /* 后运算元变数       */
    int result = 0;        /* 计算结果变数       */
    int pos = 0;           /* 目前表达式位置     */

    printf("请输入中序表达式 ==> ");
    safe_gets(exp, BUFSIZ / 10); /* 读取表达式 */
    /* 剖析表达式字符串回路：从左到右解析，运算子和操作数分开入栈 */
    while (exp[pos] != '\0' && exp[pos] != '\n') {
        if (isoperator(exp[pos])) /* 是不是运算子 */
        {
            // 左括号强插，先搁置已入栈运算子
            if (empty(stack_operator) || exp[pos] == '(') {
                /* 运算子入栈 */
                printf("    [1]push operator='%c'\n", exp[pos]);
                stack_operator = push(stack_operator, exp[pos]);
            } else {
                if (exp[pos] == ')') // 先计算括号内的子表达式
                {
                    puts("    deal operator=')'");
                    /* 取出运算子直到'(' */
                    while (stack_operator->data != '(') {
                        /* 计算括号内的表达式 */
                        stack_operator = pop(stack_operator, &op);
                        stack_operand = pop(stack_operand, &operand1);  // right
                        stack_operand = pop(stack_operand, &operand2);  // left
                        printf("      pop=%c,%d,%d, calc %d%c%d\n", op,
                               operand1, operand2, operand2, op, operand1);
                        /* 中间计算结果暂存入栈 */
                        stack_operand = push(stack_operand,
                                             get_value(op, operand1, operand2));
                    }
                    /* 弹出左括号 */
                    stack_operator = pop(stack_operator, &op);
                    puts("      pop operator='('");
                } else  // 普通运算子
                {
                    // 待闭合左括号优先级最低，入栈括号内的表达式
                    // 括号内的表达式可能也存在优先级问题，此处一并处理
                    // 比较当前运算子与栈顶(中)运算子优先权，弹出已入栈的高优先级运算子
                    while (!empty(stack_operator) &&
                           (priority(exp[pos]) <=
                            priority(stack_operator->data))) {
                        /* 执行高优先级计算 */
                        stack_operator = pop(stack_operator, &op);
                        stack_operand = pop(stack_operand, &operand1);  // right
                        stack_operand = pop(stack_operand, &operand2);  // left
                        printf(
                            "    hipri op=%c, op1=%d, op2=%d, calc "
                            "%d%c%d\n",
                            op, operand1, operand2, operand2, op, operand1);
                        /* 中间计算结果暂存入栈 */
                        stack_operand = push(stack_operand,
                                             get_value(op, operand1, operand2));
                    }
                    /* 处理完高优先级后，该运算子入栈 */
                    printf("    [2]push operator='%c'\n", exp[pos]);
                    stack_operator = push(stack_operator, exp[pos]);
                }
            }
        } else {
            /* 运算元直接入栈: left, right */
            printf("    push operand='%c'/%d\n", exp[pos], exp[pos] - 0x30);
            stack_operand = push(stack_operand, exp[pos] - 0x30);
        }

        pos++; /* 下一字符串位置*/
    }

    /* 取出剩下的运算子，并取出对应的运算元执行计算 */
    while (!empty(stack_operator)) {
        stack_operator = pop(stack_operator, &op);
        stack_operand = pop(stack_operand, &operand1);  // right
        stack_operand = pop(stack_operand, &operand2);  // left
        printf("    pop=%c,%d,%d, calc %d%c%d\n", op, operand1,
               operand2, operand2, op, operand1);
        /* 中间计算结果暂存入栈 */
        stack_operand = push(stack_operand, get_value(op, operand1, operand2));
    }
    /* 最终计算结果出栈 */
    stack_operand = pop(stack_operand, &result);
    printf("中序表达式[%s]的计算结果是 %d\n", exp, result);

    return 0;
}
