#pragma once

#include "Base.h"
#include "../Exception/AssertException.h"
#include "../Exception/OutOfBoundException.h"

namespace lxc {
	void assert(bool ass, const char* errmsg = "") { if (!ass) { throw AssertException(errmsg); } }
	
	template <class S> void assert_equals(const S s1, const S s2, const char* errmsg = "")
	{ assert(equals(s1, s2), errmsg); }

	template <class Array> void assert_in_bound(const Array& array, SizeType pos, const char* errmsg = "")
	{ if (pos < 0 || pos >= array.size()) { throw OutOfBoundException(errmsg); } }
}