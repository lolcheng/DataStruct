#include <iostream>
#include "inc/DataStruct.h"

using namespace std;
int main()
{
    SqStack<int, 100> *p = new SqStack<int, 100>(); // 顺序栈类
    int d, r, res;
    string str = "";
    cout << "Please input d and r." << endl;
    cin >> d >> r;
    while (d != 0)
    {
        p->Push(d % r); // 入栈函数
        d = d / r;
    }
    while (p->Pop(res)) // 出栈函数，出栈成功返回true
    {
        string ResString = "0123456789ABCDEF";
        str = str + ResString[res]; // 存储结果
    }
    cout << str << endl;
}