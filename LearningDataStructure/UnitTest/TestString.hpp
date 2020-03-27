/* unit test of String */

#pragma once

#include <iostream>
#include "../DataStructure/String.hpp"
#include "../General/Base.h"
#include "../Exception/AssertException.h"

void assert_string(bool ass)
{
}

void test_string_constructor()
{
	using std::cout;
	using std::endl;
	using lxc::String;
	
	String str;
	cout << str << endl;

	String str2("I love C++.", 2, 6);
	cout << str2 << endl;

	String str3("I love C++.");
	cout << str3 << endl;

	String str4(str3, 2, 6);
	cout << str4 << endl;

	String str5(str3);
	cout << str5 << endl;

	String str6(10, 'c');
	cout << str6 << endl;
}

void test_string_operator_equal()
{
	using std::cout;
	using std::endl;
	using lxc::String;

	lxc::String str;
	str = String("I love C++.");
	cout << str << endl;

	lxc::String str2;
	str2 = "I love C++.";
	cout << str2 << endl;

	lxc::String str3;
	str3 = 'c';
	cout << str3 << endl;
}

void test_string_resize()
{
	lxc::String str("I love C++.");
	str.resize(20, '.');
}

void test_string()
{
	try {
		test_string_constructor();
		test_string_operator_equal();
	}
	catch (lxc::AssertException e) {
		std::cerr << e.get_name() << " " << e.get_message() << std::endl;
	}
}