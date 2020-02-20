/* declaration of Vector */
#pragma once
#include <iostream>

typedef int SizeType;

#define DEFAULT_CAPACITY 3
#define min_of_2(a, b) (a < b ? a : b)

template <class T>
bool common_comp(T& ele1, T& ele2) { return (ele1 < ele2); }

namespace lxc {
	template <class T>
	class Vector
	{
	protected:
		SizeType _size;
		SizeType _capacity;
		T* _elements;
		void _copy_from(const T* arr, SizeType low, SizeType high);
		void _expand();
		void _shrink();

		// sort
		// comp can be considered as operator<
		void _swap(T& ele1, T& ele2);
		// for comp: if 1st ele < 2nd ele, return true; else return false.
		void _bubble_sort(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);
		void _insert_sort(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);
		void _select_sort(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);
		// heap sort
		void _max_heapify(SizeType low, SizeType high, SizeType i, bool(*comp)(T&, T&) = common_comp);
		void _build_max_heap(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);
		void _heap_sort(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);
		// merge sort
		void _merge(SizeType low, SizeType high, SizeType mid, bool(*comp)(T&, T&) = common_comp);
		void _merge_sort(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);
		// quick sort
		SizeType _partition(SizeType low, SizeType high);
		void _quick_sort(SizeType low, SizeType high, bool(*comp)(T&, T&) = common_comp);

	public:
		// constructor
		Vector(SizeType capacity = DEFAULT_CAPACITY, SizeType s = 0, T e = 0);
		Vector(const T* arr, SizeType size); // copy from [0, size) of arr
		Vector(const T* arr, SizeType low, SizeType high);
		Vector(const Vector<T>& v);
		Vector(const Vector<T>& v, SizeType low, SizeType high);

		// deconstructor
		~Vector();

		// capacity
		SizeType size() const;
		SizeType capacity() const;
		bool empty() const;
		void resize(SizeType new_size, T ele);
		void reserve(SizeType new_size);

		// access elements(read only)
		bool is_ordered() const; // ordered: from min to max
		T get(SizeType r) const;
		SizeType find(const T& ele) const; // search for ordered array(find first of ele)
		SizeType find(const T& ele, SizeType low, SizeType high) const; // search in [low, high)
		SizeType search(const T& ele) const; // search for disordered array(binary search)
		SizeType search(const T& ele, SizeType low, SizeType high) const;
		bool operator==(const Vector<T>& v) const;
		bool equals(const Vector<T>& v) const;
		bool equals(const T* arr, SizeType size) const;

		// writable interface and modifier
		T& operator[] (SizeType pos) const;
		Vector<T>& operator=(const Vector<T>& v);
		T remove(SizeType pos);
		SizeType remove(SizeType low, SizeType high);
		T remove_back();
		T remove_front();
		void insert(SizeType pos, const T& ele);
		void insert(SizeType pos, const T* arr, SizeType low, SizeType high);
		void insert(SizeType pos, const Vector<T>& v, SizeType low, SizeType high);
		void insert(SizeType pos, const Vector<T>& v, SizeType n);
		void insert(SizeType pos, const Vector<T>& v);
		void insert_back(const T& ele);
		void insert_front(const T& ele);

		// sort/unsort/uniquify
		void sort(SizeType low = 0, SizeType high = this->_size, const char* type = "bubble",
			bool(*comp)(T&, T&) = common_comp);

		// traverse
		void traverse(void(*visit)(T&)); // for function pointer
		template <class VST> void traverse(VST& visit); // for function object
	};
};
