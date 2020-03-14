#pragma once

#include <iostream>
#include "../DataStructure/String.hpp"

void test_constructor()
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

	String str6('c', 10);
	cout << str6 << endl;
}

void test_operator_equal()
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

void test_string()
{
	test_constructor();
	test_operator_equal();
}