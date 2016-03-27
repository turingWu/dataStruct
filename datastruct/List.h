#pragma once
#include "ListNode.h"
template<template T>
class List
{
private:
	int _size; //规模
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init(); //列表创建初始化
	int clear(); //清除所有节点
	void copyNodes(Posi(T), int);//复制列表中自位置p起的n项
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
	T& operator[] (int r) const
	{
		
	}
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
	int isDisordered const;
	Posi(T) find(T const& e, int n, Posi(T))const;
	Posi(T) find(T const& e)const
	{
		return find(e, _size, trailer); 
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
	Posi(T) insertAsFirst(T const& e);
	Posi(T) insertAsLast(T const& e);
	Posi(T) insertAsPre(Posi(T) p, T const& e);
	Posi(T) insertAsNext(Posi(T) p, T const& e);
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

