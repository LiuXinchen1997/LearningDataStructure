#pragma once

#include <iostream>

#include "../DataStructure/String.h"
#include "../Exception/Exception.h"

namespace lxc {
	void print_exception(Exception e) { std::cerr << e << std::endl; }

	void unittest_template(const char* errmsg, void(*test_helper)(const char*), 
		void(*exception_catcher)(Exception) = print_exception)
	{
		try { test_helper(errmsg); }
		catch (Exception e) { exception_catcher(e); }
	}

	void unittest_template(const String errmsg, void(*test_helper)(const char*),
		void(*exception_catcher)(Exception) = print_exception)
	{ unittest_template(errmsg.elements(), test_helper, exception_catcher); }
};