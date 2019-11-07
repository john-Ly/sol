#include <iostream>
#include <iomanip>  // format of "cout"
#include <cstring>
using namespace std;

// 二项式系数理解
// https://blog.csdn.net/u011240016/article/details/53008760
int min(int a, int b){
    return (a<b)? a: b;
}

// https://stackoverflow.com/questions/33841529/a-generic-function-in-c-to-print-2d-integer-array-created-by-various-techniqu
template<typename T>
void printMatrix(T mat, std::size_t N, std::size_t M) {
    cout<<"\n Printing Matrix : \n";
    for(int i = 0 ; i < N ; ++i) {
        for(int j = 0 ; j < N; ++j)
            cout << setiosflags(ios::left) << setw(4) <<  *(*(mat+i)+j);
        cout<<endl;
    }
    cout<<endl;
}

// http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/
// http://www.csl.mtu.edu/cs4321/www/Lectures/Lecture%2015%20-%20Dynamic%20Programming%20Binomial%20Coefficients.htm
//
// Returns value of Binomial Coefficient C(n, k)
int binomialCoeff(int n, int k) {
    int C[n+1][k+1];
    int i, j;

    // Caculate value of Binomial Coefficient in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= min(i, k); j++)
        {
            // Base Cases
            if (j == 0 || j == i)
                C[i][j] = 1;

            // Calculate value using previosly stored values
            else
                C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    return C[n][k];
}

/* @TODO
int binomialCoeff(int n, int k) {
    int C[k+1];
    memset(C, 0, sizeof(C));

    C[0] = 1;  // nC0 is 1

    for (int i = 1; i <= n; i++) {
        // Compute next row of pascal triangle using
        // the previous row
        for (int j = min(i, k); j > 0; j--)
            C[j] = C[j] + C[j-1];
    }
    return C[k];
}
*/

// dp
int cache[5][5];
int bino(int n, int r) {
    int& ret = cache[n][r];
	if(r == 0 || r == n) return ret = 1;  // return 1;  --> get the cache table
	if(cache[n][r] != -1) return ret;

	return ret = bino(n-1, r-1) + bino(n-1, r);
}

// recursive
int bino_re(int n, int r) {
	if (r == 0 || n == r) return 1;
	return bino(n-1, r-1) + bino(n-1, r);
}

int main(int argc, char* argv[]) {
    std::memset(cache, -1, sizeof(cache));

	// std::cout << bino(4, 2) << std::endl;
	std::cout << binomialCoeff(4, 2) << std::endl;

	// printMatrix(cache, 5, 5);
	// std::cout << bino_re(8, 4) << std::endl;
	return 0;
}
