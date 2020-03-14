#include <iostream>
#include <cstdlib>

#include "Test/TestVector.hpp"
#include "Test/TestString.hpp"

using lxc::Vector;

int main()
{
	// run unit test
	test_vector();
	test_string();

	std::cout << "hello" << std::endl;

	system("pause");
	return 0;
}