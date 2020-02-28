#include <iostream>
#include <vector>
using namespace std;
// 求出所有连续的序列 满足给定和
// sum = (a+b) *n /2
void printVector(vector<vector<int>> const &mat) {
    cout << "{\n";
	for (vector<int> row: mat) {
        cout << "  [";
		for (int val: row) {
			cout << val << ',';
		}
        cout << "],\n";
	}
    cout << "}\n";
}

vector<vector<int>> FindContinuousSequence(int sum) {
    vector<vector<int> > result;
    // 高位指针和低位指针
    int phigh = 2, plow = 1;

    // 终止条件是phigh等于sum
    while(phigh > plow){
        // 当前和，使用求和公式s = (a+b) * n / 2
        int curSum = (plow + phigh) * (phigh - plow + 1) >> 1;
        // if(curSum < sum){
        //     phigh++;
        // }
        // if(curSum == sum) {
        //     vector<int> temp;
        //     for(int i = plow; i <= phigh; i++){
        //         temp.push_back(i);
        //     }
        //     result.push_back(temp);
        //     plow++;  // 否则死循环
        // }
        // if(curSum > sum){
        //     plow++;
        // }

        if(curSum == sum) {
            vector<int> temp;
            for(int i = plow; i <= phigh; i++){
                temp.push_back(i);
            }
            result.push_back(temp);
            plow++;  // 否则死循环
        } else if (curSum < sum) { phigh++; }
        else {  plow++; }

    }
    return result;
}

int main(int argc, char *argv[]) {
    auto tmp = FindContinuousSequence(100);
    printVector(tmp);
    return 0;
}
