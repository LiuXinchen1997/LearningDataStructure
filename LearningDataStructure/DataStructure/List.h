/* declaration of List */
#pragma once

#include "List.tpp"
#include "../General/Base.h"

namespace lxc {
	#define ListNodePosi(T) lxc::ListNode<T>*
	template <class T> struct ListNode
	{
		T _element;
		ListNodePosi(T) _pred;
		ListNodePosi(T) _succ;

		ListNode() {}
		ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
			: _element(e), _pred(p), _succ(s) {}

		void feed(const T e) { this->_element = e; }
		ListNodePosi(T) insert_as_pred(const T& e);
		ListNodePosi(T) insert_as_succ(const T& e);
	};

	template <class T> class List
	{
	protected:
		SizeType _size;
		ListNodePosi(T) _header;
		ListNodePosi(T) _trailer;
		
		void _init();
		void _clear();
	public:
		// constructor
		List() { this->_init(); }
		List(const List<T>& l);
		List(const List<T>& l, SizeType low, SizeType high);
		List(ListNodePosi(T) p, SizeType n);

		// deconstructor
		~List();

		// attribution getter
		SizeType size() const { return this->_size; }
		ListNodePosi(T) header() const { return this->_header; }
		ListNodePosi(T) trailer() const { return this->_trailer; }
	};
}
