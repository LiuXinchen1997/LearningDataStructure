#include <iostream>
#include <cstdlib>

#include "Test/TestVector.hpp"

using namespace std;

void visit(int& ele) { cout << ele << " "; }

int main()
{
	test_vector();

	system("pause");
	return 0;
}