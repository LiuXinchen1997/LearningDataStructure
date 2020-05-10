/* implementation of List */
#pragma once

#include "List.h"


template <class T> ListNodePosi(T) lxc::ListNode<T>::insert_as_pred(const T& e)
{
	ListNodePosi(T) new_node = new ListNode<T>(e, this->_pred, this);
	this->_pred->_succ = new_node; this->_pred = new_node;
	
	return new_node;
}


template <class T> ListNodePosi(T) lxc::ListNode<T>::insert_as_succ(const T& e)
{
	ListNodePosi(T) new_node = new ListNode<T>(e, this, this->_succ);
	this->_succ->_pred = new_node; this->_succ = new_node;

	return new_node;
}


// constructor
template <class T> void lxc::List<T>::_init()
{
	this->_header = new ListNode<T>; this->_trailer = new ListNode<T>;
	this->_header->_succ = this->_trailer; this->_trailer->_pred = this->_header;
	this->_size = 0;
}

template <class T> lxc::List<T>::List(const List<T>& l)
{ List(l, 0, l._size - 1); }

template <class T> lxc::List<T>::List(const List<T>& l, SizeType low, SizeType high)
{
	this->_init();
	ListNodePosi(T) cur_l = l._header;
	for (SizeType i = 0; i <= low; i++) { cur_l = cur_l->_succ; }

	ListNodePosi(T) cur = this->_header;
	for (SizeType i = 0; i < high - low; i++) {
		cur->insert_as_succ(cur_l->_element);
		cur = cur->_succ; cur_l = cur_l->_succ;
	}
}

template <class T> lxc::List<T>::List(ListNodePosi(T) p, SizeType n)
{
	ListNodePosi(T) cur = this->_header;
	for (SizeType i = 0; i < n; i++) {
		cur->insert_as_succ(p->_element);
		cur = cur->_succ; p = p->_succ;
	}
}

template <class T> void lxc::List<T>::_copy_from(const T* arr, SizeType low, SizeType high)
{
	ListNodePosi(T) cur = this->_header;
	for (SizeType pos = low; pos < high; pos++)
	{
		cur->insert_as_succ(arr[pos]);
		std::cout << cur->_succ->_element << std::endl;
		cur = cur->_succ;
	}
}

template <class T> lxc::List<T>::List(const T* arr, SizeType low, SizeType high)
{ this->_init(); this->_copy_from(arr, low, high); }

template <class T> lxc::List<T>::List(const T* arr, SizeType n)
{ this->_init(); this->_copy_from(arr, 0, n); }


// deconstructor
template <class T> void lxc::List<T>::_clear()
{
	ListNodePosi(T) cur = this->_header;
	while (cur) {
		ListNodePosi(T) tmp = cur->_succ;
		delete cur; cur = tmp;
	}
}

template <class T> lxc::List<T>::~List()
{ this->_clear(); }


// element access
template <class T> T& lxc::List<T>::operator[](SizeType pos)
{
	ListNodePosi(T) cur_node = this->_header;
	for (SizeType i = 0; i <= pos; i++) {
		cur_node = cur_node->_succ;
	}

	return cur_node->_element;
}
