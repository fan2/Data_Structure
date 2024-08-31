/* ======================================== */
/*    程序实例: 10_4.c                       */
/*    插入排序法                             */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_4.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度          */

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  插入排序法                                */
/* ---------------------------------------- */
void insert(char *string, int count) {
    int i;       // 待插席位索引
    char bench;  // 待插席位字符
    int j;       // 已就序前缀尾元素索引

    for (i = 1; i < count; i++) {
        bench = string[i]; /* backup as pivot */
        printf("bench = [%d]:%c\n", i, bench);

        // bench 与有序前缀从后向前比较
        while (j >= 0 && bench < string[j]) {
            string[j + 1] = string[j];  // 向后挪动
            j--;
        }

        // for (j = i - 1; j >= 0; j--) {
        //     if (bench < string[j]) {
        //         string[j + 1] = string[j];  // 向后挪动
        //     } else {
        //         // bench >= string[j]
        //         break;
        //     }
        // }

        if (j + 1 != i) {
            string[j + 1] = bench;  // 插入合适位置
            printf("    insert pos = %d, result = %s\n", j + 1, string);
        }  // 已经就位，无需插入
    }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序             */
/* ---------------------------------------- */
// test cases: lkjoab
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要排序的字符串 ==> ");
    safe_gets(string, MAX); /* 读取字符串             */
    count = strlen(string); /* 计算字符串长度          */
    insert(string, count);  /* 插入排序法             */
    /* 输出排序后字符串 */
    printf("\n输出排序结果: [%s]\n", string);

    return 0;
}
