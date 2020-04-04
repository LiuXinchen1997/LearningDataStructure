/* implementation of String */

#pragma once
#include "String.h"
#include <iostream>
#include <climits>

#include <string>

#include "../General/Assert.h"


std::ostream& lxc::operator<< (std::ostream& os, const String& str)
{
	if (String::show_full_data) { os << str.to_cstr(); }
	else { os << str.elements(); }
	return os;
}

std::istream& lxc::operator>> (std::istream& is, String& str)
{
	char tmp_cstr[201]; // Oops!
	is >> tmp_cstr;
	String tmp_str(tmp_cstr); str = tmp_cstr;
	return is;
}


const lxc::SizeType lxc::String::DEFAULT_CAPACITY = 3;
const lxc::SizeType lxc::String::NPOS = INT_MAX;
const double lxc::String::SHRINK_RATIO = 0.25;
bool lxc::String::show_full_data = false;

// static member methods
lxc::SizeType lxc::String::_cstr_len(const char* cstr)
{
	lxc::SizeType size = 0;
	while (cstr[size]) { size++; }

	return size;
}

void lxc::String::_cstr_copy(char* dest, const char* source, lxc::SizeType low, lxc::SizeType high)
{
	high = lxc::min_of_2(high, lxc::String::_cstr_len(source));
	SizeType offset = 0;
	for (; offset < high - low; offset++) { dest[offset] = source[low + offset]; }
	dest[offset] = '\0';
}

int lxc::String::_cstr_comp(const char* cstr1, const char* cstr2)
{
	// return value: 
	// 0: str1 == str2
	// 1: str1 > str2
	// -1: str1 < str2
	SizeType len1 = lxc::String::_cstr_len(cstr1);
	SizeType len2 = lxc::String::_cstr_len(cstr2);
	lxc::SizeType len = lxc::min_of_2(len1, len2);
	for (SizeType pos = 0; pos < len; pos++) {
		if (cstr1[pos] < cstr2[pos]) { return -1; }
		else if (cstr2[pos] < cstr1[pos]) { return 1; }
	}
	if (len1 == len2) { return 0; }
	else if (len1 < len2) { return -1; }
	else { return 1; }
}

bool lxc::String::_cstr_equal(const char* cstr1, const char* cstr2)
{ return lxc::String::_cstr_comp(cstr1, cstr2) == 0; }


// type conversions
lxc::String lxc::String::to_String(int val) // !!!
{ return lxc::String(std::to_string(val).c_str()); }


