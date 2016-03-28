// datastruct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myVector.h"
#include "ListNode.h"
#include <iostream>
#include "List.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	/*listnode<int> a;
	posi(int) b = a.insertaspred(2);*/
	/*cout << b->data << endl;
	cout << a(2, 3) << endl;
	ListNode<int> a;
	if (a.next == nullptr)
	{
		cout << "null" << endl;
	}
	return 0;
	*/
	List<int> a;
	a.insertAsFirst(0);
	a.insertAsFirst(1);
	a.insertAsFirst(2);
	cout << a.size() << endl;
	List<int> b = List<int>(a, 1, 3);
	cout << b[0] << endl;
	cout << b.size() << endl;
	return 0;
}

