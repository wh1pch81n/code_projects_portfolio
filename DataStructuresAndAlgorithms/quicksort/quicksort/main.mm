//
//  main.m
//  quicksort
//
//  Created by Derrick Ho on 9/26/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <vector>

template <typename T>
void swap(T &a, T &b) {
	if (a!=b)
		a ^= b, 	b ^= a, a ^= b;
}

template<typename T>
size_t partition(std::vector<T> &v, int left, int right, int pivotIndex) {
	T pivotValue = v[pivotIndex];
	swap(v[pivotIndex], v[right]);
	for (int i = left; i < right; ++i) {
		if (v[i] < pivotValue) {
			swap(v[left], v[i]);
			left += 1;
		}
	}
	swap(v[left], v[right]);
	return left;
}

template<typename T>
void quicksort(std::vector<T> &v, int left, int right) {
	if (left >= right) return;
	int pivotNewIndex = partition(v, left, right, (left +right)>>1);
	quicksort(v, left, pivotNewIndex -1);
	quicksort(v, pivotNewIndex +1, right);
}
#undef swap

int main(int argc, const char * argv[])
{

	@autoreleasepool {
		std::vector<int>v;
		for (int i = 0; i < 10; ++i) {
			v.push_back(arc4random()%10);
		}
	    for (int i = 0; i < v.size(); ++i) {
			printf("%d ", v[i]);
		}printf("\n");
		quicksort(v, 0, v.size()-1);
		for (int i = 0; i < v.size(); ++i) {
			printf("%d ", v[i]);
		}printf("\n");
	}
    return 0;
}

