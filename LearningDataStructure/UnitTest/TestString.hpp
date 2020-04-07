/* unit test of String */

#pragma once

#include <iostream>
#include "../DataStructure/String.hpp"
#include "../General/Base.h"
#include "../General/Assert.h"
#include "../Exception/Exception.h"
#include "../Exception/AssertException.h"
#include "../Exception/OutOfRangeException.h"

void assert_string(bool ass, const char* message)
{ lxc::assert(ass, message); }

void assert_equals_string(const lxc::String& str, const char* cstr, const char* message)
{ assert_string(str == cstr, message); }

void assert_equals_string(const lxc::String& s1, const lxc::String& s2, const char* message)
{ assert_string(s1 == s2, message); }


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

void test_string_operator_assign()
{
	const char* errmsg = "unittest failed: String::operator=";
	using lxc::String;

	try {
		String str1("abcde");
		String str2;

		str2 = str1;
		assert_equals_string(str2, "abcde", errmsg);

		str2 = "aaaaa";
		assert_equals_string(str2, "aaaaa", errmsg);

		str2 = 'a';
		assert_equals_string(str2, "a", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_resize()
{
	const char* errmsg = "unittest failed: String::resize";
	using lxc::String;

	try {
		String str("abcdefg");
		
		str.resize(5);
		assert_equals_string(str, "abcde", errmsg);

		str.resize(10, 'a');
		assert_equals_string(str, "abcdeaaaaa", errmsg);

		str.resize(1, 'a');
		assert_equals_string(str, "a", errmsg);

		str.resize(20, 'a');
		assert_equals_string(str, "aaaaaaaaaaaaaaaaaaaa", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_reserve()
{
	const char* errmsg = "unittest failed: String::reserve";
	using lxc::String;

	try {
		String str("abcdefg");
		str.reserve(80);
		lxc::assert_equals(str.capacity(), lxc::SizeType(80), errmsg);
		assert_equals_string(str, "abcdefg", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_clear()
{
	const char* errmsg = "unittest failed: String::clear";
	using lxc::String;

	try {
		String str("abcdefg");
		str.clear();
		String str2;
		assert_equals_string(str, str2, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_operator_at()
{
	const char* errmsg = "unittest failed: String::operator[]";
	using lxc::String;

	try {
		String str("abcdefg");

		lxc::assert_equals(str[0], 'a', errmsg);
		lxc::assert_equals(str[str.size() - 1], 'g', errmsg);
		lxc::assert_equals(str[2], 'c', errmsg);

		str[2] = 'b';
		assert_equals_string(str, "abbdefg", errmsg);

		str[20] = 'c';
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
	catch (lxc::OutOfRangeException e) {
		// std::cerr << e << std::endl;
	}
}

void test_string_operator_plus_equals()
{
	const char* errmsg = "unittest failed: String::operator+=";
	using lxc::String;

	try {
		String str;

		str += "abc";
		assert_equals_string(str, "abc", errmsg);

		str += String("de");
		assert_equals_string(str, "abcde", errmsg);

		str += 'f';
		assert_equals_string(str, "abcdef", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_append()
{
	const char* errmsg = "unittest failed: String::append";
	using lxc::String;

	try {
		String str;
		str.append("abcdef", 0, String::NPOS);
		assert_equals_string(str, "abcdef", errmsg);

		str.append("abcdef", 3, 5);
		assert_equals_string(str, "abcdefde", errmsg);

		str.append("abcdef");
		assert_equals_string(str, "abcdefdeabcdef", errmsg);

		str.clear();
		String str2("I love C++");
		str.append(str2);
		assert_equals_string(str, "I love C++", errmsg);

		str.append(str2, 6, String::NPOS);
		assert_equals_string(str, "I love C++ C++", errmsg);

		str.append(3, 'a');
		assert_equals_string(str, "I love C++ C++aaa", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_push_back()
{
	const char* errmsg = "unittest failed: String::push_back";
	using lxc::String;

	try {
		String str("abcdef");
		str.push_back('g');
		assert_equals_string(str, "abcdefg", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_assign()
{
	const char* errmsg = "unittest failed: String::assign";
	using lxc::String;

	try {
		String str("abcdef");
		str.assign("I love C++");
		assert_equals_string(str, "I love C++", errmsg);

		str.assign("I love C++", 2, String::NPOS);
		assert_equals_string(str, "love C++", errmsg);

		str.assign("I love C++", 2, 6);
		assert_equals_string(str, "love", errmsg);

		str.assign(5, 'a');
		assert_equals_string(str, "aaaaa", errmsg);

		String str2("I love programming");
		str.assign(str2);
		assert_equals_string(str, "I love programming", errmsg);

		str.assign(str2, 2, 6);
		assert_equals_string(str, "love", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_insert()
{
	const char* errmsg = "unittest failed: String::insert";
	using lxc::String;

	try {
		String str("I like ");
		str.insert(2, "don't ");
		assert_equals_string(str, "I don't like ", errmsg);

		str.insert(str.size(), "C++", 0, String::NPOS);
		assert_equals_string(str, "I don't like C++", errmsg);

		str = " like";
		str.insert(0, "Ann and Jack", 8, String::NPOS);
		assert_equals_string(str, "Jack like", errmsg);

		str.insert(str.size(), String(" C++"));
		assert_equals_string(str, "Jack like C++", errmsg);

		str.insert(5, String("I don't like"), 2, 8);
		assert_equals_string(str, "Jack don't like C++", errmsg);

		str.insert(0, 3, 'a');
		assert_equals_string(str, "aaaJack don't like C++", errmsg);

		str.insert(-1, 4, 'b');
		str.insert(0, "abcdefg", -5, String::NPOS);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
	catch (lxc::OutOfRangeException e) {
		// std::cerr << e << std::endl;
	}
}

void test_string_erase()
{
	const char* errmsg = "unittest failed: String::errse";
	using lxc::String;

	try {
		String str("abcdefg");
		str.erase(0, 1);
		assert_equals_string(str, "bcdefg", errmsg);

		str.erase(str.size() - 1);
		assert_equals_string(str, "bcdef", errmsg);

		str.erase(1, 3);
		assert_equals_string(str, "bef", errmsg);

		str.erase(2, 2);
		assert_equals_string(str, "bef", errmsg);

		str.erase();
		assert_equals_string(str, "", errmsg);

		str.erase(-5);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
	catch (lxc::OutOfRangeException e) {
		// std::cerr << e << std::endl;
	}
}

void test_string_replace()
{
	const char* errmsg = "unittest failed: String::replace";
	using lxc::String;

	try {
		String str("I like C++");
		str.replace(0, 1, "Jack, Tom and Lily", 6, 9);
		assert_equals_string(str, "Tom like C++", errmsg);

		str.replace(9, String::NPOS, "Java");
		assert_equals_string(str, "Tom like Java", errmsg);

		str.replace(0, 3, "Jack, Tom and Lily", 4);
		assert_equals_string(str, "Jack like Java", errmsg);

		str.replace(0, 4, 3, 'A');
		assert_equals_string(str, "AAA like Java", errmsg);

		str.replace(0, 3, String("Lily"));
		assert_equals_string(str, "Lily like Java", errmsg);

		str.replace(10, String::NPOS, "Use Python", 4, String::NPOS);
		assert_equals_string(str, "Lily like Python", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
	catch (lxc::OutOfRangeException e) {}
}

void test_string_copy()
{
	const char* errmsg = "unittest failed: String::copy";
	using lxc::String;

	try {
		String str("I love you.");
		char buf[20];
		str.copy(buf);
		assert_equals_string(str, buf, errmsg);

		str.copy(buf, 2, 6);
		assert_equals_string(String("love"), buf, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
	catch (lxc::OutOfRangeException e) {}
}

void test_string_swap()
{
	const char* errmsg = "unittest failed: String::swap";
	using lxc::String;

	try {
		String str("Andy");
		String str2("Tom");
		str.swap(str2);
		assert_equals_string(str, "Tom", errmsg);
		assert_equals_string(str2, "Andy", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_operator_more_less_equals()
{
	const char* errmsg = "unittest failed: String::operator< <= > >= == !=";
	using lxc::String;

	try {
		String str("Andy");
		String str2("Anda");
		assert_string(str > str2, errmsg);
		assert_string(str >= "Aadd", errmsg);

		assert_string(str2 < str, errmsg);
		assert_string(str2 <= "Dndy", errmsg);

		assert_string(str == "Andy", errmsg);
		assert_string(str != "Anda", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_find()
{
	const char* errmsg = "unittest failed: String::find";
	using lxc::String;

	try {
		String str("I love programming.");

		lxc::assert_equals(str.find(String("love")), 2, errmsg);
		lxc::assert_equals(str.find("love", 1), 2, errmsg);
		lxc::assert_equals(str.find('p', 5, 10), 7, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_rfind()
{
	const char* errmsg = "unittest failed: String::rfind";
	using lxc::String;

	try {
		String str("abcdefabcdef.");

		lxc::assert_equals(str.rfind(String("abc")), 6, errmsg);
		lxc::assert_equals(str.rfind("cde", 2, 20), 8, errmsg);
		lxc::assert_equals(str.rfind('e'), 10, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_find_first_of()
{
	const char* errmsg = "unittest failed: String::find_first_of";
	using lxc::String;

	try {
		String str("abcdefabcdef.");

		lxc::assert_equals(str.find_first_of("ed"), 3, errmsg);
		lxc::assert_equals(str.find_first_of('c'), 2, errmsg);
		lxc::assert_equals(str.find_first_of("I love programming", 7), 10, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_find_last_of()
{
	const char* errmsg = "unittest failed: String::find_last_of";
	using lxc::String;

	try {
		String str("abcdefabcdef.");

		lxc::assert_equals(str.find_last_of("ed"), 10, errmsg);
		lxc::assert_equals(str.find_last_of('c'), 8, errmsg);
		lxc::assert_equals(str.find_last_of("I love programming", 7), 10, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_find_first_not_of()
{
	const char* errmsg = "unittest failed: String::find_first_not_of";
	using lxc::String;

	try {
		String str("abcdefabcdef.");

		lxc::assert_equals(str.find_first_not_of("ed"), 0, errmsg);
		lxc::assert_equals(str.find_first_not_of("abcdef."), String::NPOS, errmsg);
		lxc::assert_equals(str.find_first_not_of("I love programming"), 1, errmsg);
		lxc::assert_equals(str.find_first_not_of("I love programming", 7), 7, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_find_last_not_of()
{
	const char* errmsg = "unittest failed: String::find_last_not_of";
	using lxc::String;

	try {
		String str("abcdefabcdef.");

		lxc::assert_equals(str.find_last_not_of("ed"), 12, errmsg);
		lxc::assert_equals(str.find_last_not_of("abcdef."), String::NPOS, errmsg);
		lxc::assert_equals(str.find_last_not_of("I love programming."), 11, errmsg);
		lxc::assert_equals(str.find_last_not_of("I love programming.", 7), 11, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_substr()
{
	const char* errmsg = "unittest failed: String::substr";
	using lxc::String;

	try {
		String str("abcdef");

		assert_equals_string(str.substr(2), "cdef", errmsg);
		assert_equals_string(str.substr(2, 4), "cd", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_split()
{
	const char* errmsg = "unittest failed: String::split";
	using lxc::String;

	try {
		String str("ab,,cd,,ef,,gg,,");

		assert_equals_string(str.split(",,")[0], "ab", errmsg);
		assert_equals_string(str.split(",,")[3], "gg", errmsg);

		str = "hello my name is Tom";
		assert_equals_string(str.split(' ')[0], "hello", errmsg);
		assert_equals_string(str.split(' ')[1], "my", errmsg);
		assert_equals_string(str.split(' ')[2], "name", errmsg);
		assert_equals_string(str.split(' ')[3], "is", errmsg);
		assert_equals_string(str.split(' ')[4], "Tom", errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}

void test_string_compare()
{
	const char* errmsg = "unittest failed: String::compare";
	using lxc::String;

	try {
		String str("abcdef");
		assert_string(str.compare("abcdeg") < 0, errmsg);
		assert_string(str.compare("abcdef") == 0, errmsg);
		assert_string(str.compare("abcdee") > 0, errmsg);

		assert_string(str.compare(2, String::NPOS, "abcdee", 1, 5) > 0, errmsg);
		assert_string(str.compare(1, 5, "abcdef", 1, 5) == 0, errmsg);
		assert_string(str.compare(2, String::NPOS, "abcdef", 2, 5) > 0, errmsg);
	}
	catch (lxc::AssertException e) {
		std::cerr << e << std::endl;
	}
}


void test_string()
{
	test_string_constructor();
	test_string_operator_assign();
	test_string_resize();
	test_string_reserve();
	test_string_clear();
	test_string_operator_at();
	test_string_operator_plus_equals();
	test_string_append();
	test_string_push_back();
	test_string_assign();
	test_string_insert();
	test_string_erase();
	test_string_replace();
	test_string_copy();
	test_string_swap();
	test_string_operator_more_less_equals();
	test_string_find();
	test_string_rfind();
	test_string_find_first_of();
	test_string_find_last_of();
	test_string_find_first_not_of();
	test_string_find_last_not_of();
	test_string_substr();
	test_string_split();
	test_string_compare();

	return;
}
