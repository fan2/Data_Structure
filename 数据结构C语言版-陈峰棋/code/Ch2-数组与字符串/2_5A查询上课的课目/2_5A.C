/* ======================================== */
/*    程式实例: 2_5a.c                      */
/*    查询上课的课目,其中课程以代码表示.    */
/*       0 表示没课                         */
/*       1 表示计算机概论                   */
/*       2 表示离散数学                     */
/*       3 表示资料结构                     */
/*       4 表示资料库概论                   */
/*       5 表示上机实习;                    */

/*       二维数组表示矩阵，注意行和列的实际意义          */

/* ======================================== */
#include <stdio.h>

int main(int argc, char *argv[])
{
    int course[6][5] = {0, 2, 0, 2, 0, /* 课程定义       */
                        1, 4, 1, 4, 1,
                        5, 0, 5, 0, 5,
                        0, 0, 0, 0, 0,
                        3, 0, 3, 0, 3,
                        0, 0, 0, 0, 0};
    int week;     /* 星期资料变数   */
    // int class;    /* 第几节课的变数 */
    // int class_no; /* 课程代码变数   */
    int cclass;    /* 第几节课的变数 */
    int cclass_no; /* 课程代码变数   */

    printf("请输入星期(1 到 5). ==> ");
    scanf("%d", &week); /* 读取星期资料   */
    printf("请输入第几节课(1 到 6). ==> ");
    scanf("%d", &cclass);                    /* 读取第几节课   */
    cclass_no = course[cclass - 1][week - 1]; /* 课程查询       */
    switch (cclass_no)                       /* 印出课程名称   */
    {
    case 0:
        printf("这节没课\n");
        break;
    case 1:
        printf("计算机概论\n");
        break;
    case 2:
        printf("离散数学\n");
        break;
    case 3:
        printf("数据结构\n");
        break;
    case 4:
        printf("数据库概论\n");
        break;
    case 5:
        printf("上机实习\n");
        break;
    }

    return 0;
}
