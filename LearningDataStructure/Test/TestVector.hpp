/* unit test of Vector */

#pragma once
#include <iostream>
#include <string>
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
	const SizeType SORTNUM = 6;

	std::string sort_names[SORTNUM] 
		= { "bubble", "insert", "select", "heap", "merge", "quick" };
	int arr[6] = { 5, 3, 7, 1, 9, 6 };
	int sorted_arr[6] = { 1, 3, 5, 6, 7, 9 };
	lxc::Vector<int> v(arr, 6);
	for (SizeType i = 0; i < SORTNUM; i++) {
		v.unsort(0, v.size());
		v.sort(sort_names[i].c_str(), 0, v.size());
		if (!equals(v, sorted_arr, 6)) { 
			throw sort_names[i] + " sort error."; 
		}
		else { std::cout << sort_names[i] + " sort pass." << std::endl; }
	}
}

void test_vector_deduplicate()
{
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v(arr, 6);
	
	v.deduplicate();
	int _arr[4] = { 2, 4, 6, 5 };
	if (!equals(v, _arr, 4)) { throw "deduplicate error."; }
	else { std::cout << "deduplicate pass." << std::endl; }
}

void test_vector_uniquify()
{
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v(arr, 6);
	
	v.sort("quick", 0, v.size());
	v.uniquify();
	int _arr[4] = { 2, 4, 5, 6 };
	if (!equals(v, _arr, 4)) { throw "uniquify error."; }
	else { std::cout << "uniquify pass." << std::endl; }
}

void test_operator_plus()
{
	int arr[3] = { 2, 4, 6};
	lxc::Vector<int> v1(arr, 3);
	
	int arr2[3] = { 2, 4, 5 };
	lxc::Vector<int> v2(arr2, 3);
	
	int arr3[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v3 = v1 + v2;
	if (!equals(v3, arr3, 6)) { throw "operator+ error."; }
	else { std::cout << "operator+ pass." << std::endl; }
}

void test_operator_plus_equal()
{
	int arr[3] = { 2, 4, 6 };
	lxc::Vector<int> v1(arr, 3);
	
	int arr2[3] = { 2, 4, 5 };
	lxc::Vector<int> v2(arr2, 3);
	
	int arr3[6] = { 2, 4, 6, 2, 4, 5 };
	v1 += v2;
	if (!equals(v1, arr3, 6)) { throw "operator+= error."; }
	else { std::cout << "operator+= pass." << std::endl; }
}

bool filter(int& ele) { return (ele <= 4) ? true : false; }

void test_remove_if()
{
	int arr[6] = { 2, 4, 6, 2, 4, 5 };
	lxc::Vector<int> v(arr, 6);

	v.remove_if(filter);
	int _arr[] = { 6, 5 };
	if (equals(v, _arr, 2)) { std::cout << "remove_if pass." << std::endl; }
	else { throw "remove_if error."; }
}

void test_vector()
{
	try {
		test_vector_sort();
		test_vector_deduplicate();
		test_vector_uniquify();
		test_operator_plus();
		test_operator_plus_equal();
		test_remove_if();
	}
	catch (const char* err_msg) {
		std::cerr << err_msg << std::endl;
	}
}