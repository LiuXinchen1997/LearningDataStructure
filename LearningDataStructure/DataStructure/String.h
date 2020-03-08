/* declaration of Vector */

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
		static SizeType cstrlen(char* cstr);

		SizeType _size;
		SizeType _capacity;
		char* _elements;

	public:
		explicit String();
		String(const String& str);
		String(const String& str, SizeType low, SizeType high);
		String(const char* cstr, SizeType low, SizeType high);
		String(const char* cstr);
		String(SizeType n, char c);

	private:

	};
};