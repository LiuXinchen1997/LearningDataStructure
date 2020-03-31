#pragma once

#include "../DataStructure/String.h"

namespace lxc {
	class Exception {
	protected:
		const String _name;
		const String _message;

	public:
		Exception(const char* name, const char* message) : _name(name), _message(message) {};
		Exception(const String name, const String message) : _name(name), _message(message) {};
		virtual const String get_name() { return _name; };
		virtual const String get_message() { return _message; };
	};
}
