/* unit test of Vector */

#pragma once
#include <iostream>
#include <string>
#include "../DataStructure/Vector.hpp"

void visit(int& ele) { std::cout << ele << " "; }

template <class S>
bool equals(const S s1, const S s2) { return s1 == s2; }

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
	if (equals(v.reduce_to(vector_reduce_to_conventor), 21)) {
		std::cout << "vector reduce_to pass." << std::endl;
	}
	else {
		throw "vector reduce_to error.";
	}
}

void test_vector()
{
	try {
		test_vector_sort();
		test_vector_deduplicate();
		test_vector_uniquify();
		test_vector_operator_plus();
		test_vector_operator_plus_equal();
		test_vector_remove_if();
		test_vector_assign();
		test_vector_swap();
		test_vector_map_to();
		test_vector_reduce_to();
	}
	catch (const char* err_msg) {
		std::cerr << err_msg << std::endl;
	}
}