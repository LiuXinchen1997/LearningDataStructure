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
