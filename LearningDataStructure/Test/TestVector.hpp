/* unit test of Vector */
#pragma once
#include <iostream>
#include "../DataStructure/Vector.hpp"

void visit(int& ele) { std::cout << ele << " "; }

template <class T>
bool equals(const lxc::Vector<T> v1, const lxc::Vector<T> v2)
{ return v1 == v2; }

template <class T>
bool equals(const lxc::Vector<T>& v, const T* arr, SizeType size)
{ return v.equals(arr, size); }

void test_vector_merge_sort()
{
	int arr[6] = { 5, 3, 7, 1, 9, 6 };
	lxc::Vector<int> v(arr, 6);
	std::cout << v << std::endl;

	v.sort(0, v.size(), "merge");
	std::cout << v << std::endl;

	int sorted_arr[6] = { 1, 3, 5, 6, 7, 9 };
	if (!equals(v, sorted_arr, 6)) { throw "merge sort error."; }
}

void test_vector_quick_sort()
{
	int arr[6] = { 5, 3, 7, 1, 9, 6 };
	lxc::Vector<int> v(arr, 6);
	std::cout << v << std::endl;

	v.sort(0, v.size(), "quick");
	std::cout << v << std::endl;

	int sorted_arr[6] = { 1, 3, 5, 6, 7, 9 };
	if (!equals(v, sorted_arr, 6)) { throw "quick sort error."; }
}

void test_vector()
{
	try {
		test_vector_merge_sort();
		test_vector_quick_sort();
	}
	catch (const char* err_msg) {
		std::cerr << err_msg << std::endl;
	}
}