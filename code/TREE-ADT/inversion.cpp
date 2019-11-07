#include <iostream>
#include <vector>
using namespace std;

// http://blog.csdn.net/morewindows/article/details/8029996

/*
归并排序 计算给定序列 A 的逆序数
1. 将给定序列分成 L 和 R 两个部分 此时 A 的逆数属于以下情况
   a. 两个数都在 L 中
   b. 两个数都在 R 中
   c. 较大的数值在 L 中, 较小的数值在 R 中
2. a,b 分治法处理
   对已排好序的 L 和 R 进行归并过程, 若剩余的 R 的第一个数值小于剩余的 L 的第一个数值
   则逆序的个数就等于 L 中剩余数值的个数 
*/ 

// 利用递归方式对 A[left...right]进行归并排序
// 返回相应范围内 inversion 个数 = 插入排序移动次数 
long long countMove(vector<int>& A, int left, int right) {
	// 初始部分: 区间长度等于完成排序, 且不会存在 inversion
	if(left == right) return 0;
	
	// 分割成两部分使用分治法 
	int mid = (left + right) / 2;
	long long ret = countMove(A, left, mid) + countMove(A, mid+1, right);
	
	// 合并保存于临时数组的两个子数组
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while(leftIndex <= mid || rightIndex <= right) {
		if(leftIndex <= mid && 
	 		(rightIndex > right || A[leftIndex] <= A[rightIndex])
					 ) {
			tmp[tmpIndex++] = A[leftIndex++];
 		} else {
 			// A[rightIndex]小于左侧子数组中的所有剩余数值
			// 将这些数值的个数相加到 inversion
			ret += mid - leftIndex + 1;  		// 结合merge_sort 重点考虑！！！ 
			tmp[tmpIndex++] = A[rightIndex++];
 		}
	}
	for(int i=0; i<tmp.size(); ++i)
		A[left + i] = tmp[i];
	return ret;
}

int countNative(vector<int>& a) {
	int n = a.size(), cnt = 0;  
    int i, j;
    for (i = 0; i < n; i++)  
        for (j = i + 1; j < n; j++)  
            if (a[i] > a[j])
                cnt++;
    return cnt;
}

int main() {
	vector<int> a{5, 1, 4, 3, 2};
	cout << countNative(a) << endl;
	cout << countMove(a, 0, a.size()-1) << endl;
	for(auto i : a)
 		cout << i << " ";

	return 0;
}
