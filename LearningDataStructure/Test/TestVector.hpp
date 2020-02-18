/* unit test of Vector */

#include <iostream>
#include "./DataStructure/Vector.hpp"

void visit(int& ele) { std::cout << ele << " "; }

template <class T>
bool equal(Vector<T> v1, Vector<T> v2)
{ return v1 == v2; }

void test_vector()
{
	Vector<int> v1;
}