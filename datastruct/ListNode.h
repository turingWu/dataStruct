#ifndef LISTNODE_H_INCLUDED
#define LISTNODE_H_INCLUDED

#define Posi(T) ListNode<T>*

template <typename T>
struct ListNode
{
    T data;
    Posi(T) pred;
    Posi(T) next;
	ListNode() :data(NULL), pred(nullptr), next(nullptr)
	{

	}
    ListNode(T e,Posi(T) p = nullptr,Posi(T) n = nullptr)
    :data(e),pred(p),next(n)
    {


    }
    Posi(T) insertAsPred(T const& e);
    Posi(T) insertAsNext(T const& e);
};
template<typename T>
Posi(T) ListNode<T>::insertAsPred(T const& e)
{
    Posi(T) newNode = new ListNode(e,pred,this);
	if (pred!=nullptr)
	{
		pred->next = newNode;
	}
    pred = newNode;
    return newNode;
}
template <typename T>
Posi(T) ListNode<T>::insertAsNext(T const& e)
{
    Posi(T) newNode = new ListNode(e,this,next);
	if (next != nullptr)
	{
		next->pred = newNode;
	}
    next = newNode;
    return newNode;
}


#endif // LISTNODE_H_INCLUDED

