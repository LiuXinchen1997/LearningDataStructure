/* implementation of Vector */
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

#include "Vector.h"


template <class T>
std::ostream& lxc::operator<< (std::ostream& os, const lxc::Vector<T>& v)
{
	os << v.to_Str();
	return os;
}


// static member
template <class T> const lxc::SizeType lxc::Vector<T>::DEFAULT_CAPACITY = 3;
template <class T> const lxc::SizeType lxc::Vector<T>::NPOS = lxc::NPOS;
template <class T> const double lxc::Vector<T>::SHRINK_RATIO = 0.25;


// auxiliary
template <class T>
void lxc::Vector<T>::_copy_from(const T* arr, lxc::SizeType low, lxc::SizeType high)
{
	// copy from [low, high)
	this->_capacity = (high - low) * 2;
	this->_elements = new T[this->_capacity];
	this->_size = 0;
	while (low < high) {
		this->_elements[_size++] = arr[low++];
	}
}

template <class T>
void lxc::Vector<T>::_expand()
{
	T* new_elements = new T[(this->_capacity <<= 1)];
	for (lxc::SizeType i = 0; i < this->_size; i++) { new_elements[i] = this->_elements[i]; }
	delete[] this->_elements;
	this->_elements = new_elements;
}

template <class T>
void lxc::Vector<T>::_shrink()
{
	if (this->_capacity <= DEFAULT_CAPACITY) { return; }

	T* new_elements = new T[(this->_capacity >>= 1)];
	lxc::SizeType new_size = 0;
	for (; new_size < lxc::min_of_2(this->_size, this->_capacity); new_size++) {
		new_elements[new_size] = this->_elements[new_size];
	}
	delete[] this->_elements;
	this->_elements = new_elements;
	this->_size = new_size;
}


// constructor
template <class T>
lxc::Vector<T>::Vector()
{
	this->_capacity = DEFAULT_CAPACITY;
	this->_size = 0;
	this->_elements = new T[this->_capacity];
}

template <class T>
lxc::Vector<T>::Vector(lxc::SizeType _capacity, lxc::SizeType _size, T _ele)
{
	_capacity = lxc::max_of_2(_capacity, _size);
	this->_capacity = _capacity;
	this->_size = _size;
	this->_elements = new T[this->_capacity];
	for (lxc::SizeType i = 0; i < _size; i++) {
		this->_elements[i] = _ele;
	}
}

template <class T>
lxc::Vector<T>::Vector(const T* arr, lxc::SizeType size)
{
	this->_copy_from(arr, 0, size);
}

template <class T>
lxc::Vector<T>::Vector(const T* arr, lxc::SizeType low, lxc::SizeType high)
{
	this->_copy_from(arr, low, high);
}

template <class T>
lxc::Vector<T>::Vector(const lxc::Vector<T>& v)
{
	this->_copy_from(v._elements, 0, v._size);
}

template <class T>
lxc::Vector<T>::Vector(const lxc::Vector<T>& v, lxc::SizeType low, lxc::SizeType high)
{
	this->_copy_from(v._elements, low, high);
}


// deconstructor
template <class T>
lxc::Vector<T>::~Vector() { delete[] this->_elements; }


// capacity
template <class T>
lxc::SizeType lxc::Vector<T>::size() const { return this->_size; }

template <class T>
lxc::SizeType lxc::Vector<T>::capacity() const { return this->_capacity; }

template <class T>
bool lxc::Vector<T>::empty() const { return this->_size == 0; }

template <class T>
void lxc::Vector<T>::resize(lxc::SizeType new_size, const T ele)
{
	if (new_size <= this->_size) { this->_size = new_size; return; }
	if (new_size <= this->_capacity) {
		for (; this->_size < new_size; ) { this->_elements[this->_size++] = ele; }
		return;
	}

	while (new_size > this->_capacity) { this->_expand(); }
	for (; this->_size < new_size; ) { this->_elements[this->_size++] = ele; }
}

