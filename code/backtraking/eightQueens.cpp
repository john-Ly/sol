#include <iostream>
#include <algorithm>
using namespace std;

// 对所有行列进行全排列 但是效率太低了(应该使用分支界限)
int queens() {
	int pos[] = {0,1,2,3,4,5,6,7},ans = 0;
	while(next_permutation(pos,pos+8)){
		bool ok = true;
		for(int* p = pos;p<pos+8;p++)                // 行列差 相等 上对角线
			if ( count_if(pos, p, [=](int& j){return p - &j == *p-j || p - &j == j - *p ;}) )
				ok = false;                                            //  下对角线
			// 因为同一行和同一列 肯定不会相同 因为 permutation 自动排除
		ans += ok;
	}
	return ans;
}

int main() {
	cout << queens() << endl;

	return 0;
}
