/* unit test of Vector */

#pragma once
#include <iostream>
#include "../DataStructure/Vector.hpp"
#include "../General/Base.h"
#include "../General/Assert.h"
#include "../General/UnitTest.h"

void visit(int& ele) { std::cout << ele << " "; }

template <class T>
void assert_equals_vector(const lxc::Vector<T>& vec1, const lxc::Vector<T>& vec2, const lxc::String errmsg)
{ lxc::assert(vec1 == vec2, errmsg); }

template <class T>
void assert_equals_vector(const lxc::Vector<T>& vec, const T* arr, lxc::SizeType size, const lxc::String errmsg)
{ lxc::assert(vec.equals(arr, size), errmsg); }


// unittest example
void test_vector_constructor(const char* errmsg)
{
	using lxc::Vector;

	Vector<int> vec;
	lxc::assert(vec.capacity() == 3, errmsg);
	lxc::assert(vec.size() == 0, errmsg);

	Vector<int> vec2(10, 5, 10);
	int arr[5] = { 10, 10, 10, 10, 10 };
	assert_equals_vector(vec2, arr, 5, errmsg);

	int arr2[10] = { 5,3,2,5,8,5,2,5,88,11 };
	Vector<int> vec3(arr2, 2, 7);
	int _arr2[5] = { 2,5,8,5,2 };
	assert_equals_vector(vec3, _arr2, 5, errmsg);

	Vector<int> vec4(vec3);
	assert_equals_vector(vec4, vec3, errmsg);

	Vector<int> vec5(vec3, 2, 5);
	int _arr3[3] = { 8, 5, 2 };
	assert_equals_vector(vec5, _arr3, 3, errmsg);
}

void test_vector_resize(const char* errmsg)
{
	using lxc::Vector;

	int arr[6] = { 5, 4, 3, 1, 8, 9 };
	Vector<int> vec(arr, 6);

	vec.resize(4, 0);
	assert_equals_vector(vec, arr, 4, errmsg);

	vec.resize(8, 0);
	int _arr[8] = { 5,4,3,1,0,0,0,0 };
	assert_equals_vector(vec, _arr, 8, errmsg);
}

void test_vector_reserve(const char* errmsg)
{
	using lxc::Vector;

	int arr[6] = { 5, 4, 3, 1, 8, 9 };
	Vector<int> vec(arr, 6);
	
	vec.reserve(4);
	assert_equals_vector(vec, arr, 6, errmsg);

	vec.reserve(20);
	assert_equals_vector(vec, arr, 6, errmsg);
	lxc::assert(vec.capacity() == 20, errmsg);
}

void test_vector_get(const char* errmsg)
{
	using lxc::Vector;

	int arr[6] = { 6,3,5,8,1,3 };
	Vector<int> vec(arr, 6);
	lxc::assert(vec.get(0) == 6, errmsg);
	lxc::assert(vec.get(1) == 3, errmsg);
	lxc::assert(vec.get(2) == 5, errmsg);
	lxc::assert(vec.get(3) == 8, errmsg);
	lxc::assert(vec.get(5) == 3, errmsg);
}

void test_vector_front(const char* errmsg)
{
	using lxc::Vector;

	int arr[6] = { 6,3,5,8,1,3 };
	Vector<int> vec(arr, 6);
	lxc::assert(vec.front() == 6, errmsg);
}

void test_vector_back(const char* errmsg)
{
	using lxc::Vector;

	int arr[6] = { 6,3,5,8,1,3 };
	Vector<int> vec(arr, 6);
	lxc::assert(vec.back() == 3, errmsg);
}

void test_vector_find(const char* errmsg)
{
	using lxc::Vector;

	int arr[7] = { 6,3,5,8,1,9,3 };
	Vector<int> vec(arr, 7);
	lxc::assert(vec.find(6) == 0, errmsg);
	lxc::assert(vec.find(3) == 1, errmsg);
	lxc::assert(vec.find(9) == 5, errmsg);
	lxc::assert(vec.find(3, 4, lxc::NPOS) == 6, errmsg);
	lxc::assert(vec.find(9, 0, 3) == lxc::NPOS, errmsg);
	lxc::assert(vec.find(100) == lxc::NPOS, errmsg);
}

void test_vector_search(const char* errmsg)
{
	using lxc::Vector;

	int arr[6] = { 6,3,5,8,1,9 };
	Vector<int> vec(arr, 6);
	lxc::assert(vec.search(6) == lxc::NPOS, errmsg);

	int arr2[6] = { 4, 5, 6, 7, 7, 9 };
	Vector<int> vec2(arr2, 6);
	lxc::assert(vec2.search(4) == 0, errmsg);
	lxc::assert(vec2.search(9) == 5, errmsg);
	lxc::assert(vec2.search(5) == 1, errmsg);
	lxc::assert(vec2.search(7) == 3, errmsg);
	lxc::assert(vec2.search(100) == lxc::NPOS, errmsg);
	lxc::assert(vec2.find(7, 4, lxc::NPOS) == 4, errmsg);
}



