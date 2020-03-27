#pragma once

#include "Exception.h"

namespace lxc {
	class AssertException :public Exception {
	public:
		AssertException(const char* message) :Exception("AssertException", message) {};
		const char* get_message() { return _message; }
	};
};