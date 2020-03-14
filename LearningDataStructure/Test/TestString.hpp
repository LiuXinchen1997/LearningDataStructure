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

	String str6(10, 'c');
	cout << str6 << endl;
}

void test_string()
{
	test_constructor();
}