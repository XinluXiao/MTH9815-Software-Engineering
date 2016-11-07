#pragma once
#ifndef QUIZ_H
#define QUIZ_H
#include<vector>
#include<iostream>
#include<conio.h>

using namespace std;

//Quick Sort
void QuickSort(vector<double> &A, int start, int end);
int Partition(vector<double> &A, int start, int end);

//max heap class
class max_heap {
public:
	void max_heapify(int *a, int i, int n)
	{
		int j, temp;
		temp = a[i];
		j = 2 * i;
		while (j <= n)
		{
			if (j < n && a[j + 1] > a[j])
				j = j + 1;
			if (temp > a[j])
				break;
			else if (temp <= a[j])
			{
				a[j / 2] = a[j];
				j = 2 * j;
			}
		}
		a[j / 2] = temp;
		return;
	}
	void build_maxheap(int *a, int n)
	{
		int i;
		for (i = n / 2; i >= 1; i--)
		{
			max_heapify(a, i, n);
		}
	}
};


#endif
