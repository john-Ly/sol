#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// topic: n_sum, array, 双指针

namespace two {
// 给定target 求数组中和满足的两个数的下标(下标不能相同)(无序)
// https://www.cnblogs.com/grandyang/p/4130379.html
vector<int> twoSum(vector<int> &numbers, int target) {
	unordered_map<int, int> hash;   // num -> idx
	vector<int> result;
    // 按顺序遍历, 所以不可能返回相同的i
	for (int i = 0; i < numbers.size(); i++) {
        if (hash.count(target - numbers[i])) {
			result.push_back(hash[target - numbers[i]]);
			result.push_back(i);
			return result;
		}

		hash[numbers[i]] = i;
	}
	return result;
}

// 升序数组 twoSum 如果有多对数字的和等于S，输出两个数的乘积最小的
// 双指针 - 保证乘积最小
vector<int> FindNumbersWithSum(vector<int>& array, int sum) {
    vector<int> result;
    int length = array.size();
    if(length < 1) { return result; }
    int pleft = 0, pright = length - 1;

    while(pleft > pright){
        int curSum = array[pleft] + array[pright];
        if (curSum == sum) {
            result.push_back(array[pleft]);
            result.push_back(array[pright]);
            break;
        }
        else if(curSum < sum) { pleft++;}
        else { pright--; }
    }
    return result;
}

}

int main () {
    vector<int> v {2, 7, 11, 15};
    int target = 9;
    auto tmp = twoSum(v, target);

    for(auto i: tmp)
        cout << i << " ";
    cout << endl;
    return 0;
}

