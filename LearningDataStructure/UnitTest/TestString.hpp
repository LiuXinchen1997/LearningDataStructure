/* unit test of String */

#pragma once

#include <iostream>
#include "../DataStructure/String.hpp"
#include "../General/Base.h"
#include "../General/Assert.h"
#include "../Exception/AssertException.h"

void assert_string(bool ass, const char* message)
{ lxc::assert(ass, message); }

void assert_equals_string(lxc::String& str, const char* cstr, const char* message)
{ assert_string(str == cstr, message); }

void assert_equals_string(lxc::String& str1, lxc::String& str2, const char* message)
{ assert_string(str1 == str2, message); }


// unittest example
void test_string_constructor()
{
	const char* errmsg = "unittest failed: String::String";
	using lxc::String;

	try {
		String str1;
		lxc::assert(str1.capacity() == String::DEFAULT_CAPACITY, errmsg);
		lxc::assert(str1.size() == 0, errmsg);

		String str2("I love C++.", 2, 6);
		assert_equals_string(str2, "love", errmsg);

		String str3("I love C++.");
		assert_equals_string(str3, "I love C++.", errmsg);

		String str4(str3, 2, 6);
		assert_equals_string(str4, "love", errmsg);

		String str5(str3);
		assert_equals_string(str5, "I love C++.", errmsg);

		String str6(3, 'c');
		assert_equals_string(str6, "ccc", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_operator_equals()
{
	const char* errmsg = "unittest failed: String::operator==";
	using lxc::String;

	try {
		lxc::String str1("abcdefg");
		lxc::String str2("abcdefg");
		assert_string(str1 == str2, errmsg);

		lxc::String str3("abcdefh");
		assert_string(!(str1 == str3), errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string()
{
	test_string_constructor();
	test_string_operator_equals();
	//test_string_operator_plus();
}