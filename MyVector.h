#ifndef MYVECTOR_H
#define MYVECTOR_H
typedef int rank;
#define DEFAULT_CAPACITY 3

template <class T> class MyVector
{
    protected:
        rank _size; //规模
        int _capacity; //容量
        T* _elem; //数据区
        void copyForm(T const* Array,rank lo,rank hi); //复制数组区间A[lo ,hi]
        void expand(); //空间不足时扩容
        void shrink();  //装填因子过小时压缩
        bool bubble(rank lo,rank hi); //扫描交换
        void bubbleSort(rank lo,rank hi); //起泡排序算法
        rank max(rank lo,rank hi);
        void selectionSort(rank lo, rank hi); //选择排序算法
        void merge (rank lo,rank mi,rank hi); //归并算法
        void mergeSort(rank lo,rank hi); //归并排序算法
        rank partition(rank lo,rank hi); //轴点构造算法
        void quickSort(rank lo,rank hi); //快速排序算法
        void heapSort(rank lo,rank hi); //堆排序
    public:
        //构造函数
        MyVector(int c = DEFAULT_CAPACITY,int s = 0,T v = 0)
        {
            _elem = new T[_capacity = c];
            for(_size = 0;_size<s;_elem[_size++]=0);

        }
        MyVector(T const* Array)
        {
            copyForm(Array,0,3);
        }
        MyVector(T const* Array,rank n)
        {
            copyForm(Array,0,n);
        }
        MyVector(T const* Array,rank lo ,rank hi)
        {
            copyForm(Array,lo,hi);
        }
        MyVector(MyVector<T> const& v)
        {
            copyForm(v._elem,0,v._size);
        }
        MyVector(MyVector<T> const& v,rank lo ,rank li)
        {
            copyForm(v._elem,lo,li);
        }
        //构造函数end
        //析构函数
        virtual ~MyVector()
        {
            delete [] _elem; // 释放内存空间
        };

        //只读接口
        rank size() const{ return _size;} //规模
        bool isEmpty() const { return !_size;}
        int disordered() const;

        rank find(T const& elem) const //无序向量访问
        {
            return find(elem,0,_size);
        }
        rank find(T const& elem,rank lo ,rank hi) const
        {
            while(lo < hi)
            {
                if(_elem[lo++]==elem)
                {
                    return lo-1;
                }
            }
            return -1;
        }
        //有序向量查找
        rank search(T const& elem) const
        {
            return (0 >= _size)?-1:search(elem,0,_size);
        }
        rank search(T const& elem,rank lo, rank hi) const;
        //可写接口
        T& operator[](rank r) const
        {
                return _elem[r];
        } //重载下标操作符

        MyVector<T>& operator = (MyVector<T> const&);
        T remove(rank r);
        int remove(rank lo,rank li);
        rank insert(rank r ,T const& elem);
        rank insert(T const& e)
        {
            return insert(_size,e);
        }
        void sort (rank lo,rank hi);
        void sort()
        {
            sort(0,_size);
        }
        void unsort(rank lo,rank hi);
        void unsort()
        {
            unsort(0,_size);
        }
        int deduplicate(); //无序去重
        int uniquify(); //有序去重
        //遍历
        void traverse(void(*)( T& ));
        template <typename VST> void traverse( VST& );

    private:
};

template <class T>
void MyVector<T>::copyForm(T const* Array,rank lo,rank hi)
{
    _elem = new T[2*(hi - lo)];
    _size = 0;
    while(lo < hi)
    {
        _elem[_size++] = Array[lo++];
    }
}

//扩容
template <class T>
void MyVector<T>::expand()
{
    if(_size<_capacity) return;
    if(_capacity<DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity<<=1];
    for(int i=0;i<_size;i++)
    {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

//缩容
template <class T>
void MyVector<T>::shrink()
{
    if(_capacity << 1 < DEFAULT_CAPACITY ) return;
    if(_size << 2 > _capacity ) return;
    T* oldElem = _elem;
    _elem = new T[_capacity>>=2];
    for(int i = 0;i <_size;i++)
    {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

//删除
template <class T>
int MyVector<T>::remove(int lo,int hi)
{
    if(lo == hi)
    {
        return;
    }
    while(hi<_size)
    {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo; //直接抛弃后面的
    shrink();
    return hi - lo;
}
template <class T>
T MyVector<T>::remove(rank r)
{
    T elem = _elem[r];
    remove(r,r+1);
    return elem;
}
//无序去重


template <class T>
int MyVector<T>::deduplicate()
{
    int oldSize = _size;
    rank i= 1；
    while(i < _size)
    {
        (find(_elem[i],0,i)<0?i++:remove()i);
    }
    return oldSize-_size;
}

//插入
template <class T>
int MyVector<T>::insert(rank r,T & const elem)
{
    expand();
    for(int i = _size;i>r;i--)
    {
        _elem[i] = _elem[i-1];
    }
}
#endif // MYVECTOR_H
