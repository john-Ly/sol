#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// maximum contiguous subsequence sum
#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int MIN = numeric_limits<int>::min();

/**
 * Cubic maximum contiguous subsequence sum algorithm.
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
                maxSum   = thisSum;
        }

    return maxSum;
}


/**
 * Quadratic maximum contiguous subsequence sum algorithm.
 * 对比第一种算法 该算法利用了上一次求和的结果 避免重复计算 达到 O(N^2) 
 */
int maxSubSum2( const vector<int> & a )
{
	int N = a.size();
    int maxSum = MIN;

    for( int i = 0; i < N; ++i )
    {
        int thisSum = 0;
        for( int j = i; j < N; ++j )
        {
            thisSum += a[ j ];

            if( thisSum > maxSum )
                maxSum = thisSum;
        }
    }

    return maxSum;
}

/**
 * Return maximum of three integers.
 */
int max3( int a, int b, int c )
{
    return a > b ? a > c ? a : c : b > c ? b : c;
}

/**
 * Recursive maximum contiguous subsequence sum algorithm.
 * Finds maximum sum in subarray spanning a[left..right].
 * Does not attempt to maintain actual best sequence.
 */
int maxSumRec( const vector<int> & a, int left, int right )
{
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
    // fastMaxSum() 求出是 左 右 的最大和
	//  但是如果跨了两个区间 则从 左边的最后一位开始累加 右边第一位开始累加
	// 避免了 连个区间链接是 有 遗漏 或者 编码复杂 

	int single = MAX( fastMaxSum(a, lo, mid), fastMaxSum(a, mid+1, hi) );
    
	return MAX( single, left+right );
}

/**
 * Driver for divide-and-conquer maximum contiguous
 * subsequence sum algorithm.
 */
int maxSubSum3( const vector<int> & a )
{
    return maxSumRec( a, 0, a.size( ) - 1 );
}

/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 */
int maxSubSum4( const vector<int> & a )
{
    int maxSum = 0, thisSum = 0;

    for( int j = 0; j < a.size( ); ++j )
    {
        thisSum += a[ j ];

        if( thisSum > maxSum )
            maxSum = thisSum;
        else if( thisSum < 0 )
            thisSum = 0;
    }

    return maxSum;
}

/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 * Dynamic Programming :
 *    maxAt(i) = max(0, maxAt(i-1)) + A[i]
 *               filter the negative sum
 */
int fastestMaxSum( const vector<int> & a ) {
    int maxSum = 0, thisSum = 0;

    for( int j = 0; j < a.size( ); ++j ) {
    	thisSum = MAX(thisSum, 0) + a[j];
    	maxSum = MAX(thisSum, maxSum);
    }

    return maxSum;
}


/**
 * Simple test program.
 */
int main( )
{
    vector<int> a { 4, -3, 5, -2, -1, 2, 6, -2 };
    int maxSum;

    maxSum = maxSubSum1( a );
    cout << "Max sum is " <<  maxSum << endl;
    maxSum = maxSubSum2( a );
    cout << "Max sum is " <<  maxSum << endl;
    maxSum = maxSubSum3( a );
    cout << "Max sum is " <<  maxSum << endl;
    maxSum = maxSubSum4( a );
    cout << "Max sum is " <<  maxSum << endl;

    return 0;
}
