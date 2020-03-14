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
SizeType lxc::String::_cstr_len(const char* cstr)
{
	SizeType size = 0;
	while (cstr[size]) { size++; }

	return size;
}


// constructor
void lxc::String::_copy_from(const char* cstr, SizeType low, SizeType high)
{
	this->_elements = new char[(high - low + 1) << 1];
	this->_capacity = ((high - low + 1) << 1);
	this->_size = 0;

	for (SizeType pos = low; pos < high; pos++) {
		this->_elements[this->_size++] = cstr[pos];
	}
	this->_elements[this->_size] = '\0';
}

lxc::String::String()
{
	this->_elements = new char[DEFAULT_CAPACITY + 1];
	this->_capacity = DEFAULT_CAPACITY;
	this->_size = 0;

	this->_elements[this->_size] = '\0';
	std::cout << this->_elements << std::endl;
}

lxc::String::String(const char* cstr, SizeType low, SizeType high)
{ this->_copy_from(cstr, low, high); }

lxc::String::String(const char* cstr)
{ this->_copy_from(cstr, 0, lxc::String::_cstr_len(cstr)); }

lxc::String::String(const String& str, SizeType low, SizeType high)
{ this->_copy_from(str._elements, low, high); }

lxc::String::String(const String& str)
{ this->_copy_from(str._elements, 0, str._size); }

lxc::String::String(SizeType n, char c)
{
	this->_elements = new char[2 * n];
	this->_capacity = 2 * n;
	this->_size = 0;

	while (this->_size < n) {
		this->_elements[this->_size++] = c;
	}
	this->_elements[this->_size] = '\0';
}
