#include <iostream>
#include <cstdlib>

#include "Vector.h"

using namespace std;

void visit(int& ele) { cout << ele << " "; }

int main()
{
	int arr[8] = { 2,3,8,7,6 };
	Vector<int> v(arr, 0, 5);
	Vector<int> v2 = v;

	v2.traverse(visit);
	cout << endl;

	v2.sort(0, 5, "heap");
	v2.traverse(visit);
	cout << endl;

	system("pause");
	return 0;
}