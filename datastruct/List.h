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
	int clear(); //清除所有节点  pass
	void copyNodes(Posi(T), int);//复制列表中自位置p起的n项 pass
	Posi(T) merge(Posi(T), int, Posi(T), int); //合并
	void mergeSort(Posi(T), int);  //对从p开始连续的n个节点进行归并排序
	void selectionSort(Posi(T), int);//对p开始的n个连续的节点进行选择排序pass
	void insertionSort(Posi(T), int); //对从p开始的N个节点插入排序pass
public:

	List()
	{
		init();
	}//默认
	List(List<T> const& L);//复制lpass
	List(List<T> const& L, int r, int n);//复制l中r到n pass
	List(Posi(T) p, int n); //pass
	~List()
	{
		clear();
		delete header;
		delete trailer;
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
	T& operator[] (int r) const; //pass
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
	bool isDisordered() const;
	Posi(T) findInPred(T const& e, int n, Posi(T) p)const; //pass
	Posi(T) find(T const& e)const //pass
	{
		return findInPred(e, _size, trailer); 
	}
	Posi(T) search(T const& e, int n, Posi(T)) const; //有序查找 pass
	Posi(T) search(T const& e) const
	{
		return search(e, _size, trailer);
	}
	Posi(T) selectMax(Posi(T) p, int n) const;//在p和n-1中找max pass

	Posi(T) selectMax() const //pass
	{
		return selectMax(header->next, _size);
	}
	//可写接口
	Posi(T) insertAsFirst(T const& e); //pass
	Posi(T) insertAsLast(T const& e);  //pass
	Posi(T) insertAsPre(Posi(T) p, T const& e); //pass
	Posi(T) insertAsNext(Posi(T) p, T const& e); //pass
	Posi(T) insertAsPre(Posi(T) p, Posi(T) q); //pass
	Posi(T) insertAsNext(Posi(T) p, Posi(T) q); //pass
	T remove(Posi(T) p); //pass
	void merge(List<T>& l)
	{
		merge(first(), size, l, l.first(), l._size);
	}
	void sort(Posi(T) p, int n);
	void sort()
	{
		sort(first(), _size);
	}
	int deduplicate(); //pass
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
		if (e == ((p=p->pred)->data))
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
template<typename T>
inline T List<T>::remove(Posi(T) p)
{
	p->pred->next = p->next;
	p->next->pred = p->pred;
	T a = p->data;
	delete p;
	_size--;
	return a;
}
template<typename T>
inline int List<T>::clear()
{
	int oldSize = _size;
	while (_size>0)
	{
		remove(header->next);
	}
	return oldSize;
}
template<typename T>
inline bool List<T>::isDisordered() const
{
	Posi(T) p = header->next;
	while (p->next->next!=nullptr)
	{
		if ((p->data)>(p->next->data))
		{
			return false;
		}
		p = p->next;
	}
	return true;
}
template<typename T>
int List<T>::deduplicate()
{
	int oldSize = _size;
	Posi(T) p = header->next;
	int k = 0;
	while (trailer!=p)
	{
		Posi(T) a = findInPred(p->data, k, p);
		p = p->next;
		if (a!=NULL)
		{
			remove(a);
		}
		else
		{
			k++;
		}
		
	}
	return oldSize - _size;
}
template<typename T>
Posi(T) List<T>::selectMax(Posi(T) p, int n) const
{
	Posi(T) node = p;
	while (n-->0)
	{
		if ((node->next)==trailer)
		{
			return p;
		}
		if ((node->next->data)>(p->data))
		{
			p = node->next;
		}
		node = node->next;
	}
	return p;
}

template<typename T> //重写接口，以至于可以插入已有节点，同一个链表的节点
Posi(T) List<T>::insertAsPre(Posi(T) p, Posi(T) n)
{
	p->next->pred = p->pred;
	p->pred->next = p->next;
	p->pred = n->pred;
	p->next = n;
	n->pred = p;
	p->pred->next = p;
	return p;
}
template<typename T>
Posi(T) List<T>::insertAsNext(Posi(T) p, Posi(T) n)
{
	p->next->pred = p->pred;
	p->pred->next = p->next;
	p->pred = n;
	p->next = n->next;
	n->next = p;
	p->next->pred = p;
	return p;
}
template<typename T>
void List<T>::sort(Posi(T) p, int n)
{
	//insertionSort(p, n);
	//selectionSort(p, n);
	mergeSort(p, n);
}

template<typename T>
void List<T>::insertionSort(Posi(T) p, int n)
{
	Posi(T) runner = p;
	p = p->next;
	for (int i = 1; i < n; i++)
	{
		
		int j = i+1;
		while (j-- > 0)
		{
			if ((p->data)>(runner->data)||p==header)//短路逻辑
			{
				Posi(T) temp = p->next;
				insertAsNext(p, runner);
				runner = temp->pred;
				p = temp;
				break;
			}
			else
			{
				runner = runner->pred;
			}
		}
	}
}
template<typename T>
Posi(T) List<T>::search(T const& e, int n, Posi(T) p) const
{
	while (n-->0)
	{
		p = p->pred;
		if (p->data < e)
		{
			return p;
		}
	}
	return header;
}

template<typename T>
void List<T>::selectionSort(Posi(T) p, int n)
{
	do
	{
		insertAsNext(p=selectMax(p, n), header);
		p = p->next;
	} while (n-->0);
}

template<typename T>//包括p在内的n个元素
Posi(T) List<T>::merge(Posi(T) left_p, int left_len,Posi(T) right_p, int right_len)
{
	while (left_len > 0&&right_len > 0)
	{
		if (left_p->data < right_p->data)
		{
			left_p = left_p->next;
			left_len--;
		}
		else
		{
			Posi(T) temp_p = right_p->next;
			insertAsPre(right_p, left_p);
			right_p = temp_p;
			right_len--;
		}
	}
	while (right_len-->0)
	{
		right_p = right_p->next;
	}
	return right_p;
}

template<typename T>
void List<T>::mergeSort(Posi(T) p, int n)
{
	Posi(T) h = p->pred;
	Posi(T) r_p;
	for (int i = 1; i < n; i*=2)
	{
		p = h->next;
		r_p = p;
		int count = 0;
		while (count*2<n)
		{
			int r_len = 0;
			while (r_len<i&&r_p!=trailer)
			{
				r_p = r_p->next;
				r_len++;
				count++; //右链表移动的次数
			}
			if (r_p == trailer)
			{
				break;
			}
			if (count*2>n)
			{
				r_len = n%i;
			}
			p = merge(p, i, r_p, r_len);
			r_p = p;
		}
	}
}