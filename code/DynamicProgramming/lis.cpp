#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring> // memset()
#include <functional>  // std::swap
#include <limits>
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ((a) > (b) ? (a) > (c) ? (a) : (c) : (b) > (c) ? (b) : (c) )
/*  int max3( int a, int b, int c ) {
    	return a > b ? a > c ? a : c : b > c ? b : c;
    }   */
// lis: 严格的递增序列  (子串要求连续 子序列不要求)

vector<int> a { 10, 22, 9, 33, 21, 50, 41, 60 };
vector<int> b { 5, 2, 1, 4, 5, 4, 5, 3, 6};
const long long NEGINF = numeric_limits<long long>::min();
int cnt=0;
// vector<int> a { 10, 5, 6, 7 };

// 穷举搜索法:
// worst-case: O(n*2^n)
int lis(const vector<int>& A) {
	if(A.empty()) return 0;
	int ret = 0;
	for(int i=0; i<A.size(); ++i) {
		vector<int> B;
		for(int j=i+1; j<A.size(); ++j)
		    if(A[i]<A[j]) B.push_back(A[j]);
        // 序列B包含所有大于 A[i]的数字, 也就是下一个可能的lis

        auto tmp = 1+lis(B);
		ret = max(ret, tmp);
	}
	return ret;
}

int cache[11];
// a[-1] 是不存在的数字 但是可以满足一个起始点 所有遍历
// lis2[i] = 表示字符串S[i...]里面的lis
int lis2(int start) {
    // cnt++;
	int& ret = cache[start+1];
	if(ret != -1) return ret;

    long long t = (start == -1 ? NEGINF : a[start]);
	ret = 1;
	for(int next=start+1; next<a.size(); ++next) {
        // 这个循环实际上对把问题分割成了n个子问题 所以-1可以保证后面的数都被加进来
	    if(/*start == -1 ||*/ t<a[next]) {
            // @TODO 为什么选用tmp临时变量 调用函数的次数cnt下降了一半
	        auto tmp = 1+lis2(next);
	        ret = MAX(ret, tmp);
        }
        // ret = MAX(ret, 1+lis2(next));
	}
	return ret;
}

// 需要单独指定起始值
// cache[i] = 表示字符串S[i...]里面的lis
int lis3(int start) {
	int& ret = cache[start];
	if(ret != -1) return ret;

    // 总是存在S[start] 故长度至少为1
	ret = 1;
	for(int next=start+1; next<a.size(); ++next) {
	    if(a[start]<a[next]) {
	        auto tmp = 1+lis3(next);
	        ret = max(ret, tmp);
        }
        // ret = max(ret, 1+lis3(next));
	}
	return ret;
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable& median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;

    // 3 numbers, 3 steps to sort them
    // left < center < right
    if( a[ center ] < a[ left ] )
        std::swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        std::swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        std::swap( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && tmp < a[ j - 1 ]; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right ) {
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );

        // Begin partitioning
        int i = left, j = right - 1;  //???
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

        quicksort( a, left, i - 1 );     // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}

// sort + lcs
int c[11][11];
int quick_lis4(vector<int>& a, vector<int>& b, int m, int n) {
	int& ret = c[m][n];
	if (m == 0 || n == 0)
		return ret = 0;

	if(ret != -1) return ret;
	if (a[m-1] == b[n-1])
		ret = quick_lis4(a, b, m-1, n-1) + 1;
	else
		ret = max(quick_lis4(a, b, m, n-1), quick_lis4(a, b, m-1, n));
	return ret;
}

/* 返回MaxV[i]中刚刚大于x的那个元素的下标 */
int BinSearch(int * MaxV, int size, int x) {
    int left = 0, right = size-1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(MaxV[mid] < x)
            left = mid + 1;
    	else
            right = mid - 1;
    }
    return left;
}

int lis5(vector<int>& a) {
	int maxV[a.size()+1];
	// 初始化
    maxV[0] = a[0];
    int len = 1;

    for(int i = 1; i < a.size(); ++i) {/* 寻找arr[i]属于哪个长度LIS的最大元素 */
        if(a[i] > maxV[len-1]) /* 大于最大的自然无需查找，否则二分查其位置 */
            maxV[len++] = a[i];
		else {
            int pos = BinSearch(maxV,len,a[i]);
            maxV[pos] = a[i];
        }
    }
    return len;
}
// lower_bound也可以使用

int main() {
    // int cnt = lis( a );
    // cout << "longest-1 is " << cnt << endl;  // 5

    memset(cache, -1, sizeof(cache));
	cout << lis2(-1)-1 << endl;
    // cout << cnt << '\n';

    // cout << "longest-3 is ";
	// memset(cache, -1, sizeof(cache));
    // int maxLen = 0;
    // for (int begin=0; begin<a.size(); ++begin)
    // 	maxLen = max(maxLen, lis3(begin));
    // cout << maxLen << endl;


    /*
	memset(cache, -1, sizeof(c));
	vector<int> a_copy = a;
	quicksort(a_copy);
	for (auto i:a_copy) cout << i << " ";
	cout << endl;
	cout << quick_lis4(a, a_copy, a.size(), a_copy.size()) << endl;*/

	// cout << lis5(b) << endl;

    return 0;
}
