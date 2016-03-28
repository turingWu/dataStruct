#pragma once
#include "ListNode.h"

template<typename T>
class List
{
private:
	int _size; //��ģ
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init(); //�б�����ʼ�� pass
	int clear(); //������нڵ� 
	void copyNodes(Posi(T), int);//�����б�����λ��p���n�� pass
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
	}//�жϽڵ�Ϸ�
	int isDisordered() const;
	Posi(T) findInPred(T const& e, int n, Posi(T) p)const; //pass
	Posi(T) find(T const& e)const //pass
	{
		return findInPred(e, _size, trailer); 
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
	int uniquify();//����ȥ��
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
		if (p->next->next == nullptr)//��ֹ�±�Խ��
		{
			return;
		}
		p = p->next;
		
	}
}
template<typename T>
inline List<T>::List(List<T> const& L,int r,int n)
{
	//copyNodes(L[r], n); ԭ�����д�
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
template<typename T> //����Ӧ���е��������������ڵ㲻�ǵ�ǰthis��list����Ļ�����ô_size�ӵľ��ǲ��ԵĶ���                    
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