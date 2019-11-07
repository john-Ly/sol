#include <iostream>
#include <vector>
#include <cstring> // memset()
#include <functional>  // std::swap
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ((a) > (b) ? (a) > (c) ? (a) : (c) : (b) > (c) ? (b) : (c) )

vector<int> a{ 8, 1, 5, 9, 0, 3, 5, 2, 7, 6 , 5, 5,5 , 4, 4, 4};
//vector<int> a{4, 5};
// quicksort在 pivot 等于 j, 造成错误
// 在数组较短的情况下 利用其它排序 

const int & median3(vector<int> & a, int left, int right)
{
	int center = (left + right) / 2;

	// 3 numbers, 3 steps to sort them
	// left < center < right
	if (a[center] < a[left])
		std::swap(a[left], a[center]);
	if (a[right] < a[left])
		std::swap(a[left], a[right]);
	if (a[right] < a[center])
		std::swap(a[center], a[right]);

	// Place pivot at position right - 1
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}

void quicksort(vector<int> & a, int left, int right) {
	if(left < right) {
		const int & pivot = median3(a, left, right);
	
		// Begin partitioning
		int i = left, j = right - 1;

		while (true) {
			while (i<right && a[++i] < pivot) {}

			while (j>left && pivot < a[--j]) {}

			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}

		std::swap(a[i], a[right - 1]);  // Restore pivot

		quicksort(a, left, i-1);     // Sort small elements
		quicksort(a, i + 1, right);    // Sort large elements
	}
}

int main() {
	quicksort(a, 0, a.size() - 1);
	for (auto i : a)
		cout << i << " ";
		cout << endl;
	return 0;
}
