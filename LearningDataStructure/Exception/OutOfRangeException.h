#pragma once

#include "Exception.h"

namespace lxc {
	class OutOfRangeException :public Exception {
	public:
		OutOfRangeException(const char* message) :Exception("OutofBoundException", message) {};
		OutOfRangeException(const String message) :Exception(String("OutofBoundException"), message) {};
	};
};