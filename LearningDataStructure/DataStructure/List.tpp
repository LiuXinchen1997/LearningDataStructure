/* implementation of List */
#pragma once

#include "List.h"


template <class T> ListNodePosi(T) lxc::ListNode<T>::insert_as_pred(const T& e)
{
	ListNodePosi(T) new_node = new ListNode<T>(e, this->pred, this);
	this->pred->succ = new_node; this->pred = new_node;
	
	return new_node;
}


template <class T> ListNodePosi(T) lxc::ListNode<T>::insert_as_succ(const T& e)
{
	ListNodePosi(T) new_node = new ListNode<T>(e, this, this->succ);
	this->succ->pred = new_node; this->succ = new_node;

	return new_node;
}