template <class T>
void lxc::Vector<T>::reserve(lxc::SizeType new_capacity)
{
	if (new_capacity < DEFAULT_CAPACITY) { return; }
	if (new_capacity <= this->_size) { return; }
	T* new_elements = new T[new_capacity];
	for (lxc::SizeType i = 0; i < this->_size; i++) {
		new_elements[i] = this->_elements[i];
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_capacity = new_capacity;
}


// access elements(read only)
template <class T>
bool lxc::Vector<T>::is_ordered() const
{
	for (lxc::SizeType i = 0; i < this->_size - 1; i++) {
		if (this->_elements[i] > this->_elements[i + 1]) { return false; }
	}
	return true;
}

template <class T>
T lxc::Vector<T>::get(lxc::SizeType pos) const 
{
	assert_in_accessible_range(*this, pos, "Vector::get");
	return this->_elements[pos];
}

template <class T>
T lxc::Vector<T>::front() const 
{
	assert_in_accessible_range(*this, 0, "Vector::front");
	return this->get(0); 
}

template <class T>
T lxc::Vector<T>::back() const 
{
	assert_in_accessible_range(*this, this->_size - 1, "Vector::back");
	return this->get(this->_size - 1);
}

template <class T>
lxc::SizeType lxc::Vector<T>::find(const T& ele) const { return this->find(ele, 0, this->_size); }

template <class T>
lxc::SizeType lxc::Vector<T>::find(const T& ele, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);

	for (lxc::SizeType i = low; i < high; i++) {
		if (this->get(i) == ele) { return i; }
	}
	return this->NPOS; // don't find it.
}

template <class T>
lxc::SizeType lxc::Vector<T>::search(const T& ele) const
{
	return this->search(ele, 0, this->_size);
}

template <class T>
lxc::SizeType lxc::Vector<T>::search(const T& ele, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);

	if (!this->is_ordered()) { return this->NPOS; }
	while (low < high) {
		lxc::SizeType mid = (low + high) / 2;
		if (this->get(mid) == ele) { return mid; }
		else if (this->get(mid) < ele) { low = mid + 1; }
		else { high = mid; }
	}

	return this->NPOS;
}

template <class T>
bool lxc::Vector<T>::operator==(const lxc::Vector<T>& v) const
{
	if (this->_size != v._size) { return false; }
	for (lxc::SizeType i = 0; i < this->_size; i++) {
		if (this->get(i) != v.get(i)) { return false; }
	}

	return true;
}

template <class T>
bool lxc::Vector<T>::equals(const Vector<T>& v) const
{ return *this == v; }

template <class T>
bool lxc::Vector<T>::equals(const T* arr, lxc::SizeType size) const
{ return *this == lxc::Vector<T>(arr, size); }

template <class T>
bool lxc::Vector<T>::equals(const T* arr, lxc::SizeType low, lxc::SizeType high) const
{ return *this == lxc::Vector<T>(arr, low, high); }

template <class T>
lxc::String lxc::Vector<T>::to_Str() const
{
	String str = String("Vector { capacity: ") + String::to_String(this->_capacity)
		+ ", size: " + String::to_String(this->_size) + ", elements: [ ";
	for (lxc::SizeType i = 0; i < this->_size; i++) {
		if (i) { str += ", "; }
		str += String::to_String(this->get(i));
	}
	str += "] }";

	return str;
}


// writable interface and modifier
template <class T>
T& lxc::Vector<T>::operator[] (lxc::SizeType pos) const { return this->_elements[pos]; }

template <class T>
lxc::Vector<T>& lxc::Vector<T>::operator=(const lxc::Vector<T>& v)
{
	if (this->_elements) delete[] this->_elements;
	this->_copy_from(v._elements, 0, v._size);
	return *this;
}

template <class T>
void lxc::Vector<T>::assign(const T* arr, lxc::SizeType size)
{ *this = Vector(arr, size); }

template <class T>
void lxc::Vector<T>::assign(const T* arr, lxc::SizeType low, lxc::SizeType high)
{ *this = Vector(arr, low, high); }

template <class T>
void lxc::Vector<T>::assign(const lxc::Vector<T>& v) { *this = Vector(v); }

template <class T>
void lxc::Vector<T>::assign(const lxc::Vector<T>& v, lxc::SizeType low, lxc::SizeType high)
{ *this = Vector(v, low, high); }

template <class T>
void lxc::Vector<T>::swap(lxc::Vector<T>& v) { this->_swap(*this, v); }

