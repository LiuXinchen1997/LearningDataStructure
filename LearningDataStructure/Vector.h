#pragma once

typedef int Rank;

#define DEFAULT_CAPACITY 3
#define min_of_2(a, b) (a < b ? a : b)

template <class T>
class Vector
{
protected:
	int _size;
	int _capacity;
	T* _elements;
	void copy_from(const T* arr, Rank low, Rank high);
	void expand();
	void shrink();

public:
	// constructor
	Vector(int capacity = DEFAULT_CAPACITY, int s = 0, T e = 0);
	Vector(const T* arr, Rank n); // copy from [0, n) of arr
	Vector(const T* arr, Rank low, Rank high);
	Vector(const Vector<T>& v);
	Vector(const Vector<T>& v, Rank low, Rank high);

	// deconstructor
	~Vector();

	// readable only
	Rank size() const;
	Rank empty() const;
	bool is_ordered() const; // ordered: from min to max
	T get(Rank r) const;
	Rank find(const T& ele) const; // search for ordered array(find first of ele)
	Rank find(const T& ele, Rank low, Rank high) const; // search in [low, high)
	Rank search(const T& ele) const; // search for disordered array(binary search)
	Rank search(const T& ele, Rank low, Rank high) const;
	bool operator==(const Vector<T>& v) const;

	// writable
	T& operator[] (Rank r) const;
	Vector<T>& operator=(const Vector<T>& v);
	T remove(Rank r);
	int remove(Rank low, Rank high);
	Rank insert(Rank r, const T& ele);
	Rank insert_back(const T& ele);
	Rank insert_front(const T& ele);

	// sort/unsort/uniquify
	// transverse
};


// auxiliary
template <class T>
void Vector<T>::copy_from(const T* arr, Rank low, Rank high)
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
void Vector<T>::expand()
{
	if (double(this->_size) / this->_capacity < 0.5) { return; }

	T* new_elements = new T[(this->capacity <<= 1)];
	for (int i = 0; i < this->_size; i++) {
		new_elements[i] = this->_elements[i];
	}
	delete[] this->_elements;
	this->_elements = new_elements;
}

template <class T>
void Vector<T>::shrink()
{
	if (this->_capacity <= DEFAULT_CAPACITY) { return; }
	if (double(this->_size) / this->_capacity > 0.25) { return; }

	T* new_elements = new T[(this->_capacity >>= 1)];
	for (int i = 0; i < min_of_2(this->_size, this->_capacity); i++) {
		new_elements[i] = this->_elements[i];
	}
	delete[] this->_elements;
	this->_elements = new_elements;
}

// constructor
template <class T>
Vector<T>::Vector(int capacity, int s, T ele)
{
	this->_capacity = capacity;
	this->_size = s;
	this->_elements = new T[s];
	for (int i = 0; i < s; i++) {
		this->_elements[i] = ele;
	}
}

template <class T>
Vector<T>::Vector(const T* arr, Rank n)
{ this->copy_from(arr, 0, n); }

template <class T>
Vector<T>::Vector(const T* arr, Rank low, Rank high)
{ this->copy_from(arr, low, high); }

template <class T>
Vector<T>::Vector(const Vector<T>& v)
{ this->copy_from(v._elements, 0, v._size); }

template <class T>
Vector<T>::Vector(const Vector<T>& v, Rank low, Rank high)
{ this->copy_from(v._elements, low, high); }


// deconstructor
template <class T>
Vector<T>::~Vector() { delete[] this->_elements; }

// read only
template <class T>
Rank Vector<T>::size() const { return this->_size; }

template <class T>
Rank Vector<T>::empty() const { return this->_size == 0; }

template <class T>
bool Vector<T>::is_ordered() const
{
	for (int i = 0; i < this->_size - 1; i++) {
		if (this->_elements[i] > this->_elements[i + 1]) { return false; }
	}
	return true;
}

template <class T>
T Vector<T>::get(Rank r) const { return this->_elements[r]; }

template <class T>
Rank Vector<T>::find(const T& ele) const { return this->find(ele, 0, this->_size); }

template <class T>
Rank Vector<T>::find(const T& ele, Rank low, Rank high) const
{
	for (int i = low; i < high; i++) {
		if (this->get(i) == ele) { return i; }
	}
	return -1; // don't find it.
}

template <class T>
Rank Vector<T>::search(const T& ele) const
{ return this->search(ele, 0, this->_size); }

template <class T>
Rank Vector<T>::search(const T& ele, Rank low, Rank high) const
{
	if (!this->is_ordered()) { throw "Vector is not ordered."; }
	while (low < high) {
		Rank mid = (low + high) / 2;
		if (this->get(mid) == ele) { return mid; }
		else if (this->get(mid) < ele) { low = mid + 1; }
		else { high = mid; }
	}

	return -1;
}

template <class T>
bool Vector<T>::operator==(const Vector<T>& v) const
{
	if (this->_size != v._size) { return false; }
	for (int i = 0; i < this->_size; i++) {
		if (this->get(i) != v.get(i)) { return false; }
	}

	return true;
}


// writable
template <class T>
T& Vector<T>::operator[] (Rank r) const { return this->_elements[r]; }

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
	if (this->_elements) delete[] this->_elements;
	this->copy_from(v._elements, 0, v._size);
	return *this;
}

template <class T>
T Vector<T>::remove(Rank r)
{
	T ele = this->get(r);
	this->remove(r, r + 1);

	return ele;
}

template <class T>
int Vector<T>::remove(Rank low, Rank high)
{
	T* new_elements = new T[this->_capacity];
	for (int i = 0, j = 0; i < this->_size; i++) {
		if (i < low || high <= i) { continue; }
		new_elements[j] = this->_elements[i];
		j++;
	}

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_size -= (high - low);
	this->shrink();

	return (high - low);
}

template <class T>
Rank insert(Rank r, const T& ele)
{

}

//Rank insert_back(const T& ele);
//Rank insert_front(const T& ele);