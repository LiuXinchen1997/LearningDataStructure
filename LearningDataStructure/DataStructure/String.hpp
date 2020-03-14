/* implementation of String */

#pragma once
#include "String.h"
#include <iostream>


std::ostream& operator<< (std::ostream& os, const lxc::String& str)
{
	os << "capacity: " << str.capacity(); 
	os << ", size: " << str.size();
	os << ", elements: " << str.c_str();
	return os;
}


// static member methods
lxc::SizeType lxc::String::_cstr_len(const char* cstr)
{
	lxc::SizeType size = 0;
	while (cstr[size]) { size++; }

	return size;
}

void lxc::String::_cstr_copy(char* dest, const char* source, lxc::SizeType low, lxc::SizeType high)
{
	SizeType offset = 0;
	for (; offset < high - low; offset++) { dest[offset] = source[low + offset]; }
	dest[offset] = '\0';
}

void lxc::String::_cstr_copy(char* dest, const char* source)
{ lxc::String::_cstr_copy(dest, source, 0, lxc::String::_cstr_len(source)); }


// constructor
void lxc::String::_copy_from(const char* cstr, lxc::SizeType low, lxc::SizeType high)
{
	this->_elements = new char[(high - low + 1) << 1];
	this->_capacity = ((high - low + 1) << 1);
	
	lxc::String::_cstr_copy(this->_elements, cstr, low, high);
	this->_size = high - low;
}

void lxc::String::_copy_from(lxc::SizeType n, char c)
{
	this->_elements = new char[2 * n];
	this->_capacity = 2 * n;
	this->_size = 0;

	while (this->_size < n) {
		this->_elements[this->_size++] = c;
	}
	this->_elements[this->_size] = '\0';
}

lxc::String::String()
{
	this->_elements = new char[DEFAULT_CAPACITY + 1];
	this->_capacity = DEFAULT_CAPACITY;
	this->_size = 0;

	this->_elements[this->_size] = '\0';
}

lxc::String::String(const char* cstr, lxc::SizeType low, lxc::SizeType high)
{ this->_copy_from(cstr, low, high); }

lxc::String::String(const char* cstr)
{ this->_copy_from(cstr, 0, lxc::String::_cstr_len(cstr)); }

lxc::String::String(const String& str, lxc::SizeType low, lxc::SizeType high)
{ this->_copy_from(str._elements, low, high); }

lxc::String::String(const String& str)
{ this->_copy_from(str._elements, 0, str._size); }

lxc::String::String(lxc::SizeType n, char c)
{ this->_copy_from(n, c); }

lxc::String& lxc::String::operator= (const String& str)
{
	delete[] this->_elements;
	this->_copy_from(str.c_str(), 0, str.size());
	return *this;
}

lxc::String& lxc::String::operator= (const char* cstr)
{
	delete[] this->_elements;
	this->_copy_from(cstr, 0, lxc::String::_cstr_len(cstr));
	return *this;
}

lxc::String& lxc::String::operator= (char c)
{
	delete[] this->_elements;
	this->_copy_from(1, c);
	return *this;
}


// capacity
void lxc::String::_expand()
{
	char* new_elements = new char[this->_capacity <<= 1];
	lxc::String::_cstr_copy(new_elements, this->_elements);
	
	delete[] this->_elements;
	this->_elements = new_elements;
}

void lxc::String::_shrink()
{
	if ((this->_capacity >> 1) < this->DEFAULT_CAPACITY) { return; }

	char* new_elements = new char[this->_capacity = (this->_capacity >> 1) + 1];
	this->_size = lxc::min_of_2(this->_size, this->_capacity - 1);
	lxc::String::_cstr_copy(new_elements, this->_elements, 0, this->_size);
	
	delete[] this->_elements;
	this->_elements = new_elements;
}

void lxc::String::resize(lxc::SizeType new_size, char c)
{
	if (new_size <= this->_size) {
		this->_size = new_size;
		if (double(this->_size) / this->_capacity < 0.25) { this->_shrink(); }
		return;
	}

	while (this->_capacity < new_size + 1) { this->_expand(); }
	for (;  this->_size < new_size; ) {
		this->_elements[this->_size++] = c;
	}
	this->_elements[this->_size] = '\0';
}

void lxc::String::reserve(SizeType new_capacity)
{
	if (new_capacity <= this->_size) { return; }
	
	char* new_elements = new char[new_capacity];
	lxc::String::_cstr_copy(new_elements, this->_elements, 0, this->_size);
	delete[] this->_elements;
	this->_elements = new_elements;
	this->_capacity = new_capacity;
}
