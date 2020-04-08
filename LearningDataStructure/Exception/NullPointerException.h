#pragma once

#include "Exception.h"

namespace lxc {
	class NullPointerException :public Exception {
	public:
		NullPointerException(const char* message) :Exception("NullPointerException", message) {};
		NullPointerException(const String message) :Exception(String("NullPointerException"), message) {};
	};
};