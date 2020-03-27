#pragma once

namespace lxc {
	class Exception {
	protected:
		const char* _name;
		const char* _message;

	public:
		Exception(const char* name, const char* message) : _name(name), _message(message) {};
		virtual const char* get_name() { return _name; };
		virtual const char* get_message() = 0;
	};
}