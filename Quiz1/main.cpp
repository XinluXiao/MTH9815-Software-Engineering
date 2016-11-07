#include<iostream>
#include<vector>
#include<algorithm>
#include "Quiz.h"

using namespace std;

void main()
{
	//Sample vector A
	vector<double> A = { 11,13,3,5,4,6,9,7,8,10 };

	//Quick Sort
	cout << "The following are the result for Quick Sort:" << endl;
	auto A2 = A;
	QuickSort(A2, 0, A2.size() - 1);
	vector<double>::iterator it;
	for (it = A2.begin(); it != A2.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	//Max_heap
	int n, i;
	cout << "enter no of elements of array\n";
	cin >> n;
	int a[20];
	for (i = 1; i <= n; i++)
	{
		cout << "enter element" << (i) << endl;
		cin >> a[i];
	}
	max_heap result;
	result.build_maxheap(a, n);
	cout << "Max Heap\n";
	for (i = 1; i <= n; i++)
	{
		cout << a[i] << endl;
	}
}