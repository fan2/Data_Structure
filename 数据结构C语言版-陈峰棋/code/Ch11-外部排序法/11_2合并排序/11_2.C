/* ======================================== */
/*    程式实例: 11_2.c                       */
/*    合并排序                               */
/* ======================================== */
#include <stdio.h>

#define LEN 4 /* 最大元素个数         */

/* ---------------------------------------- */
/*  合并排序                                 */
/* ---------------------------------------- */
void merge(FILE *merge, FILE *sort1, FILE *sort2, int len)
{
    int s1, s2; /* 资料计数             */
    char c, c1, c2;

    c1 = getc(sort1); /* 读取第一个档案       */
    c2 = getc(sort2); /* 读取第二个档案       */
    s1 = s2 = 0;      /* 设定计数初值         */
    while (1)
    {
        if (c1 < c2) /* 比较两个值           */
        {
            /* 第一个档案小, 存入主档 */
            putc(c1, merge);
            s1++;                 /* 计数加一            */
            if (s1 < len)         /* 是否未读完          */
                c1 = getc(sort1); /* 读取第一个档案       */
            else
                break; /* 跳出回路             */
        }
        else
        {
            /* 第二个档案小, 存入主档 */
            putc(c2, merge);
            s2++;                 /* 计数加一            */
            if (s2 < len)         /* 是否未读完          */
                c2 = getc(sort2); /* 读取第一个档案       */
            else
                break; /* 跳出回路             */
        }
    }
    /* 第一个档案是否是最後一笔 */
    if (s1 < len) /* 处理最後一笔         */
    {
        putc(c1, merge); /* 存入主档             */
        s1++;            /* 计数加一             */
    }
    /* 第二个档案是否是最後一笔 */
    if (s2 < len) /* 处理最後一笔         */
    {
        putc(c2, merge); /* 存入主档             */
        s2++;            /* 计数加一             */
    }
    /* 第一个档案 */
    while (s1 < len) /* 取出剩下的资料       */
    {
        c = getc(sort1); /* 读取第一个档案       */
        putc(c, merge);  /* 存入主档            */
        s1++;            /* 计数加一            */
    }
    /* 第二个档案 */
    while (s2 < len) /* 取出剩下的资料       */
    {
        c = getc(sort2); /* 读取第二个档案       */
        putc(c, merge);  /* 存入主档            */
        s2++;            /* 计数加一            */
    }
}

/* ---------------------------------------- */
/*  主程式: 读取两个档案内容, 接着用合并排        */
/*  序法来排序.                               */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    FILE *fp;  /* 主档指标            */
    FILE *fp1; /* 第一资料档案指标     */
    FILE *fp2; /* 第二资料档案指标     */

    fp = fopen("result.txt", "r+"); /* 开启主档             */
    if (fp == NULL)
        printf("主档开启错误! \n");
    else
        fp1 = fopen("sort1.txt", "r+"); /* 开启第一资料档案 */
    if (fp1 == NULL)
        printf("第一资料档开启错误! \n");
    else
    {
        fp2 = fopen("sort2.txt", "r+"); /*开启第二资料档案*/
        if (fp2 == NULL)
            printf("第二资料档开启错误! \n");
        else
        {
            printf("正在处理数据，请稍等. . . \n");
            merge(fp, fp1, fp2, LEN); /* 合并排序法     */
            printf("数据处理完成! \n");
            fclose(fp); /* 关档                 */
            fclose(fp1);
            fclose(fp2);
        }
    }

    return 0;
}
