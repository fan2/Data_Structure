/* ======================================== */
/*    程式实例: 5_7_2.c                      */
/*    中序转前序: (l,o,r) -> (o,l,r)         */
/* ======================================== */
/*
1.
事实上前序和后序表达式的计算比起中序表达式的计算还要简单，如果能够将中序表达式转换成前序或后序表达式，
    就可以生成更容易处理的表达式，其实前序和后序表达式才是计算机最容易处理的表达式。
2.
中序表达式转换成前序表达式的方法只需将中序表达式计算的步骤稍加修饰，同时加入括号处理的功能。
    两个表达式的操作数排列顺序完全相同，运算符的排列不同（高优先级最先前置在右），需要借助两个辅助栈，
    中间表达式从后往前拼接。而运算符的处理和中序表达式的计算相同。
3.
括号的处理是在遇到左括号时，将之存入运算符栈，等到导入的是右括号时，才从运算符栈取出运算符后输出，
    重复上述操作直到再度遇到左括号。
*/
/*
 * (a+b)*(c-d):
 * 1. +ab
 * 2. -cd
 * 3. *+ab-cd
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXP_SIZE 20 /* 表达式支持最长 20 个字符 */

struct stack_node /* 栈的结构宣告      */
{
    char data[EXP_SIZE]; /* 栈资料（运算子或远算元或中间表达式）*/
    struct stack_node *next; /* 指向下一节点 */
};
typedef struct stack_node stack_list; /* 串列新型态      */
typedef stack_list *link;             /* 串列指标新型态   */

link stack_operator = NULL; /* 运算子栈指标     */
link stack_operand = NULL;  /* 运算元栈指标     */

/* ---------------------------------------- */
/*  栈资料的存入（运算子或远算元或中间表达式）      */
/* ---------------------------------------- */
link push(link stack, char value[]) {
    if (strlen(value) == 0) {
        printf("压入的字符串为空! \n");
        return NULL; /* 存入失败 */
    }

    /* 配置节点记忆体 */
    link new_node = (link)malloc(sizeof(stack_list));
    if (!new_node) {
        printf("记忆体配置失败! \n");
        return NULL; /* 存入失败 */
    }
    strcpy(new_node->data, value); /* 建立节点内容    */
    new_node->next = stack;        /* 新节点指向原开始 */
    stack = new_node;              /* 新节点成为栈开始 */

    return stack;
}

/* ---------------------------------------- */
/*  栈资料的取出（运算子或远算元或中间表达式）      */
/* ---------------------------------------- */
link pop(link stack, char *value) {
    link top; /* 指向栈顶端        */

    if (stack != NULL) {
        top = stack;              /* 指向栈顶端      */
        stack = stack->next;      /* 栈指标指向下节点 */
        strcpy(value, top->data); /* 取出资料        */
        free(top);                /* 释回节点记忆体   */
        return stack;             /* 传回栈指标      */
    } else
        *value = 0;  // 开头置空

    return stack;
}

