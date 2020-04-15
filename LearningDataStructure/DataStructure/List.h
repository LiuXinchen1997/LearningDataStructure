/* declaration of List */
#pragma once

#include "List.tpp"
#include "../General/Base.h"

namespace lxc {
	#define ListNodePosi(T) lxc::ListNode<T>*
	template <class T> struct ListNode
	{
		T element;
		ListNodePosi(T) pred;
		ListNodePosi(T) succ;

		ListNode() {}
		ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
			: element(e), pred(p), succ(s) {}

		void feed(const T e) { this->element = e; }
		ListNodePosi(T) insert_as_pred(const T& e);
		ListNodePosi(T) insert_as_succ(const T& e);
	};
}