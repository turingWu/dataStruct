#pragma once
#include "ListNode.h"

template<typename T>
class List
{
private:
	int _size; //规模
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init(); //列表创建初始化 pass
	int clear(); //清除所有节点 
	void copyNodes(Posi(T), int);//复制列表中自位置p起的n项 pass
	void merge(Posi(T)&, int, List<T>&, Posi(T), int); //合并
	void mergeSort(Posi(T), int);  //对从p开始连续的n个节点进行归并排序
	void selectionSort(Posi(T), int);//对p开始的n个连续的节点进行选择排序
	void insertionSort(Posi(T), int); //对从p开始的N个节点插入排序
public:

	List()
	{
		init();
	}//默认
	List(List<T> const& L);//复制l
	List(List<T> const& L, int r, int n);//复制l中r到n
	List(Posi(T) p, int n); 
	~List()
	{
	}//清理所有节点

	//只读接口
	int size() const 
	{
		return _size;
	}
	bool empty() const
	{
		return _size <= 0;
	}
	T& operator[] (int r) const;
	Posi(T) first() const
	{
		return header->next;
	}
	Posi(T) last() const
	{
		return trailer->pred;
	}
	bool valid(Posi(T) p)
	{
		return p && (trailer != p) && (p != header);
	}//判断节点合法
	int isDisordered() const;
	Posi(T) findInPred(T const& e, int n, Posi(T) p)const; //pass
	Posi(T) find(T const& e)const //pass
	{
		return findInPred(e, _size, trailer); 
	}
	Posi(T) search(T const& e, int n, Posi(T)) const; //有序查找
	Posi(T) search(T const& e) const
	{
		return search(e, _size, trailer);
	}
	Posi(T) selectMax(Posi(T) p, int n) const;//在p和n-1中找max
	Posi(T) selectMax() const
	{
		return selectMax(header->pred, _size);
	}
	//可写接口
	Posi(T) insertAsFirst(T const& e); //pass
	Posi(T) insertAsLast(T const& e);  //pass
	Posi(T) insertAsPre(Posi(T) p, T const& e); //pass
	Posi(T) insertAsNext(Posi(T) p, T const& e); //pass
	T remove(Posi(T) p);
	void merge(List<T>& l)
	{
		merge(first(), size, l, l.first(), l._size);
	}
	void sort(Posi(T) p, int n);
	void sort()
	{
		sort(first(), _size);
	}
	int deduplicate();
	int uniquify();//有序去重
	void reverse();
	void traverse(void(*) (T&));
	template <typename VST>
	void traverse(VST&);
};

template<typename T>
inline void List<T>::init()
{
	_size = 0;
	header = new ListNode < T > ;
	trailer = new ListNode < T > ;
	header->next = trailer;
	trailer->pred = header;
}
template<typename T>
inline void List<T>::copyNodes(Posi(T) p, int n)
{
	init();
	while (n-- > 0)
	{
		insertAsLast(p->data);
		if (p->next->next == nullptr)//防止下标越界
		{
			return;
		}
		p = p->next;
		
	}
}
template<typename T>
inline List<T>::List(List<T> const& L,int r,int n)
{
	//copyNodes(L[r], n); 原代码有错。
	Posi(T) p = L.first();
	while (r-->0)
	{
		p = p->next;
	}
	copyNodes(p, n);
}
template<typename T>
inline List<T>::List(List<T> const& L)
{
	copyNodes(L.first(), L._size);
}
template<typename T>
inline T& List<T>::operator[](int n)const
{
	Posi(T) node = first();
	while (n-->0)
	{
		node = node->next;
	}
	return node->data;
}
template<typename T>
inline Posi(T) List<T>::findInPred(T const& e, int n, Posi(T) p) const
{
	while (n-- > 0)
	{
		if (e == ((p->pred)->data))
		{
			return p;
		}
	}
	return NULL;
}
template<typename T>
inline Posi(T) List<T>::insertAsFirst(T  const& e)
{
	_size++;
	return header->insertAsNext(e);
}
template<typename T>
inline Posi(T) List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}
template<typename T> //这里应该有点隐患，如果传入节点不是当前this的list对象的话，那么_size加的就是不对的对象                    
inline Posi(T) List<T>::insertAsPre(Posi(T) p,T const& e)
{
	_size++;
	return p->insertAsPred(e);
}
template<typename T>
inline Posi(T) List<T>::insertAsNext(Posi(T) p, T const& e)
{
	_size++;
	return p->insertAsNext(e);
}