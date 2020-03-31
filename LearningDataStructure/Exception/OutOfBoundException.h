#pragma once

#include "Exception.h"

namespace lxc {
	class OutOfBoundException :public Exception {
	public:
		OutOfBoundException(const char* message) :Exception("OutofBoundException", message) {};
		OutOfBoundException(const String message) :Exception(String("OutofBoundException"), message) {};
	};
};