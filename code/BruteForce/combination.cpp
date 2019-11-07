#include <iostream>
#include <vector>
using namespace std;

// combination m from n.
// n: 元素总数量
// Picked: 已选元素的序号
// toPick: 还需选择的元素数量; 为0 全部组合
void pick(int n, vector<int>& picked, int toPick) {
 	if(toPick == 0) {
		for(auto i : picked)
			cout << i << "-";

		cout << endl;
		return;
 	}

	int smallest = picked.empty() ? 0 : picked.back() + 1;

	for(int next=smallest; next<n; ++next){
		picked.push_back(next);
		pick(n, picked, toPick-1);
		picked.pop_back();
	}
}

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

int main() {
	int n=4;
//	for (int i=0; i<n; ++i)
//		for (int j=i+1; j<n; ++j)
//			for (int k=j+1; k<n; ++k)
//				for (int l=k+1; l<n; ++l)
//					cout << i << "-" << j << "-" << k << "-" << l << endl;

   // vector<int> tmp;
   //  pick(n, tmp, n);

    allPick(n);    // 2^n-1

    return 0;
}
