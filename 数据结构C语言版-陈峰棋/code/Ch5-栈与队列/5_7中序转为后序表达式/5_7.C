/* ======================================== */
/*    程式实例: 5_7.c                        */
/*    中序转为后序表达式                       */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack_node /* 栈的结构宣告      */
{
    int data;                /* 栈资料            */
    struct stack_node *next; /* 指向下一节点       */
};
typedef struct stack_node stack_list; /* 串列新型态      */
typedef stack_list *link;             /* 串列指标新型态   */

link stack_operator = NULL; /* 运算子栈指标     */

/* ---------------------------------------- */
/*  栈资料的存入                              */
/* ---------------------------------------- */
link push(link stack, int value) {
    link new_node; /* 新节点指标 */

    /* 配置节点记忆体 */
    new_node = (link)malloc(sizeof(stack_list));
    if (!new_node) {
        printf("记忆体配置失败! \n");
        return NULL; /* 存入失败 */
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
    link top; /* 指向栈顶端        */

    if (stack != NULL) {
        top = stack;         /* 指向栈顶端      */
        stack = stack->next; /* 栈指标指向下节点 */
        *value = top->data;  /* 取出资料        */
        free(top);           /* 释回节点记忆体   */
        return stack;        /* 传回栈指标      */
    } else
        *value = -1;

    return stack;
}

/* ---------------------------------------- */
/*  检查栈是否是空的                           */
/* ---------------------------------------- */
int empty(link stack) {
    if (stack == NULL) /* 是否是空            */
        return 1;      /* 空的                */
    else
        return 0; /* 不是空的            */
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
            return 1; /* 是运算子            */
        default:
            return 0; /* 不是运算子          */
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
/*  主程式: 输入中序表达式后, 转成后序.           */
/* ---------------------------------------- */
/*
1.
事实上前序和后序表达式的计算比起中序表达式的计算还要简单，如果能够将中序表达式转换成前序或后序表达式，
    就可以生成更容易处理的表达式，其实前序和后序表达式才是计算机最容易处理的表达式。
2.
中序表达式转换成后序表达式的方法只需将中序表达式计算的步骤稍加修饰，同时加入括号处理的功能。
    两个表达式的操作数排列顺序完全相同，只有运算符的排列不同，所以中序表达式在转换时不需要操作数栈，
    只需在导入任何操作数后马上输出。而运算符的处理和中序表达式的计算相同。
3.
括号的处理是在遇到左括号时，将之存入运算符栈，等到导入的是右括号时，才从运算符栈取出运算符后输出，
    重复上述操作直到再度遇到左括号。
*/
/* test cases:
    | infix         | postfix     | expr          | result      |
    |---------------|-------------|---------------|-------------|
 1. | a+b           | ab+         | 4+8           | 48+         |
 2. | a+b*c         | abc*+       | 4+8*3         | 483*+       |
 3. | a*b-c         | ab*c-       | 4*8-3         | 48*3-       |
 4. | a+b*c-d       | abc*+d-     | 4+8*3-7       | 483*+7-     |
 5. | a*b-c*d       | ab*cd*-     | 4*8-3*7       | 48*37*-     |
 6. | a*(b+c)       | abc+*       | 4*(8+3)       | 483+*       |
 7. | (a+b)/c       | ab+c/       | (4+8)/3       | 48+3/       |
 8. | (a+b)*(c-d)   | ab+cd-/     | (4+8)*(7-3)   | 48+73-*     |
 9. | a+b*(c-d)     | abcd-*+     | 4+8*(7-3)     | 4873-*+     |
 A. | a*b+c*(d-e)/f | ab*cde-*f/+ | 4*8+9*(7-5)/3 | 48*975-*3/+ |
 B. | a*b+c*(d*e-f)/g   | ab*cde*f-*g/+ |
    | 4*8+9*(7*2-5)/3   | 48*972*5-*3/+ |
 C. | a*b+c*(d-e*f)/g   | ab*cdef*-*g/+ |
    | 4*8+9*(7-1*2)/3   | 48*9712*-*3/+ |
 D. | a*b+c*(d-(e+f))/g | ab*cdef+-*g/+ |
    | 4*8+5*(9-(1+2))/3 | 48*5912+-*3/+ |
 */
int main(int argc, char *argv[]) {
    char infix[BUFSIZ / 10];  /* 中序表达式字符串      */
    char result[BUFSIZ / 10]; /* 结果表达式字符串      */
    int op = 0;               /* 运算子变数          */
    int pos = 0;              /* 目前表达式位置       */
    int rpos = 0;             /* 结果表达式位置       */

    printf("请输入中序表达式 ==> ");
    safe_gets(infix, BUFSIZ / 10); /* 读取表达式 */
    while (infix[pos] != '\0' && infix[pos] != '\n') {
        if (isoperator(infix[pos])) /* 是不是运算子 */
        {
            // 左括号强插，优先级最低，先搁置从前，入栈括号内的计算表达式
            if (empty(stack_operator) || infix[pos] == '(') {
                /* 运算子入栈 */
                printf("    [1]push operator='%c'\n", infix[pos]);
                stack_operator = push(stack_operator, infix[pos]);
            } else {
                if (infix[pos] == ')') /* 遇到闭合右括号 */
                {
                    puts("    deal operator=')'");
                    /* 取出运算子直到'(' */
                    while (stack_operator->data != '(') {
                        stack_operator = pop(stack_operator, &op);
                        /* 将括号内的运算子存入后序表达式 */
                        result[rpos++] = op;
                        printf("      pop operator='%c'\n", op);
                    }
                    /* 弹出左括号 */
                    stack_operator = pop(stack_operator, &op);
                    puts("      pop operator='('");
                } else  // 普通运算子
                {
                    // 比较当前运算子与栈顶(中)运算子优先权，弹出已入栈的高优先级运算子
                    // 括号内的表达式可能也存在优先级问题，此处一并处理
                    while (!empty(stack_operator) &&
                           (priority(infix[pos]) <=
                            priority(stack_operator->data))) {
                        /* 取出运算子 */
                        stack_operator = pop(stack_operator, &op);
                        /* 存入结果表达式 */
                        result[rpos++] = op;
                        printf("    pop hipri operator='%c'\n", op);
                    }
                    /* 处理完高优先级后，该运算子入栈 */
                    printf("    [2]push operator='%c'\n", infix[pos]);
                    stack_operator = push(stack_operator, infix[pos]);
                }
            }
        } else {
            /* 运算元依序存入结果表达式 */
            printf("    push operand='%c'\n", infix[pos]);
            result[rpos++] = infix[pos];
        }
        pos++;
    }

    /* 取出剩下的运算子 */
    while (!empty(stack_operator)) {
        stack_operator = pop(stack_operator, &op); /* 取出运算子    */
        result[rpos++] = op;                       /* 存入结果表达式 */
        printf("    pop operator='%c'\n", op);
    }
    result[rpos] = '\0'; /* 设定字符串结束 */
    printf("中序表达式[%s]转换成后序表达式是[%s]\n", infix, result);

    return 0;
}
