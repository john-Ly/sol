#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.cnblogs.com/grandyang/p/4444160.html

// 类似二叉树 每次都先找到左边的分支
// @TODO 这个发现很好 递归的调用实际上就是在树/图上遍历(深度优先)
void DFS(int left, int right, string out, vector<string> &res) {
    // cout << left << "-" << right << endl;
    // 错误处理: 如果穿进来的left > right一定是不匹配的
    if (left > right) return;

    if (left == 0 && right == 0) res.push_back(out);
    else {
        // 每次都从左分支开始 则只要数量一致, 一定能找到所有匹配
        if (left > 0) DFS(left - 1, right, out + '(', res);
        if (right > 0) DFS(left, right - 1, out + ')', res);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    DFS(n, n, "", res);
    return res;
}

int main() {
    auto tmp = generateParenthesis(3);
    for (auto& str : tmp)
        cout << str << endl;

    return 0;
}
