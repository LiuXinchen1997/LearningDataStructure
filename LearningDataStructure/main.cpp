#include <iostream>
#include <cstdlib>

#include "Vector.h"

using namespace std;

int main()
{
	int a = 1;
	cout << MIN_OF_2(1.3,2.6) << endl;
	std::cout << "hello " << std::endl;
	int arr[5] = { 2,3,6,7,8 };
	Vector<int> v(arr, 0, 5);
	Vector<int> v2 = v;

	v2[1] = 3;
	try {
		std::cout << v2.search(3) << endl;
	}
	catch (const char* msg) {
		cout << msg << endl;
	}

	system("pause");
	return 0;
}