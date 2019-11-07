#include <iostream>
#include <vector>
#include <set>        // multiset
#include <algorithm>  // sort, max
#include <utility>    // pair
using namespace std;

// 贪心算法证明方法：
/*
1. 比赛 *只能输* 或 *肯定能赢* P263算法问题实战策略
2. 交换论证的方法
*/
//  如果对方给定列出场顺序, 己方怎么安排能够取得最多的胜利次数
int order(const vector<int>& russian, const vector<int>& China) {
	int wins = 0;
	multiset<int> ratings(China.begin(), China.end());
	// multiset 使用二叉搜索树构成 所以构造时就是 顺序排列的

	for(const auto rus : russian) {
		// 评分高的选手不能取胜 就用评分最低选手出场
		if(*ratings.rbegin() < rus)
			ratings.erase(ratings.begin());
		// 其他情况下 能够战胜对方的选手中, 让评分低的选手出战
		else {
            // erase删除特定iter位置的元素 避免删除所有重复的相同key
			ratings.erase(ratings.lower_bound(rus));
			++wins;
		}
	}
	return wins;
}

int main() {
	vector<int> russian{3000, 2700, 2800, 2200, 2500, 1900};
	vector<int> China{2800, 2750, 2995, 1800, 2600, 2000};
	cout << "Following sessions wined: \n";
    cout << order(russian, China) << endl;
    return 0;
}
