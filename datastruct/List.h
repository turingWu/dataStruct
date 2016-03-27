#pragma once
#include "ListNode.h"
template<template T>
class List
{
private:
	int _size; //��ģ
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init(); //�б�����ʼ��
	int clear(); //������нڵ�
	void copyNodes(Posi(T), int);//�����б�����λ��p���n��
	void merge(Posi(T)&, int, List<T>&, Posi(T), int); //�ϲ�
	void mergeSort(Posi(T), int);  //�Դ�p��ʼ������n���ڵ���й鲢����
	void selectionSort(Posi(T), int);//��p��ʼ��n�������Ľڵ����ѡ������
	void insertionSort(Posi(T), int); //�Դ�p��ʼ��N���ڵ��������
public:

	List()
	{
		init();
	}//Ĭ��
	List(List<T> const& L);//����l
	List(List<T> const& L, int r, int n);//����l��r��n
	List(Posi(T) p, int n); 
	~List()
	{
	}//�������нڵ�

	//ֻ���ӿ�
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
	}//�жϽڵ�Ϸ�
	int isDisordered const;
	Posi(T) find(T const& e, int n, Posi(T))const;
	Posi(T) find(T const& e)const
	{
		return find(e, _size, trailer); 
	}
	Posi(T) search(T const& e, int n, Posi(T)) const; //�������
	Posi(T) search(T const& e) const
	{
		return search(e, _size, trailer);
	}
	Posi(T) selectMax(Posi(T) p, int n) const;//��p��n-1����max
	Posi(T) selectMax() const
	{
		return selectMax(header->pred, _size);
	}
	//��д�ӿ�
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
	int uniquify();//����ȥ��
	void reverse();
	void traverse(void(*) (T&));
	template <typename VST>
	void traverse(VST&);
};

