#include <iostream>
#include <cstdlib>

#include "UnitTest/TestVector.hpp"
#include "UnitTest/TestString.hpp"

#include "DataStructure/List.tpp"


int main()
{
	// run unit test
	test_vector();
	// test_string();

	int arr[5] = { 3,4,5,7,1 };
	lxc::List<int> list(arr, 0, 5);

	std::cout << "end." << std::endl;

	system("pause");
	return 0;
}