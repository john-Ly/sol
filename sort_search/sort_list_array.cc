#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

// 例题: 一个几乎有序的数组 每个元素最多移动k布 就可以有序
//  采用堆排序 建立一个k大小的滑动窗口  每次进行排序    时间复杂度O(N lg k)
//  插入排序 可以达到 O(n*k)

// 1. 稳定性(相同元素的相对位置) 快排 堆排 选择排序 shell
// 2. 使用场景
//    + 数据范围较小 (人的身高/ 年龄)  --> 计数排序
//
//    + 数组较小 且 几乎排序           --> 插入排序
//   数组较大 采用快排 或者其他O(n lg n)


// 桶的数量 O(M) 空间复杂度
// 计数排序/桶排序 (按身高排序(范围一定) 建立每个桶 + 遍历一边即可)

// 逆序对的个数理论上O(n^2)
namespace n2 {
// http://blog.csdn.net/morewindows/article/details/8029996

/*
归并排序 顺便计算给定序列 A 的逆序数
1. 将给定序列分成 L 和 R 两个部分 此时 A 的逆数属于以下情况
   a. 两个数都在 L 中
   b. 两个数都在 R 中
   c. 较大的数值在 L 中, 较小的数值在 R 中
2. a,b 分治法处理
   对已排好序的 L 和 R 进行归并过程, 若剩余的 R 的第一个数值小于剩余的 L 的第一个数值
   则逆序的个数就等于 L 中剩余数值的个数
*/

// usage:
// countMove(a, 0, a.size()-1)
// 返回相应范围内 inversion 个数 = 插入排序移动次数
long long countMove(vector<int>& A, int left, int right) {
	// 初始部分: 区间长度等于完成排序, 且不会存在 inversion
	if(left == right) return 0;

	// 分割成两部分使用分治法
	int mid = (left + right) / 2;
	long long ret = countMove(A, left, mid) + countMove(A, mid+1, right);

	// 合并两个有序的子数组, 保存于临时数组的两个子数组
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while(leftIndex <= mid || rightIndex <= right) {
        // L非空                R为空                   L左边第一个小于右边第一个
		if(leftIndex <= mid && (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
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


// 冒泡排序 每次确定一个有序数 第i趟 [n-i, n-1]
void bubble_sort(vector<int> v) {
    bool swaped = false;
    for (int i=0; i<v.size(); ++i) {
        if (!swaped) break;
        int end = v.size()-i;    // 最后一位是最大值
        for (int j=1; j<end; ++j) {
            if (v[j] < v[j-1]) {
                swap(v[j], v[j-1]);
                swaped = true;
            }
        }
    }
}

// 有序区间在 [0,i]
void select_sort(vector<int> v) {
    for (int i=0; i<v.size(); ++i) {
        int minIdx = i;
        // 每次找出全局最小
        for (int j=i+1; j<v.size(); ++j) {
            if (v[j] < v[minIdx]) {
                minIdx = j;
            }
        }
        swap(v[i], v[minIdx]);
    }
}

// 希尔排序
void insert_sort(vector<int> v) {
    for (int i=1; i<v.size(); ++i) {
        for (int j=i; j>0; --j) {
            if (v[j] < v[j-1]) {
                swap(v[j], v[j-1]);
            }
        }
    }
}
}

namespace merge_sort {
void merge_inplace(vector<int>& a, vector<int>& tmpArray,
           int leftPos, int rightPos, int rightEnd ) {
    int leftEnd = rightPos - 1;
    int rightNum = rightEnd - rightPos + 1;

    // 找出左部分 第一个 X[i] < Y[0], swap(), 在Y范围进行排序 保证sorted
    // 如果 左半部分都小于Y[0] 则不用排序
    for (int i=leftPos; i<=leftEnd; ++i) {
        if (a[i] > a[rightPos]) {
            swap(a[i], a[rightPos]);

            // @TODO 二分法
            // (就算找到了插入位置 还是要移动 O(n)) -- 感觉还是不划算
            auto tmp = a[rightPos];
            // Y[0] 在Y[1...n-1]有序范围内的插入位置
            int j = rightPos+1;
            for (; j<=rightEnd && a[j] < tmp ; ++j) {
                a[j-1] = a[j]; // 因为数组保持连续 需要移动元素
            }
            // 退出循环后 a[j] >= tmp 插入位置为j-1
            a[j-1] = tmp;
        }
    }
}

void mergeSort(vector<int>& a, int left, int right) {
    // right - left >= 2 否则没法拆成 两个部分
    if(left < right) {
        int center = (left+right) / 2;
        mergeSort(a, left, center);
        mergeSort(a, center+1, right);

        // 1. std::inplace_merge(left, center+1, right)

        // 2. 使用临时数组
        vector<int> tmp(right-left+1);
        int tmpIndex = 0, leftIndex = left, rightIndex = center + 1;
        // 合并两个有序的子数组, 保存于临时数组的两个子数组
        while(leftIndex <= center || rightIndex <= right) {
            // L非空                R为空                   L左边第一个小于右边第一个
            if(leftIndex <= center && (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
                tmp[tmpIndex++] = A[leftIndex++];
            } else {
                // A[rightIndex]小于左侧子数组中的所有剩余数值
                tmp[tmpIndex++] = A[rightIndex++];
            }
        }
        for(int i=0; i<tmp.size(); ++i)
            a[left+i] = tmp[i];
    }
}

// 左闭右闭
void mergeSort(vector<int>& a) {
    mergeSort(a, 0, a.size()-1);
}
}

namespace quick_sort {
// 应该是三路快排
// Time O(n lg n); Space O(lg N) ~ lg(N) 最差的情况
void quick_sort(vector<int>& nums, int left, int right) {
    if (left == right) return;

    // 1. 第一个元素作为pivot
    int pivot = nums[left], l = left + 1, r = right;

    // 2. 循环退出时, r指向左边的区域,
    while (l <= r) {
        if (nums[l] > pivot && nums[r] < pivot) {
            swap(nums[l++], nums[r--]);
        }

        if (nums[l] <= pivot) ++l;
        if (nums[r] >= pivot) --r;
    }
    // 确定pivot的最终顺序
    swap(nums[left], nums[r]);

    quick_sort(nums, left, r);
    quick_sort(nums, l, right);
}

void driver() {
    std::vector<int> v = {32,71,12,45,26,80,53,33,36,45};
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));

    // for(int elem : v) std::cout << elem << ' ';
    std::cout << "\n";
    quick_sort(v, 0, v.size()-1);

    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}
}

// Space O(1); Time O(n lg n)
namespace heap_sort {
// 用可以动态扩容的vector实现完全二叉树
// 二进制堆： 两个形状规则
//  (1.除最后一层外 其余所有层必须填满节点)
//  (2.最后一层外 必须从最侧开始填充节点)
// 大小关系规则(父节点拥有的元素要大于子节点)

// 2. 生成堆 的时间复杂度 O(n) , 但是建堆的目的是取出最值 总的时间复杂度为O(n lg n)
// 使用每次读入一个项, 然后push_heap的方式 也是O(n lg n)
vector<int> heap;

// 先满足形状关系, 在满足大小关系
// time: O(lg n)
void push_heap(vector<int>& heap, int newValue) {
	// 向堆的末端插入 newValue
	heap.push_back(newValue);
	// newValue 当前位置
	int idx = heap.size() - 1;
	// 直至到达根节点或遇到包含比 newValue 更大元素的父节点为止
    // 每次循环进入树的上一层
    // idx == 0 代表最高层
	while(idx>0 && heap[(idx-1)/2] < heap[idx]){
		swap(heap[idx], heap[(idx-1)/2]);
		idx = (idx-1) / 2;
	}
}

// @TODO pop_heap怎么实现
// 从拥有整数元素的最大堆中删除最大元素
// time: O(lg n)
void pop_heap(vector<int>& heap) {
    auto old = heap[0];
	// 从堆的末端得到元素值并覆盖根节点
	heap[0] = heap.back();
	heap.pop_back();
	int here = 0;
    // 每次循环会移动到树的下一层
	while(true) {
		int left = here * 2 + 1, right = here * 2 + 2;
		// 到达叶节点时
		if(left >= heap.size()) break;
		int next = here;
		if(heap[next] < heap[left])
			next = left;
		if(right < heap.size() && heap[next] < heap[right])
	 		next = right;
		if(next == here) break;
		swap(heap[here], heap[next]);
		here = next;
	}
    heap.push_back(old);
}

// heap_sort 删除最大值之后 最后一个元素的位置是空的 因此heap_sort可以原地排序(排序不是稳定的)
void heap_sort(vector<int>& v) {
	for(auto i : v) push_heap(heap, i);

	for(int i=v.size()-1; i>=0; --i) {
		v[i] = heap.front();
		pop_heap(heap);
	}
}
}

int main() {
    quick_sort::driver();
	// vector<int> v{5, 1, 4, 3, 2};
	// heap_sort(v);
	// for(auto i : v)
    //   	cout << i << " ";
    // cout << endl;

	return 0;
}
