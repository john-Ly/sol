#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


// @TODO 1. unordered_map的使用
// 2.
vector<int> twoSum(vector<int> &numbers, int target)
{
    //Key is the number and value is its index in the vector.
	unordered_map<int, int> hash;
	vector<int> result;
	for (int i = 0; i < numbers.size(); i++) {
		int numberToFind = target - numbers[i];

        //if numberToFind is found in map, return them
		if (hash.find(numberToFind) != hash.end()) {
            //+1 because indices are NOT zero based
			result.push_back(hash[numberToFind]);
			result.push_back(i);
			return result;
		}

        //number was not found. Put it in the map.
		hash[numbers[i]] = i;
	}
	return result;
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

