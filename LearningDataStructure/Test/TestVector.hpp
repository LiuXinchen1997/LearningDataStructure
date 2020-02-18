/* unit test of Vector */
#pragma once
#include <iostream>
#include "../DataStructure/Vector.hpp"

void visit(int& ele) { std::cout << ele << " "; }

template <class T>
bool equal(lxc::Vector<T> v1, lxc::Vector<T> v2)
{ return v1 == v2; }

void test_vector()
{
	lxc::Vector<int> v1(10, 5, 2);

	std::cout << v1;
}