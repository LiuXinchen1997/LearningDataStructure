/* implementation of Vector */

#pragma once
#include "String.h"

static SizeType lxc::String::cstrlen(char* cstr)
{
	SizeType size = 0;
	while (cstr[size]) { size++; }

	return size;
}

lxc::String::String()
{
	this->_elements = new char[DEFAULT_CAPACITY + 1];
	this->_capacity = DEFAULT_CAPACITY;
	this->_size = 0;

	this->_elements[this->_size] = '\0';
}

lxc::String::String(const String& str)
{
	this->_elements = new char[str._capacity + 1];
	this->_capacity = str._capacity;
	this->_size = str._size;

	for (SizeType pos = 0; pos < this->_size; pos++) { this->_elements[pos] = str._elements[pos]; }
	this->_elements[this->_size] = '\0';
}


//String(const String& str, SizeType low, SizeType high);
//String(const char* s, SizeType low, SizeType high);
//String(const char* s);
//String(SizeType n, char c);
