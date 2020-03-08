/* declaration of Vector */
#pragma once
#include <iostream>
#include <climits>
#include "../General/Base.h"

namespace lxc {
	class String
	{
	protected:
		static const SizeType npos = INT_MAX;
		SizeType _size;
		SizeType _capacity;
		char* _elements;

	public:
		explicit String();
		String(const String& str);
		String(const String& str, SizeType low, SizeType high);
		String(const char* s, SizeType low, SizeType high);
		String(const char* s);
		String(SizeType n, char c);

	private:

	};
};