/* declaration of String */

#pragma once
#include <iostream>
#include "../General/Base.h"

namespace lxc {
	class String
	{
	protected:
		static const SizeType DEFAULT_CAPACITY;
		static const SizeType NPOS;
		static const double SHRINK_RATIO;
		static SizeType _cstr_len(const char* cstr);
		static void _cstr_copy(char* dest, const char* source, SizeType low, SizeType high);
		static void _cstr_copy(char* dest, const char* source);
		static int _cstr_comp(const char* cstr1, const char* cstr2);
		static bool _cstr_equal(const char* cstr1, const char* cstr2);

		SizeType _size;
		SizeType _capacity;
		char* _elements;

		void _copy_from(const char* cstr, SizeType low, SizeType high);
		void _copy_from(SizeType n, char c);
		void _expand();
		void _shrink();

	public:
		// constructor
		explicit String();
		String(const char* cstr, SizeType low, SizeType high);
		String(const char* cstr);
		String(const String& str, SizeType low, SizeType high);
		String(const String& str);
		String(SizeType n, char c);
		String& operator= (const String& str);
		String& operator= (const char* cstr);
		String& operator= (char c);

		// deconstructor
		~String() { delete[] this->_elements; }

		// getter
		const char* c_str() const { return this->_elements; }
		SizeType size() const { return this->_size; }
		SizeType length() const { return this->size(); }
		SizeType capacity() const { return this->_capacity; }
		SizeType max_size() const { return this->NPOS; }

		// capacity
		void resize(SizeType new_size, char c = char());
		void reserve(SizeType new_capacity);
		void clear();
		bool empty() const { return (this->_size == 0); };

		// element access
		const char& operator[] (SizeType pos) const { return this->_elements[pos]; };
		char& operator[] (SizeType pos) { return this->_elements[pos]; };
		const char& at(SizeType pos) const { return this->operator[](pos); };
		char& at(SizeType pos) { return this->operator[](pos); };
		char get(SizeType pos) { return this->at(pos); }

		// modifiers
		String& operator+= (const String& str);
		String& operator+= (const char* cstr);
		String& operator+= (char c);
		String& append(const char* cstr, SizeType low, SizeType high);
		String& append(const char* cstr, SizeType n);
		String& append(const char* cstr);
		String& append(const String& str, SizeType low, SizeType high);
		String& append(const String& str);
		String& append(SizeType n, char c);
		void push_back(char c);
		String& assign(const char* cstr, SizeType low, SizeType high);
		String& assign(const char* cstr, SizeType n);
		String& assign(const char* cstr);
		String& assign(SizeType n, char c);
		String& assign(const String& str, SizeType low, SizeType high);
		String& assign(const String& str);
		String& insert(SizeType pos, const char* cstr, SizeType low, SizeType high);
		String& insert(SizeType pos, const char* cstr);
		String& insert(SizeType pos, SizeType n, char c);
		String& insert(SizeType pos, const String& str);
		String& insert(SizeType pos, const String& str, SizeType low, SizeType high);
		String& erase(SizeType low = 0, SizeType high = NPOS);
		String& replace(SizeType low1, SizeType high1, const char* cstr, SizeType low2, SizeType high2);
		String& replace(SizeType low, SizeType high, const char* cstr);
		String& replace(SizeType low, SizeType high, const char* cstr, SizeType n);
		String& replace(SizeType low, SizeType high, SizeType n, char c);
		String& replace(SizeType low, SizeType high, const String& str);
		String& replace(SizeType low1, SizeType high1, const String& str, SizeType low2, SizeType high2);
		SizeType copy(char* s, SizeType low, SizeType high);
		void swap(String& str);

		// operations
		bool operator==(const String str) const { return _cstr_equal(_elements, str.c_str()); }
		bool operator<(const String str) const { return _cstr_comp(_elements, str.c_str()) < 0; }
		bool operator<=(const String str) const { return _cstr_comp(_elements, str.c_str()) <= 0; }
		bool operator>(const String str) const { return _cstr_comp(_elements, str.c_str()) > 0; }
		bool operator>=(const String str) const { return _cstr_comp(_elements, str.c_str()) >= 0; }
		String operator+(const String str) const;
		String operator+(const char* cstr) const;
		String operator+(const char c) const;
	};
};
