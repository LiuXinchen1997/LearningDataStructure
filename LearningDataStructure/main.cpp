#include <iostream>
#include <cstdlib>

#include "UnitTest/TestVector.hpp"
#include "UnitTest/TestString.hpp"

using lxc::Vector;

int main()
{
	// run unit test
	// test_vector();
	test_string();

	std::cout << "end!" << std::endl;

	system("pause");
	return 0;
}