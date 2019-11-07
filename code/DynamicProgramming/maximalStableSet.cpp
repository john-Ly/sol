#include <iostream>
#include <bitset>
#include <string>
using namespace std;

// http://en.cppreference.com/w/cpp/utility/bitset/bitset

int n;
int explodes[4] = {	2,  1,  8,  4 };
				// 0010   1000
				   // 0001    0100

// 确认给定集合的稳定性 
bool isStable(int set) {
	for(int i=0; i<n; ++i)
		// 遍历集合中每一个元素
		//   存在元素 i        是否存在元素 i 的 *克星*
		// 输出：0 或者 1<<i 
	    if( (set & (1<<i)) && (set & explodes[i]) ) {
/*	    	std::bitset<4> b1(set & (1<<i));
	    	std::bitset<4> b2(set & explodes[i]);
	    	cout << i << " " << b1 << " "<< b2 << endl;*/
   		    return false;
		}
    return true;
}

// 算出所有最大稳定集的个数 
int countStableSet() {
	int ret = 0;
	// 遍历所有集合 n=4 共2^4-1= 15种 
	for(int set=1; set < (1<<n); ++set) {
		if(!isStable(set)) continue;
		// 确认是否是最大稳定集之前, 需要确认还有没有可放入的物质
		bool canExtend = false;
		for(int add=0; add<n; ++add)
				// 不存在 add 元素          不存在 add 元素的 克星 
		    if( (set & (1<<add)) == 0 && (set & explodes[add]) == 0 ) {
		    	canExtend = true;
		    	break;
			}
		if(!canExtend) ++ret;
	}
	return ret;
}

int main() {
	n = 4;
	// http://en.cppreference.com/w/cpp/io/manip/boolalpha
	cout << boolalpha << isStable(13) << endl;
	cout << countStableSet() << endl;

    return 0;
}