/*
void test_vector_merge_sort()
{
	int arr[6] = { 5, 3, 7, 1, 9, 6 };
	lxc::Vector<int> v(arr, 6);
	std::cout << v << std::endl;

	v.sort("merge", 0, v.size());
	std::cout << v << std::endl;

	int sorted_arr[6] = { 1, 3, 5, 6, 7, 9 };
	if (!equals(v, sorted_arr, 6)) { throw "merge sort error."; }
}

void test_vector_quick_sort()
{
	int arr[6] = { 5, 3, 7, 1, 9, 6 };
	lxc::Vector<int> v(arr, 6);
	std::cout << v << std::endl;

	v.sort("quick", 0, v.size());
	std::cout << v << std::endl;

	int sorted_arr[6] = { 1, 3, 5, 6, 7, 9 };
	if (!equals(v, sorted_arr, 6)) { throw "quick sort error."; }
}

void test_vector_sort()
{
	const lxc::SizeType SORTNUM = 6;

	std::string sort_names[SORTNUM] 
		= { "bubble", "insert", "select", "heap", "merge", "quick" };
	int arr[6] = { 5, 3, 7, 1, 9, 6 };
	int sorted_arr[6] = { 1, 3, 5, 6, 7, 9 };
	lxc::Vector<int> v(arr, 6);
	for (lxc::SizeType i = 0; i < SORTNUM; i++) {
		v.unsort(0, v.size());
		v.sort(sort_names[i].c_str(), 0, v.size());
		if (!equals(v, sorted_arr, 6)) { 
			throw std::string("vector ") + sort_names[i] + " sort error."; 
		}
		else { std::cout << "vector " << sort_names[i] + " sort pass." << std::endl; }
	}
}

void test_vector_deduplicate()
{
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v(arr, 6);
	
	v.deduplicate();
	int _arr[4] = { 2, 4, 6, 5 };
	if (!equals(v, _arr, 4)) { throw "vector deduplicate error."; }
	else { std::cout << "vector deduplicate pass." << std::endl; }
}

void test_vector_uniquify()
{
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v(arr, 6);
	
	v.sort("quick", 0, v.size());
	v.uniquify();
	int _arr[4] = { 2, 4, 5, 6 };
	if (!equals(v, _arr, 4)) { throw "vector uniquify error."; }
	else { std::cout << "vector uniquify pass." << std::endl; }
}

void test_vector_operator_plus()
{
	int arr[3] = { 2, 4, 6};
	lxc::Vector<int> v1(arr, 3);
	
	int arr2[3] = { 2, 4, 5 };
	lxc::Vector<int> v2(arr2, 3);
	
	int arr3[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v3 = v1 + v2;
	if (!equals(v3, arr3, 6)) { throw "vector operator+ error."; }
	else { std::cout << "vector operator+ pass." << std::endl; }
}

void test_vector_operator_plus_equal()
{
	int arr[3] = { 2, 4, 6 };
	lxc::Vector<int> v1(arr, 3);
	
	int arr2[3] = { 2, 4, 5 };
	lxc::Vector<int> v2(arr2, 3);
	
	int arr3[6] = { 2, 4, 6, 2, 4, 5 };
	v1 += v2;
	if (!equals(v1, arr3, 6)) { throw "vector operator+= error."; }
	else { std::cout << "vector operator+= pass." << std::endl; }
}

bool vector_vector_remove_if_filter(const int ele) { return (ele <= 4) ? true : false; }

void test_vector_remove_if()
{
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v(arr, 6);

	v.remove_if(vector_vector_remove_if_filter);
	int _arr[] = { 6, 5 };
	if (equals(v, _arr, 2)) { std::cout << "vector remove_if pass." << std::endl; }
	else { throw "vector remove_if error."; }
}

void test_vector_assign()
{
	lxc::Vector<int> v;
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	v.assign(arr, 6);

	if (equals(v, arr, 6)) { std::cout << "vector assign pass." << std::endl; }
	else { throw "vector assign error."; }
}

void test_vector_swap()
{
	int arr[] = { 2, 5, 3, 7, 7 };
	int arr2[] = { 4, 1, 7, 9, 4, 2 };
	lxc::Vector<int> v(arr, 5);
	lxc::Vector<int> v2(arr2, 6);

	v.swap(v2);

	if (equals(v, arr2, 6) && equals(v2, arr, 5)) { std::cout << "vector swap pass." << std::endl; }
	else { throw "vector swap error."; }
}

int vector_map_to_convertor(int ele) { return ele * 2; }

void test_vector_map_to()
{
	int arr[] = { 5, 3, 4, 2, 8, 9, 7 };
	lxc::Vector<int> v(arr, 7);

	lxc::Vector<int> v2 = v.map_to(vector_map_to_convertor);
	int _arr[] = { 10, 6, 8, 4, 16, 18, 14 };
	if (equals(v2, _arr, 7)) { std::cout << "vector map_to pass." << std::endl; }
	else { throw "vector map_to error."; }
}

int vector_reduce_to_conventor(const int ele1, const int ele2) { return ele1 + ele2; }

void test_vector_reduce_to()
{
	int arr[] = { 5, 2, 6, 3, 5 };
	lxc::Vector<int> v(arr, 5);
	if (lxc::equals(v.reduce_to(vector_reduce_to_conventor), 21)) {
		std::cout << "vector reduce_to pass." << std::endl;
	}
	else {
		throw "vector reduce_to error.";
	}
}
*/

void test_vector()
{
	using lxc::unittest_template;

	try {
		lxc::String errmsg = "unittest failed: Vector::";
		unittest_template(errmsg + "Vector", test_vector_constructor);
		unittest_template(errmsg + "resize", test_vector_resize);
		unittest_template(errmsg + "reserve", test_vector_reserve);
		unittest_template(errmsg + "get", test_vector_get);
		unittest_template(errmsg + "front", test_vector_front);
		unittest_template(errmsg + "back", test_vector_back);
		unittest_template(errmsg + "find", test_vector_find);
		unittest_template(errmsg + "search", test_vector_search);
	}
	catch (const char* err_msg) {
		std::cerr << err_msg << std::endl;
	}
}