template <class T>
void lxc::Vector<T>::clear() { *this = Vector(); }

template <class T>
T lxc::Vector<T>::remove(lxc::SizeType pos)
{
	T ele = this->get(pos);
	this->remove(pos, pos + 1);

	return ele;
}

template <class T>
lxc::SizeType lxc::Vector<T>::remove(lxc::SizeType low, lxc::SizeType high)
{
	T* new_elements = new T[this->_capacity];
	for (lxc::SizeType i = 0, j = 0; i < this->_size; i++) {
		if (low <= i && i < high) { continue; }
		new_elements[j] = this->_elements[i];
		j++;
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_size -= (high - low);

	if (double(this->_size) / this->_capacity < lxc::Vector<T>::SHRINK_RATIO) { this->_shrink(); }
	return (high - low);
}

template <class T>
T lxc::Vector<T>::remove_back()
{
	T ele = this->_elements[this->_size - 1];
	this->_size--;

	if (double(this->_size) / this->_capacity < lxc::Vector<T>::SHRINK_RATIO) { this->_shrink(); }
	return ele;
}

template <class T>
T lxc::Vector<T>::remove_front()
{
	T ele = this->_elements[0];
	T* new_elements = new T[this->_capacity];
	for (lxc::SizeType i = 1, j = 0; i < this->_size; i++, j++) {
		new_elements[j] = this->_elements[i];
	}
	delete[] this->_elements;
	this->_elements = new_elements;
	this->_size--;

	if (double(this->_size) / this->_capacity < lxc::Vector<T>::SHRINK_RATIO) { this->_shrink(); }
	return ele;
}

template <class T>
lxc::SizeType lxc::Vector<T>::remove_if(bool(*filter)(const T))
{
	T* new_elements = new T[this->_capacity];
	lxc::SizeType new_size = 0;
	for (lxc::SizeType i = 0; i < this->_size; i++) {
		if (!filter(this->_elements[i])) { 
			new_elements[new_size++] = this->_elements[i]; 
		}
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	lxc::SizeType res = this->_size - new_size;
	this->_size = new_size;

	return res;
}

template <class T>
void lxc::Vector<T>::insert(lxc::SizeType pos, const T& ele)
{
	if (this->_size == this->_capacity) { this->_expand(); }

	T* new_elements = new T[this->_capacity];
	for (lxc::SizeType i = 0, j = 0; j < this->_size + 1;) {
		if (j == pos) {
			new_elements[j] = ele;
			j++;
			continue;
		}

		new_elements[j] = this->_elements[i];
		i++; j++;
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_size++;
}

template <class T>
void lxc::Vector<T>::insert(lxc::SizeType pos, const T* arr, lxc::SizeType low, lxc::SizeType high)
{
	while (this->_capacity < this->_size + (high - low)) { this->_expand(); }

	T* new_elements = new T[this->_capacity];
	for (lxc::SizeType i = 0, j = 0; j < this->_size + (high - low);) {
		if (pos <= j && j < pos + high - low) {
			new_elements[j] = arr[low + j - pos];
			j++;
			continue;
		}
		new_elements[j] = this->_elements[i];
		i++; j++;
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_size += (high - low);
}

template <class T>
void lxc::Vector<T>::insert(lxc::SizeType pos, const lxc::Vector<T>& v, lxc::SizeType low, lxc::SizeType high)
{
	this->insert(pos, v._elements, low, high);
}

template <class T>
void lxc::Vector<T>::insert(lxc::SizeType pos, const lxc::Vector<T>& v, lxc::SizeType n)
{
	this->insert(pos, v, 0, n);
}

template <class T>
void lxc::Vector<T>::insert(lxc::SizeType pos, const lxc::Vector<T>& v)
{
	this->insert(pos, v, 0, v._size);
}

template <class T>
void lxc::Vector<T>::insert_back(const T& ele)
{ this->insert(this->_size, ele); }

template <class T>
void lxc::Vector<T>::insert_front(const T& ele)
{ this->insert(0, ele); }

template <class T>
lxc::Vector<T> lxc::Vector<T>::operator+(const Vector<T>& v)
{
	lxc::Vector<T> res_v(*this);
	res_v.insert(res_v.size(), v);
	return res_v;
}

template <class T>
lxc::Vector<T>& lxc::Vector<T>::operator+=(const Vector<T>& v)
{
	this->insert(this->_size, v);
	return *this;
}


// functional op
template <class T> template <class S>
lxc::Vector<S> lxc::Vector<T>::map_to(S(*mapper)(T))
{
	Vector<S> v;
	for (lxc::SizeType i = 0; i < this->_size; i++) { 
		v.insert_back(mapper(this->_elements[i]));
	}

	return v;
}

template <class T> template <class S> 
S lxc::Vector<T>::reduce_to(S(*reducer)(const T, const T))
{
	if (this->_size < 2) { throw "reduce error: too few elements."; return 0; }
	S cur = reducer(this->_elements[0], this->_elements[1]);
	for (lxc::SizeType i = 2; i < this->_size; i++) {
		cur = reducer(cur, this->_elements[i]);
	}

	return cur;
}


// sort/unsort/uniquify
template <class T> template <class S>
void lxc::Vector<T>::_swap(S& ele1, S& ele2) { S tmp = ele1; ele1 = ele2; ele2 = tmp; }

template <class T>
void lxc::Vector<T>::_bubble_sort(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	for (lxc::SizeType i = 0; i < high - low; i++) {
		for (lxc::SizeType j = low; j < high - i - 1; j++) {
			if (!comp(this->_elements[j], this->_elements[j + 1])) {
				T tmp = this->_elements[j];
				this->_elements[j] = this->_elements[j + 1];
				this->_elements[j + 1] = tmp;
			}
		}
	}
}

template <class T>
void lxc::Vector<T>::_insert_sort(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	for (lxc::SizeType i = low; i < high; i++) {
		T tmp = this->_elements[i];
		lxc::SizeType j = i - 1;
		while (j >= low) {
			if (comp(tmp, this->_elements[j])) {
				this->_elements[j + 1] = this->_elements[j];
				j--;
			}
			else {
				break;
			}
		}
		this->_elements[j + 1] = tmp;
	}
}

template <class T>
void lxc::Vector<T>::_select_sort(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	for (lxc::SizeType i = high - 1; i > low; i--) {
		T _max = this->_elements[low];
		lxc::SizeType _max_pos = low;
		for (lxc::SizeType j = low + 1; j <= i; j++) {
			if (comp(_max, this->_elements[j])) {
				_max = this->_elements[j];
				_max_pos = j;
			}
		}
		T tmp = this->_elements[_max_pos];
		this->_elements[_max_pos] = this->_elements[i];
		this->_elements[i] = tmp;
	}
}

template <class T>
void lxc::Vector<T>::_max_heapify(lxc::SizeType low, lxc::SizeType high, lxc::SizeType i, bool(*comp)(T&, T&))
{
	lxc::SizeType lc = (i - low) * 2 + 1 + low;
	lxc::SizeType rc = (i - low) * 2 + 2 + low;
	lxc::SizeType _max_pos = i;
	if (lc < high && comp(this->_elements[_max_pos], this->_elements[lc])) {
		_max_pos = lc;
	}
	if (rc < high && comp(this->_elements[_max_pos], this->_elements[rc])) {
		_max_pos = rc;
	}

	if (_max_pos != i) {
		this->_swap(this->_elements[_max_pos], this->_elements[i]);
		this->_max_heapify(low, high, _max_pos, comp);
	}
}

template <class T>
void lxc::Vector<T>::_build_max_heap(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	for (lxc::SizeType i = low + (low + high) / 2 + 1; i >= low; i--) {
		this->_max_heapify(low, high, i, comp);
	}
}

template <class T>
void lxc::Vector<T>::_heap_sort(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	this->_build_max_heap(low, high, comp);
	for (lxc::SizeType i = high - 1; i > low; i--) {
		this->_swap(this->_elements[low], this->_elements[i]);
		this->_max_heapify(low, i, low, comp);
	}
}

template <class T>
void lxc::Vector<T>::_merge(lxc::SizeType low, lxc::SizeType high, lxc::SizeType mid, bool(*comp)(T&, T&))
{
	// merge two lists: [low, mid) and [mid, high)
	T* tmp = new T[high - low + 1];
	for (lxc::SizeType i = low, j = mid, k = 0; k < high - low;) {
		if (high <= j || (i < mid && comp(this->_elements[i], this->_elements[j]))) {
			tmp[k] = this->_elements[i];
			k++; i++;
		}
		if (mid <= i || (j < high && comp(this->_elements[j], this->_elements[i]))) {
			tmp[k] = this->_elements[j];
			k++; j++;
		}
	}

	for (lxc::SizeType i = 0; i < high - low; i++) {
		this->_elements[low + i] = tmp[i];
	}
	delete[] tmp;
}

template <class T>
void lxc::Vector<T>::_merge_sort(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	if (high - 1 <= low) { return; }
	lxc::SizeType mid = (low + high) / 2;
	_merge_sort(low, mid, comp);
	_merge_sort(mid, high, comp);
	this->_merge(low, high, mid, comp);
}

template <class T>
lxc::SizeType lxc::Vector<T>::_partition(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	T seperate = this->_elements[high - 1];
	lxc::SizeType i = low, j = low;
	while (true) {
		if (comp(this->_elements[j], seperate)) {
			this->_swap(this->_elements[i++], this->_elements[j]);
		}
		j++;
		if (j == high) { break; }
	}
	this->_swap(this->_elements[i], this->_elements[high - 1]);

	return i;
}

template <class T>
void lxc::Vector<T>::_quick_sort(lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	if (high <= low) { return; }
	lxc::SizeType seperate_pos = this->_partition(low, high);
	_quick_sort(low, seperate_pos);
	_quick_sort(seperate_pos + 1, high);
}

template <class T>
void lxc::Vector<T>::sort(const char* type, lxc::SizeType low, lxc::SizeType high, bool(*comp)(T&, T&))
{
	switch (type[0])
	{
	case 'b':
		this->_bubble_sort(low, high, comp);
		break;
	case 'i':
		this->_insert_sort(low, high, comp);
		break;
	case 's':
		this->_select_sort(low, high, comp);
		break;
	case 'h':
		this->_heap_sort(low, high, comp);
		break;
	case 'm':
		this->_merge_sort(low, high, comp);
		break;
	case 'q':
		this->_quick_sort(low, high, comp);
		break;
	default:
		break;
	}
}

template <class T>
void lxc::Vector<T>::unsort(lxc::SizeType low, lxc::SizeType high)
{
	srand((unsigned int)time(0));

	for (lxc::SizeType i = high - 1; i >= low + 1; i--) {
		lxc::SizeType pos = (rand() % (i - low + 1)) + low;
		this->_swap(this->_elements[pos], this->_elements[i]);
	}
}

template <class T>
lxc::SizeType lxc::Vector<T>::deduplicate()
{
	T* new_elements = new T[this->_capacity];
	lxc::SizeType new_size = 0;
	for (lxc::SizeType i = 0; i < this->_size; i++) {
		bool existed = false;
		for (lxc::SizeType j = 0; j < i; j++) {
			if (this->_elements[j] == this->_elements[i]) { existed = true; break; }
		}
		if (!existed) { new_elements[new_size++] = this->_elements[i]; }
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	lxc::SizeType res = this->_size - new_size;
	this->_size = new_size;

	return res;
}

template <class T>
lxc::SizeType lxc::Vector<T>::uniquify()
{
	if (!this->is_ordered()) { throw "lxc::Vector is not ordered."; }
	T* new_elements = new T[this->_capacity];
	lxc::SizeType new_size = 0;

	new_elements[new_size++] = this->_elements[0];
	T cur_ele = this->_elements[0];
	for (lxc::SizeType i = 1; i < this->_size; i++) {
		if (this->get(i) != cur_ele) {
			new_elements[new_size++] = this->_elements[i];
			cur_ele = this->_elements[i];
		}
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	lxc::SizeType res = this->_size - new_size;
	this->_size = new_size;

	return res;
}

// traverse
template <class T>
void lxc::Vector<T>::traverse(void(*visit)(T&))
{
	for (lxc::SizeType i = 0; i < this->_size; i++) { visit(this->_elements[i]); }
}

template <class T> template <class VST>
void lxc::Vector<T>::traverse(VST& visit)
{
	for (lxc::SizeType i = 0; i < this->_size; i++) { visit(this->_elements[i]); }
}
