/* ======================================== */
/*    程序实例: 10_2b.c                    */
/*    冒泡排序法                            */
/* ======================================== */
// 两两交换冒泡

#include <stdlib.h>
#define MAX  20                   /* 最大字符串长度           */

/* ---------------------------------------- */
/*  冒泡排序法                              */
/* ---------------------------------------- */
void bubble(char *string,int count)
{
   int i,j;
   char temp;

   for ( j = count; j > 1; j-- )  /* 第一层循环：扫描个数 */
   {
      for ( i = 0; i < j - 1; i++ )     /* 第二层循环：扫描，最后一趟string[0+1],string[0] */
         if ( string[i+1] < string[i] ) /*比较相邻的数组元素*/
         {
            temp = string[i+1];         /* 交换两字符      */
            string[i+1] = string[i];
            string[i] = temp;
         }

      printf("输出结果: [%s]\n",string); /* 输出交换后字符串  */
   }
}

/* ---------------------------------------- */
/*  主程序: 输入字符串后将字符串排序           */
/* ---------------------------------------- */
int main()
{
   char string[MAX];              /* 字符串数组               */
   int count;                     /* 字符串长度               */

   printf("输入要排序的字符串 ==> ");
   gets(string);                  /* 读取字符串               */
   count = strlen(string);        /* 计算字符串长度           */
   bubble(string,count);          /* 冒泡排序法             */
   /* 输出排序后字符串 */
   printf("\n输出排序结果: [%s]\n",string);

   return 0;
}


//////////////////////////////////////////////////////////////////////////
/*
void bubble(char *string, int count)
{
    int i, // 内层循环索引
        j; // 外层循环次数

    int temp;

    for (j=count-1; j>=1; j--)
        for (i=0; i<j; i++)
        {
            if (string[i+1] < string[i])
            {
                temp = string[i+1];
                string[i+1] = string[i];
                string[i] = temp;
            }
        }
}
*/