/* declaration of String */

#pragma once
#include <iostream>
#include <climits>
#include "../General/Base.h"

namespace lxc {
	class String
	{
	protected:
		static const SizeType DEFAULT_CAPACITY = 3;
		static const SizeType NPOS = INT_MAX;
		static SizeType _cstr_len(const char* cstr);

		SizeType _size;
		SizeType _capacity;
		char* _elements;

		void _copy_from(const char* cstr, SizeType low, SizeType high);

	public:
		// constructor
		explicit String();
		String(const char* cstr, SizeType low, SizeType high);
		String(const char* cstr);
		String(const String& str, SizeType low, SizeType high);
		String(const String& str);
		String(SizeType n, char c);

		// deconstructor
		~String() { delete[] this->_elements; }

		// getter
		const char* c_str() const { return this->_elements; }
		SizeType size() const { return this->_size; }
		SizeType length() const { return this->size(); }
		SizeType capacity() const { return this->_capacity; }
	};
};