/* ---------------------------------------- */
/*  检查栈是否是空的                           */
/* ---------------------------------------- */
int empty(link stack) {
    if (stack == NULL) /* 是否是空            */
        return 1;      /* 空的               */
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
/*  主程式: 输入中序表达式后, 转成前序.           */
/* ---------------------------------------- */
// test cases:
//     | infix             | prefix        | expr              | result        |
//     |-------------------|---------------|-------------------|---------------|
//  1. | a+b               | +ab           | 4+8               | +48           |
//  2. | a+b*c             | +a*bc         | 4+8*3             | +4*83         |
//  3. | a*b-c             | -*abc         | 4*8-3             | -*483         |
//  4. | a+b*c-d           | -+a*bcd       | 4+8*3-7           | -+4*837       |
//  5. | a*b-c*d           | -*ab*cd       | 4*8-3*7           | -*48*37       |
//  6. | a*(b+c)           | *a+bc         | 4*(8+3)           | *4+83         |
//  7. | (a+b)/c           | /+abc         | (4+8)/3           | /+483         |
//  8. | (a+b)*(c-d)       | *+ab-cd       | (4+8)*(7-3)       | *+48-73       |
//  9. | a+b*(c-d)         | +a*b-cd       | 4+8*(7-3)         | +4*8-73       |
//  A. | a*b+c*(d-e)/f     | +*ab/*c-def   | 4*8+9*(7-5)/3     | +*48/*9-753   |
//  B. | a*b+c*(d*e-f)/g   | +*ab/*c-*defg | 4*8+9*(7*2-5)/3   | +*48/*9-*7253 |
//  C. | a*b+c*(d-e*f)/g   | +*ab/*c-d*efg | 4*8+9*(7-1*2)/3   | +*48/*9-7*123 |
//  D. | a*b+c*(d-(e+f))/g | +*ab/*c-d+efg | 4*8+5*(9-(1+2))/3 | +*48/*5-9+123 |
int main(int argc, char *argv[]) {
    char infix[EXP_SIZE];     /* 中序表达式字符串         */
    int pos = 0;              /* 目前表达式解析位置       */
    char exp[EXP_SIZE] = {0}; /* intermediate, result  */
    char op[2] = {0};         /* operator/operand char */
    char op1[EXP_SIZE] = {0}; /* pop right operand     */
    char op2[EXP_SIZE] = {0}; /* pop left operand      */

    printf("请输入中序表达式 ==> ");
    safe_gets(infix, EXP_SIZE); /* 读取表达式 */
    while (infix[pos] != '\0' && infix[pos] != '\n') {
        if (isoperator(infix[pos])) /* 是不是运算子 */
        {
            // 左括号强插，先搁置已入栈运算子
            if (empty(stack_operator) || infix[pos] == '(') {
                /* 运算子入栈 */
                printf("    [1]push operator='%c'\n", infix[pos]);
                op[0] = infix[pos];
                stack_operator = push(stack_operator, op);
            } else {
                if (infix[pos] == ')') // 先拼接括号内的子表达式
                {
                    puts("    deal operator=')'");
                    /* 取出运算子直到'(' */
                    while (strcmp(stack_operator->data, "(") != 0) {
                        stack_operator = pop(stack_operator, op);
                        stack_operand = pop(stack_operand, op1);  // right
                        stack_operand = pop(stack_operand, op2);  // left
                        exp[0] = 0;                               // reset
                        /* 拼接中间表达式 */
                        strcat(exp, op);
                        strcat(exp, op2);
                        strcat(exp, op1);
                        /* 中间表达式暂存入栈 */
                        stack_operand = push(stack_operand, exp);
                        printf("      intermediate = %s\n", exp);
                    }
                    /* 弹出左括号 */
                    stack_operator = pop(stack_operator, op);
                    puts("      pop operator='('");
                } else  // 普通运算子
                {
                    // 待闭合左括号优先级最低，入栈括号内的表达式
                    // 括号内的表达式可能也存在优先级问题，此处一并处理
                    // 比较当前运算子与栈顶(中)运算子优先权，弹出已入栈的高优先级运算子
                    while (!empty(stack_operator) &&
                           (priority(infix[pos]) <=
                            priority(stack_operator->data[0]))) {
                        /* 执行高优先级计算(拼接表达式) */
                        stack_operator = pop(stack_operator, op);
                        stack_operand = pop(stack_operand, op1);  // right
                        stack_operand = pop(stack_operand, op2);  // left
                        exp[0] = 0;                               // reset
                        /* 拼接中间表达式 */
                        strcat(exp, op);
                        strcat(exp, op2);
                        strcat(exp, op1);
                        /* 中间表达式暂存入栈 */
                        stack_operand = push(stack_operand, exp);
                        printf("    pop hipri exp=%s\n", exp);
                    }
                    /* 处理完高优先级后，该运算子入栈 */
                    printf("    [2]push operator='%c'\n", infix[pos]);
                    op[0] = infix[pos];
                    stack_operator = push(stack_operator, op);
                }
            }
        } else {
            /* 运算元依序存入结果表达式 */
            printf("    push operand='%c'\n", infix[pos]);
            op[0] = infix[pos];  // 单运算元(Single ASCII Char)
            stack_operand = push(stack_operand, op);
        }
        pos++;
    }

    /* 取出剩下的运算子，并取出对应的运算元执行计算(拼接表达式) */
    while (!empty(stack_operator)) {
        stack_operator = pop(stack_operator, op);
        stack_operand = pop(stack_operand, op1);  // right
        stack_operand = pop(stack_operand, op2);  // left
        exp[0] = 0;                               // reset
        /* 拼接中间表达式 */
        strcat(exp, op);
        strcat(exp, op2);
        strcat(exp, op1);
        /* 中间表达式暂存入栈 */
        stack_operand = push(stack_operand, exp);
        printf("    exp=%s\n", exp);
    }
    /* 最终拼接完成的表达式出栈 */
    stack_operand = pop(stack_operand, exp);
    printf("中序表达式[%s]转换成前序表达式是[%s]\n", infix, exp);

    return 0;
}
