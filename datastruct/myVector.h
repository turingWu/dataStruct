#ifndef MYVECTOR_H
#define MYVECTOR_H
typedef int rank;
#define DEFAULT_CAPACITY 3

template <class T> class MyVector
{
protected:
	
	void copyForm(T const* Array, rank lo, rank hi); //������������A[lo ,hi]
	void expand(); //�ռ䲻��ʱ����
	void shrink();  //װ�����ӹ�Сʱѹ��
	bool bubble(rank lo, rank hi); //ɨ�轻��
	void bubbleSort(rank lo, rank hi); //���������㷨
	rank max(rank lo, rank hi);
	void selectionSort(rank lo, rank hi); //ѡ�������㷨
	void merge(rank lo, rank mi, rank hi); //�鲢�㷨
	void mergeSort(rank lo, rank hi); //�鲢�����㷨
	rank partition(rank lo, rank hi); //��㹹���㷨
	void quickSort(rank lo, rank hi); //���������㷨
	void heapSort(rank lo, rank hi); //������
public:
	//���캯��
	MyVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size<s; _elem[_size++] = 0);

	}
	MyVector(T const* Array)
	{
		copyForm(Array, 0, 3);
	}
	MyVector(T const* Array, rank n)
	{
		copyForm(Array, 0, n);
	}
	MyVector(T const* Array, rank lo, rank hi)
	{
		copyForm(Array, lo, hi);
	}
	MyVector(MyVector<T> const& v)
	{
		copyForm(v._elem, 0, v._size);
	}
	MyVector(MyVector<T> const& v, rank lo, rank li)
	{
		copyForm(v._elem, lo, li);
	}
	//���캯��end
	//��������
	virtual ~MyVector()
	{
		delete[] _elem; // �ͷ��ڴ�ռ�
	};

	//ֻ���ӿ�
	rank size() const{ return _size; } //��ģ
	bool isEmpty() const { return !_size; }
	int disordered() const;

	rank find(T const& elem) const //������������
	{
		return find(elem, 0, _size);
	}
	rank find(T const& elem, rank lo, rank hi) const
	{
		return find(elem, lo, hi);
	}
	//������������
	rank search(T const& elem) const
	{
		return (0 >= _size) ? -1 : search(elem, 0, _size);
	}
	rank search(T const& elem, rank lo, rank hi) const;
	//��д�ӿ�
	T& operator[](rank r) const
	{
		return _elem[r];
	} //�����±������

	MyVector<T>& operator = (MyVector<T> const&);
	T remove(rank r);
	int remove(rank lo, rank li);
	rank insert(rank r, T const& elem);
	rank insert(T const& e)
	{
		return insert(_size, e);
	}
	void sort(rank lo, rank hi);
	void sort()
	{
		sort(0, _size);
	}
	void unsort(rank lo, rank hi);
	void unsort()
	{
		unsort(0, _size);
	}
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	//����
	void traverse(void(*)(T&));
	template <typename VST> void traverse(VST&);

private:
	rank _size; //��ģ
	int _capacity; //����
	T* _elem; //������
};
template <class T>
void MyVector<T>::copyForm(T const* Array, rank lo, rank hi)
{
	_elem = new T[2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = Array[lo++];
	}
}

template <class T>
void MyVector<T>::expand()
{
	if (_size<_capacity) return;
	if (_capacity<DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i<_size; i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

//����
template <class T>
void MyVector<T>::shrink()
{
	if (_capacity << 1 < DEFAULT_CAPACITY) return;
	if (_size << 2 > _capacity) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 2];
	for (int i = 0; i <_size; i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

//ɾ��
template <class T>
int MyVector<T>::remove(int lo, int hi)
{
	if (lo == hi)
	{
		return;
	}
	while (hi<_size)
	{
		_elem[lo++] = _elem[hi++];
	}
	_size = lo; //ֱ�����������
	shrink();
	return hi - lo;
}
template <class T>
T MyVector<T>::remove(rank r)
{
	T elem = _elem[r];
	remove(r, r + 1);
	return elem;
}
//����ȥ��


template <class T>
int MyVector<T>::deduplicate()
{
	int oldSize = _size;
	rank i = 1��
		while (i < _size)
		{
		(find(_elem[i], 0, i)<0 ? i++ : remove()i);
		}
	return oldSize - _size;
}

//����
template <class T>
int MyVector<T>::insert(rank r, T const& elem)
{
	expand();
	for (int i = _size; i>r; i--)
	{
		_elem[i] = _elem[i - 1];
	}
}
//����
template <class T> void MyVector<T>::traverse(void(*visit)(T &))
{
	for (int i = 0; i<_size; i++)
	{
		visit(_elem[i]);
	}
}
//����ȥ��
template <class T>
int MyVector<T>::uniquify()
{
	rank go = 0, j = 0;
	while (++go<_size)
	{
		if (_elem[go] != _elem[j])
		{
			_elem[j += 1] = _elem[go];
		}
	}
	_size = j + 1;
	shrink();
	return go - _size;
}
#endif // MYVECTOR_H