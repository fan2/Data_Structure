/* ======================================== */
/*    程序实例: 10_2a.c                      */
/*    在字符串中查找最大字符                    */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_2A.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度           */

extern void safe_gets(char *str, int size);

/* ---------------------------------------------------------------*/
/*  找最大的字符                                                    */
/*  冒泡排序的第一遍，把右边小的往左边推，将最大数推到最右                  */
/* -------------------------------------------------------------- */
void findchar(char *string, int count) {
    int i;
    char temp;

    for (i = 0; i < count - 1; i++)
        if (string[i] > string[i + 1]) {  // 逆序交换
            printf("swap [%d]:%c<=>[%d]:%c, ", i, string[i], i + 1,
                   string[i + 1]);
            temp = string[i + 1];
            string[i + 1] = string[i];
            string[i] = temp;
            printf("string=%s\n", string);
        }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串来找最大字符               */
/* ---------------------------------------- */
// test cases: kljoab
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要查找的字符串 ==> ");
    safe_gets(string, MAX);  /* 读取字符串              */
    count = strlen(string);  /* 计算字符串长度           */
    findchar(string, count); /* 查找                   */
    /* 输出处理后字符串 */
    printf("处理后字符串: [%s]\n", string);
    /* 输出最大的字符 */
    printf("最大的字符是:%c\n", string[count - 1]);

    return 0;
}
