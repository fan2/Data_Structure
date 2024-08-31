/* ======================================== */
/*    程序实例: 10_6.c                       */
/*    快速排序法(Hoare partition scheme)     */
/* ======================================== */
// gcc -xc ../../utilities/safe_gets.c 10_6.C && ./a.out

#include <stdio.h>
#include <string.h>

#define MAX 20 /* 最大字符串长度       */

extern void safe_gets(char *str, int size);

/* ---------------------------------------- */
/*  快速排序法的递归处理                        */
/* ---------------------------------------- */
void q_sort(char *string, int left, int right) {
    /* 是否继续分割 */
    if (left < right) {
        printf("Hoare partition: string[%d:%d] begin: ", left, right);
        for (int k = left; k <= right; k++) /* 输出待处理字符串 */
            printf("%c", string[k]);
        printf("\n");

        int i = left;                  /* 分割的左(开)边界          */
        int j = right + 1;             /* 分割的右(开)边界          */
        char partition = string[left]; /* 取第一个元素作为分割基准元素 */
        printf("Hoare partition: base=%d, left=%d, right=%d\n", left, left + 1,
               right);
        char temp; /* 交换中转站临时值           */
        do {
            do { /* 从 left+1 开始往右找大 */
                i++;
            } while (string[i] < partition);

            do { /* 从 right 开始往左找小 */
                j--;
            } while (string[j] > partition);

            /* 两侧相对基准逆序（s[i]>=p>=s[j]），交换数据使得前后升序 */
            if (i < j) {
                printf("    swap([%d]:%c, [%d]:%c)\n", i, string[i], j,
                       string[j]);
                temp = string[i];
                string[i] = string[j];
                string[j] = temp;
            }
        } while (i < j);  // i<j: 两侧继续向中间扫描; i>=j: 结束本轮基准校序

        /*
         * while 结束循环条件：i>=j
         * s[j]<=p<=s[i]，(j,i)是左小右大的分界
         * 交换基准元素到分界中心（归位），完成本轮分治
         */
        if (left != j) {
            printf("    swap base [%d]:%c to rightmost min [%d]:%c\n", left,
                string[left], j, string[j]);
            temp = string[left];
            string[left] = string[j];
            string[j] = temp;
        } else {
            printf("    base [%d]:%c is already in the right place\n", left, string[left]);
        }

        printf("Hoare partition: string[%d:%d] end: ", left, right);
        for (int k = left; k <= right; k++) /* 输出处理后字符串 */
            printf("%c", string[k]);
        printf("\n");

        /* 递归快排基准左侧 */
        q_sort(string, left, j - 1);
        /* 递归快排基准右侧 */
        q_sort(string, j + 1, right);
    }
}

/* ---------------------------------------- */
/*  快速排序法                               */
/* ---------------------------------------- */
void quick_sort(char *string, int n) {
    q_sort(string, 0, n - 1);
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序             */
/* ---------------------------------------- */
// test cases: deacfbhg
int main(int argc, char *argv[]) {
    char string[MAX];
    int count;

    printf("输入要排序的字符串 ==> ");
    safe_gets(string, MAX);    /* 读取字符串     */
    count = strlen(string);    /* 计算字符串长度 */
    quick_sort(string, count); /* 快速排序法     */
    /* 输出排序后字符串 */
    printf("\n输出排序结果: [%s]\n", string);

    return 0;
}
