#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4377150.html
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/discuss/39038/Kadane's-Algorithm-Since-no-one-has-mentioned-about-this-so-far-%3A)-(In-case-if-interviewer-twists-the-input)

// maximum contiguous subsequence sum
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int MIN = numeric_limits<int>::min();

/**
 * Cubic maximum contiguous subsequence sum algorithm.
 *  枚举上下界{i,j | 0<=i<=j<=n}，维护一个max值即可。
 *  枚举上下界的时间复杂度为O(n^2) 求区间和的复杂度为O(n) -- 总时间复杂度为O(n^3)
 */
int maxSubSum1( const vector<int> & a ) {
	int N = a.size();
    int maxSum = MIN;

    for( int i=0; i<N; ++i )
        for( int j=i; j<N; ++j ) {
        	// get the range A[i..j]'s sum
            int thisSum = 0;

            for( int k=i; k<=j; ++k )
                thisSum += a[ k ];

            if( thisSum > maxSum )
                maxSum = thisSum;
        }

    return maxSum;
}


/**
 * Quadratic maximum contiguous subsequence sum algorithm.
 * 对比第一种算法 该算法利用了上一次求和的结果 避免重复计算 达到 O(N^2)
 * 部分连续最大和 -- 中间部分
 *
 * 先定下第一个数字 然后从这个数字动态增大范围(利用了上次的计算)
 *
 * @TODO 可能的问题 会出现负数的情况
 */
int maxSubSum2(const vector<int>& a) {
	int N = a.size();
    int maxSum = MIN;

    for( int i=0; i<N; ++i) {
        int thisSum = 0;
        for( int j = i; j<N; ++j) {
            // 该算法利用了上一次求和的结果 避免重复计算
            thisSum += a[ j ];

            if( thisSum > maxSum )
                maxSum = thisSum;
        }
    }

    return maxSum;
}

// Return maximum of three integers.
int max3( int a, int b, int c ) {
    return a > b ? a > c ? a : c : b > c ? b : c;
}

/**
 * Recursive maximum contiguous subsequence sum algorithm.
 * Finds maximum sum in subarray spanning a[left..right].
 * Does not attempt to maintain actual best sequence.
 */
int maxSumRec( const vector<int>& a, int left, int right) {
    if( left == right )  // Base case
        if( a[ left ] > 0 )
            return a[ left ];
        else
            return 0;

    int center = ( left + right ) / 2;
    int maxLeftSum  = maxSumRec( a, left, center );
    int maxRightSum = maxSumRec( a, center + 1, right );

    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for( int i = center; i >= left; --i )
    {
        leftBorderSum += a[ i ];
        if( leftBorderSum > maxLeftBorderSum )
            maxLeftBorderSum = leftBorderSum;
    }

    int maxRightBorderSum = 0, rightBorderSum = 0;
    for( int j = center + 1; j <= right; ++j )
    {
        rightBorderSum += a[ j ];
        if( rightBorderSum > maxRightBorderSum )
            maxRightBorderSum = rightBorderSum;
    }

    return max3( maxLeftSum, maxRightSum,
                    maxLeftBorderSum + maxRightBorderSum );
}

int fastMaxSum( const vector<int>& a, int lo, int hi ) {
    if( lo == hi ) return a[ lo ];

    int mid = ( lo + hi ) / 2;

	int left = MIN, right = MIN, sum = 0;
	for( int i=mid; i>=lo; --i ) {
		sum += a[i];
		left = MAX(left, sum);
    }

	for( int j=mid+1; j<=hi; ++j ) {
		sum += a[j];
		right = MAX(right, sum);
    }
    // fastMaxSum() 求出是 左 右 的最大和(子问题)
	// 但是如果跨了两个区间 则从 左边的最后一位开始累加(固定) 右边第一位开始累加(固定)
	// 避免了 连个区间链接是 有 遗漏 或者 编码复杂

	int single = MAX( fastMaxSum(a, lo, mid), fastMaxSum(a, mid+1, hi) );

	return MAX( single, left+right );
}

/**
 * Driver for divide-and-conquer maximum contiguous
 * subsequence sum algorithm.
 *
 * T(n) = 2T(n/2) + O(n)   同时是快速排序的时间复杂度
 */
int maxSubSum3( const vector<int> & a )
{
    return maxSumRec( a, 0, a.size( ) - 1 );
}

/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 * retuern maxSum + start & end index
 * ref: OneNote->algorithm
 *
 *  这个变种算法思路很好 实质还是DP算法
 */
int maxSubSum4(const vector<int> & a, int& start, int& end) {
    int maxSum = 0, thisSum = 0;
    int curstart = start = 0;

    for(int j=0; j<a.size(); ++j) {
    	if (thisSum < 0) {
		    thisSum == a[j];
    		curstart = j;
		} else
		    thisSum += a[j];

        // 范围更新
        if(thisSum>maxSum) {
            maxSum = thisSum;
			start = curstart;
			end = j;
		}
    }

    return maxSum;
}

/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 * Dynamic Programming :
 *   以a[i]结尾最大和 递推公式
 *    maxAt(i) = max(0, maxAt(i-1)) + A[i]
 *               filter the negative sum
 */
// @TODO 如果全是负数 找出最大的值
int fastestMaxSum( const vector<int> & a ) {
    int maxSum = MIN, thisSum = 0;

    for( int j = 0; j < a.size( ); ++j ) {
        // 排除负数的情况
        // thisSum就是 maxAt[j]
    	thisSum = MAX(thisSum, 0) + a[j];
    	maxSum = MAX(thisSum, maxSum);
    }

    return maxSum;
}

// @SEE 建议
int maxSubArray(vector<int>& nums) {
    int res = MIN, curSum = 0;
    for (int num : nums) {
        curSum = max(curSum + num, num);
        res = max(res, curSum);
    }
    return res;
}

// 仅针对数值类型进行比较
template <class T>
T maxNumInThree(T a, T b, T c) {
    T max;
    max = (a > b) ? a : b;
    max = (max > c) ? max : c;

    return max;
}



/**
 * Simple test program.
 */
int main() {
    vector<int> a { 4, -3, 5, -2, -1, 2, 6, -2 };
    int maxSum;
	int x = 0, y = 0;

    maxSum = maxSubSum1( a );
    cout << "Max sum is " <<  maxSum << endl;
    maxSum = maxSubSum2( a );
    cout << "Max sum is " <<  maxSum << endl;
    maxSum = maxSubSum3( a );
    cout << "Max sum is " <<  maxSum << endl;
    maxSum = maxSubSum4( a, x, y );
    cout << "Max sum is " <<  maxSum << " " << x << " " << y << endl;

    return 0;
}
