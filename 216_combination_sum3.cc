#include <iostream>
#include <vector>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4537983.html
// 求组合 相似
// 数字范围限定在1-9
// topick可以省去单独的变量 l
void pick(int n, int toPick, vector<int>& picked, vector<vector<int> >& res) {
 	if(toPick == 0 && n==0) {
        res.push_back(picked);
		return;
 	}

    // 从1开始计数 (组合不能包含重复的项+按顺序生成)
	int smallest = picked.empty() ? 1 : picked.back() + 1;
	for(int next=smallest; next<=9; ++next){
		picked.push_back(next);
		pick(n-next, toPick-1, picked, res);
		picked.pop_back();
	}
}

vector<vector<int> > combinationSum3(int k, int n) {
    vector<vector<int> > res;
    vector<int> out;
    pick(n, k, out, res);
    return res;
}