// constructor
void lxc::String::_copy_from(const char* cstr, lxc::SizeType low, lxc::SizeType high)
{
	high = lxc::min_of_2(high, lxc::String::_cstr_len(cstr));
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
{ 
	high = min_of_2(high, this->_cstr_len(cstr));
	this->_copy_from(cstr, low, high); 
}

lxc::String::String(const String& str, lxc::SizeType low, lxc::SizeType high)
{
	high = min_of_2(high, str.size());
	this->_copy_from(str._elements, low, high);
}

lxc::String::String(lxc::SizeType n, char c)
{ this->_copy_from(n, c); }

lxc::String& lxc::String::operator= (const String& str)
{
	delete[] this->_elements;
	this->_copy_from(str.elements(), 0, str.size());
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


// getter
const lxc::String lxc::String::to_str() const
{
	const String str = String("String { capacity: ") + String::to_String(_capacity)
		+ ", size: " + String::to_String(_size) + ", elements: \""
		+ _elements + "\" }";

	return str;
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
		this->_size = new_size; this->_elements[this->_size] = '\0';
		if (double(this->_size) / this->_capacity < lxc::String::SHRINK_RATIO) { this->_shrink(); }
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

void lxc::String::clear()
{
	this->_size = 0;
	delete[] this->_elements;

	this->_elements = new char[lxc::String::DEFAULT_CAPACITY];
	this->_elements[this->_size] = '\0';
	this->_capacity = lxc::String::DEFAULT_CAPACITY;
}


// element access
char& lxc::String::operator[] (lxc::SizeType pos)
{
	assert_in_accessible_range(*this, pos, "String::operator[]");
	return this->_elements[pos];
}


// modifiers
lxc::String& lxc::String::operator+= (const lxc::String& str)
{ return this->append(str); }

lxc::String& lxc::String::operator+= (const char* cstr)
{ return this->append(cstr); }

lxc::String& lxc::String::operator+= (char c)
{ return this->append(1, c); }

lxc::String& lxc::String::append(const char* cstr, lxc::SizeType low, lxc::SizeType high)
{
	high = lxc::min_of_2(high, lxc::String::_cstr_len(cstr));
	while (this->_capacity <= this->_size + high - low + 1) { this->_expand(); }
	lxc::String::_cstr_copy(this->_elements + this->_size, cstr, low, high);
	this->_size += (high - low);

	return *this;
}

lxc::String& lxc::String::append(const char* cstr, lxc::SizeType n)
{ return this->append(cstr, 0, n); }

lxc::String& lxc::String::append(const char* cstr)
{ return this->append(cstr, 0, lxc::String::_cstr_len(cstr)); }

lxc::String& lxc::String::append(const lxc::String& str, lxc::SizeType low, lxc::SizeType high)
{ return this->append(str.elements(), low, high); }

lxc::String& lxc::String::append(const lxc::String& str)
{ return this->append(str, 0, str.size()); }

lxc::String& lxc::String::append(lxc::SizeType n, char c)
{
	if (this->_capacity <= this->_size + n) { this->_expand(); }
	while (n--) { this->_elements[this->_size++] = c; }
	this->_elements[this->_size] = '\0';

	return *this;
}

void lxc::String::push_back(char c) { this->append(1, c); }

lxc::String& lxc::String::assign(const char* cstr, lxc::SizeType low, lxc::SizeType high)
{
	delete[] this->_elements;
	this->_copy_from(cstr, low, high);
	return *this;
}

lxc::String& lxc::String::assign(const char* cstr, lxc::SizeType n)
{ return this->assign(cstr, 0, n); }

lxc::String& lxc::String::assign(const char* cstr)
{ return this->assign(cstr, 0, lxc::String::_cstr_len(cstr)); }

lxc::String& lxc::String::assign(lxc::SizeType n, char c)
{
	delete[] this->_elements;
	this->_copy_from(n, c);
	return *this;
}

lxc::String& lxc::String::assign(const lxc::String& str, lxc::SizeType low, lxc::SizeType high)
{ return this->assign(str.elements(), low, high); }

lxc::String& lxc::String::assign(const lxc::String& str)
{ return this->assign(str.elements()); }

lxc::String& lxc::String::insert(lxc::SizeType pos, const char* cstr, lxc::SizeType low, lxc::SizeType high)
{
	high = min_of_2(high, lxc::String::_cstr_len(cstr));
	const char* errmsg = "String::insert";
	assert_in_modified_range(*this, pos, errmsg);
	assert_in_accessible_range(String(cstr), low, errmsg);
	assert_in_modified_range(String(cstr), high, errmsg);

	SizeType new_capacity = 0;
	char* new_elements = new char[new_capacity = ((this->_size + high - low + 1) << 1)];
	String::_cstr_copy(new_elements, this->_elements, 0, pos);
	String::_cstr_copy(new_elements + pos, cstr, low, high);
	String::_cstr_copy(new_elements + pos + (high - low), this->_elements, pos, String::NPOS);
	SizeType new_size = this->_size + high - low;

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_capacity = new_capacity;
	this->_size = new_size;
	return *this;
}

lxc::String& lxc::String::insert(lxc::SizeType pos, const char* cstr)
{ return this->insert(pos, cstr, 0, String::NPOS); }

lxc::String& lxc::String::insert(lxc::SizeType pos, lxc::SizeType n, char c)
{ return this->insert(pos, String(n, c)); }

lxc::String& lxc::String::insert(lxc::SizeType pos, const lxc::String& str)
{ return this->insert(pos, str.elements()); }

lxc::String& lxc::String::insert(lxc::SizeType pos, const lxc::String& str, lxc::SizeType low, lxc::SizeType high)
{ return this->insert(pos, str.elements(), low, high); }

lxc::String& lxc::String::erase(lxc::SizeType low, lxc::SizeType high)
{
	high = lxc::min_of_2(high, this->_size);
	const char* errmsg = "String::erase";
	assert_in_accessible_range(*this, low, errmsg);
	assert_in_modified_range(*this, high, errmsg);

	lxc::String::_cstr_copy(this->_elements + low, this->_elements + high);
	this->_size -= (high - low);
	this->_elements[this->_size] = '\0';

	if (double(this->_size) / this->_capacity < lxc::String::SHRINK_RATIO) { this->_shrink(); }
	return *this;
}

lxc::String& lxc::String::replace(lxc::SizeType low1, lxc::SizeType high1, const char* cstr,
	lxc::SizeType low2, lxc::SizeType high2)
{
	high1 = lxc::min_of_2(high1, this->_size);
	high2 = lxc::min_of_2(high2, lxc::String::_cstr_len(cstr));
	const char* errmsg = "String::replace";
	assert_in_accessible_range(*this, low1, errmsg); assert_in_modified_range(*this, high1, errmsg);
	assert_in_accessible_range(String(cstr), low2, errmsg); assert_in_modified_range(String(cstr), high2, errmsg);

	lxc::SizeType new_size = this->_size - (high1 - low1) + (high2 - low2);
	lxc::SizeType new_capacity = 0;
	char* new_elements = new char[new_capacity = (new_size << 1)];

	lxc::String::_cstr_copy(new_elements, this->_elements, 0, low1);
	lxc::String::_cstr_copy(new_elements + low1, cstr, low2, high2);
	lxc::String::_cstr_copy(new_elements + low1 + (high2 - low2), this->_elements, high1, lxc::String::NPOS);

	delete[] this->_elements;
	this->_elements = new_elements;
	this->_capacity = new_capacity;
	this->_size = new_size;

	if (double(this->_size) / this->_capacity < lxc::String::SHRINK_RATIO) { this->_shrink(); }
	return *this;
}


lxc::String& lxc::String::replace(lxc::SizeType low, lxc::SizeType high, const char* cstr)
{ return this->replace(low, high, cstr, 0, lxc::String::_cstr_len(cstr)); }

lxc::String& lxc::String::replace(lxc::SizeType low, lxc::SizeType high, const char* cstr, lxc::SizeType n)
{ return this->replace(low, high, cstr, 0, n); }

lxc::String& lxc::String::replace(lxc::SizeType low, lxc::SizeType high, const lxc::String& str)
{ return this->replace(low, high, str.elements()); }

lxc::String& lxc::String::replace(lxc::SizeType low1, lxc::SizeType high1, const String& str,
	lxc::SizeType low2, lxc::SizeType high2)
{ return this->replace(low1, high1, str.elements(), low2, high2); }

lxc::String& lxc::String::replace(lxc::SizeType low, lxc::SizeType high, lxc::SizeType n, char c)
{ return this->replace(low, high, String(n, c)); }

lxc::SizeType lxc::String::copy(char* cstr, lxc::SizeType low, lxc::SizeType high)
{
	high = lxc::min_of_2(high, this->_size);
	const char* errmsg = "String::copy";
	assert_in_accessible_range(*this, low, errmsg);
	assert_in_modified_range(*this, high, errmsg);

	String::_cstr_copy(cstr, this->_elements, low, high);

	return high - low;
}

void lxc::String::swap(lxc::String& str) { lxc::swap(*this, str); }


// operations
lxc::String lxc::String::operator+(const String str) const
{
	String new_str(*this); new_str += str;
	return new_str;
}

lxc::String lxc::String::operator+(const char* cstr) const
{ return this->operator+(String(cstr)); }

lxc::String lxc::String::operator+(const char c) const
{ return this->operator+(String(1, c)); }


bool lxc::String::equals(const char* cstr) const { return _cstr_equal(_elements, cstr); }

bool lxc::String::equals(const String str) const
{
	if (this->_size != str.size()) { return false; }
	return _cstr_equal(_elements, str.elements());
}

lxc::SizeType lxc::String::find(const char* cstr, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	SizeType cstrlen = String::_cstr_len(cstr);
	if (high - low < cstrlen) { return NPOS; }

	for (SizeType pos = low; pos <= high - cstrlen; pos++) {
		bool match = true;
		for (SizeType pos2 = 0; pos2 < String::_cstr_len(cstr); pos2++) {
			if (cstr[pos2] != this->_elements[pos + pos2]) { match = false; break; }
		}
		if (match) { return pos; }
	}

	return NPOS;
}

lxc::SizeType lxc::String::find(const lxc::String& str, lxc::SizeType low, lxc::SizeType high) const
{ return find(str.elements(), low, high); }

lxc::SizeType lxc::String::find(char ch, lxc::SizeType low, lxc::SizeType high) const
{ return find(String(1, ch), low, high); }

lxc::SizeType lxc::String::rfind(const char* cstr, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	SizeType cstrlen = String::_cstr_len(cstr);
	if (high - low < cstrlen) { return NPOS; }

	for (SizeType pos = high - 1; pos >= low + cstrlen - 1; pos--) {
		bool match = true;
		for (SizeType pos2 = cstrlen - 1; pos2 >= 0; pos2--) {
			if (cstr[pos2] != this->_elements[pos - (cstrlen - 1 - pos2)]) { match = false; break; }
		}
		if (match) { return pos - cstrlen + 1; }
	}

	return NPOS;
}

lxc::SizeType lxc::String::rfind(const lxc::String& str, lxc::SizeType low, lxc::SizeType high) const
{ return rfind(str.elements(), low, high); }

lxc::SizeType lxc::String::rfind(char ch, lxc::SizeType low, lxc::SizeType high) const
{ return rfind(String(1, ch), low, high); }

lxc::SizeType lxc::String::find_first_of(const char* cstr, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	SizeType cstrlen = String::_cstr_len(cstr);
	for (SizeType pos = low; pos < high; pos++) {
		for (SizeType pos2 = 0; pos2 < cstrlen; pos2++) {
			if (this->_elements[pos] == cstr[pos2]) { return pos; }
		}
	}

	return NPOS;
}

lxc::SizeType lxc::String::find_first_of(const lxc::String& str, lxc::SizeType low, lxc::SizeType high) const
{ return find_first_of(str.elements(), low, high); }

lxc::SizeType lxc::String::find_first_of(char ch, lxc::SizeType low, lxc::SizeType high) const
{ return find_first_of(String(1, ch), low, high); }

lxc::SizeType lxc::String::find_last_of(const char* cstr, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	SizeType cstrlen = String::_cstr_len(cstr);
	for (SizeType pos = high - 1; pos >= low; pos--) {
		for (SizeType pos2 = 0; pos2 < cstrlen; pos2++) {
			if (this->_elements[pos] == cstr[pos2]) { return pos; }
		}
	}

	return NPOS;
}

lxc::SizeType lxc::String::find_last_of(const lxc::String& str, lxc::SizeType low, lxc::SizeType high) const
{ return find_last_of(str.elements(), low, high); }

lxc::SizeType lxc::String::find_last_of(char ch, lxc::SizeType low, lxc::SizeType high) const
{ return find_last_of(String(1, ch), low, high); }

lxc::SizeType lxc::String::find_first_not_of(const char* cstr, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	for (SizeType pos = low; pos < high; pos++) {
		if (this->find_first_of(cstr, pos, pos + 1) == NPOS) { return pos; }
	}

	return NPOS;
}

lxc::SizeType lxc::String::find_first_not_of(const lxc::String& str, lxc::SizeType low, lxc::SizeType high) const
{ return find_first_not_of(str.elements(), low, high); }

lxc::SizeType lxc::String::find_first_not_of(char ch, lxc::SizeType low, lxc::SizeType high) const
{ return find_first_not_of(String(1, ch), low, high); }

lxc::SizeType lxc::String::find_last_not_of(const char* cstr, lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	for (SizeType pos = high - 1; pos >= low; pos--) {
		if (this->find_last_of(cstr, pos, pos + 1) == NPOS) { return pos; }
	}

	return NPOS;
}

lxc::SizeType lxc::String::find_last_not_of(const lxc::String& str, lxc::SizeType low, lxc::SizeType high) const
{ return find_last_not_of(str.elements(), low, high); }

lxc::SizeType lxc::String::find_last_not_of(char ch, lxc::SizeType low, lxc::SizeType high) const
{ return find_last_not_of(String(1, ch), low, high); }

lxc::String lxc::String::substr(lxc::SizeType low, lxc::SizeType high) const
{
	high = lxc::min_of_2(high, this->_size);
	return String(*this, low, high);
}

lxc::Vector<lxc::String> lxc::String::split(const lxc::String& splitter) const
{
	Vector<String> res;
	SizeType prev = 0;
	while (prev < this->_size) {
		SizeType cur = this->find(splitter, prev);
		res.insert_back(this->substr(prev, cur));

		if (cur == String::NPOS) { break; }
		prev = cur + splitter.size();
	}

	return res;
}
