/* ======================================== */
/*    程式实例: 3_1_1a.c                  */
/*    使用malloc()来配置浮点数记忆体        */
/* ======================================== */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float *fp; /* 浮点指标宣告     */

    fp = (float *)malloc(sizeof(float)); /* 配置浮点数记忆体 */

    if (!fp) /* 检查指标         */
    {
        printf("内存分配失败! \n");
        exit(1);
    }

    *fp = 3.1415926; /* 设定变数值       */

    printf("圆周率: %10.8f \n", *fp); /* 列出结果         */

    return 0;
}
