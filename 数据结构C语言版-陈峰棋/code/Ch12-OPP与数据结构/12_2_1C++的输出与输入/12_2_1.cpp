/* ======================================== */
/*    程序实例: 12_2_1.cpp                   */
/*    C++的输出与输入                        */
/* ======================================== */
#include <iostream>
#include <cstring>

using namespace std;

#define MAX 20 /* 最大字符串长度           */

/* ---------------------------------------- */
/*  主程式: 输入与输出数据                      */
/* ---------------------------------------- */
int main(int argc, char *argv[])
{
    char string[MAX]; /* 字符串数组               */
    int count;        /* 字符串长度               */

    cout << "请输入字符串内容: ";     /* 输出字符串              */
    cin >> string;                    /* 输入字符串              */
    count = strlen(string);           /* 计算字符串长度           */
    cout << "字符串内容:[" << string; /* 输出字符串的内容         */
    cout << "]长度为:" << count << "\n";

    return 0;
}
