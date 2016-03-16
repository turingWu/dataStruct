#include <iostream>
#include "MyVector.h"
#include "Stack.h"
using namespace std;


int main()
{
    int a[] = {1,2,3};
    MyVector<int> b = MyVector<int>(a,0,3);

   //d未初始化，执行函数D.getElement()时导致程序终止
    return 0;
}
