#include "Quiz.h"
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

//Quick Sort
void QuickSort(vector<double> &A, int start, int end)
{
	if (start < end)
	{
		int pIndex = Partition(A, start, end);
		QuickSort(A, start, pIndex - 1);
		QuickSort(A, pIndex + 1, end);
	}
}
int Partition(vector<double> &A, int start, int end)
{
	double pivot = A[end];
	int pIndex = start;
	for (int i = start; i < end; ++i)
	{
		if (A[i] <= pivot)
		{
			swap(A[i], A[pIndex]);
			pIndex = pIndex + 1;
		}
	}
	swap(A[pIndex], A[end]);
	return pIndex;
}