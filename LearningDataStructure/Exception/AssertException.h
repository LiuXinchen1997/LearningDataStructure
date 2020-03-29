#pragma once

#include "Exception.h"

namespace lxc {
	class AssertException :public Exception {
	public:
		AssertException(const char* message) :Exception("AssertException", message) {};
		AssertException(const String message) :Exception(String("AssertException"), message) {};
	};
};