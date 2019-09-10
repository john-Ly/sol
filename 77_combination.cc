#include <iostream>
#include <vector>
using namespace std;

// 排列 组合 subset 幂集合
//

// 集合的幂集  排除空集
void allPick(int n) {
	int num = 1<<n;      // 0 0001 --> 1 0000
	cout << num << endl;
	for(int i=1; i<num; i++) {    //从 1 循环到 2^n -1
		for(int j=0; j<n; j++) { // 对每一位进行比较
			int temp = i;
			if(temp & (1<<j))   //对应位上为1，则输出对应的字符
				cout << j;
		}
		cout << "\n";
	}
}

// combination m from n.  // n: 元素总数量
// Picked: 已选元素的序号
// toPick: 还需选择的元素数量; 为0 全部组合
void pick(int n, int toPick, vector<int>& picked, vector<vector<int> >& res) {
 	if(toPick == 0) {
        res.push_back(picked);
		return;
 	}

    // 从1开始计数 (组合不能包含重复的项+按顺序生成)
	int smallest = picked.empty() ? 1 : picked.back() + 1;

    // 类似与DFS 但是不同@NOTE
    // 递归的思想是 只假设第一层的处理方案 递归调用 类似DFS直到最深层 关键是回溯环节
	for(int next=smallest; next<=n; ++next) {
		picked.push_back(next);
		pick(n, toPick-1, picked, res);
		picked.pop_back();
	}
}


vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> out;
    pick(n, k, out, res);
    return res;
}
