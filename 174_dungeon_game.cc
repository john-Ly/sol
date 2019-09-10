#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "  [";
		for (T val: row) {
			cout << val << " , ";
		}
        cout << "],\n";
	}
    cout << "}\n";
}

vector<vector<int>> dungeon = {
		{-2,-3, 3},
		{-5,-10,1},
		{10,30,-5},
	};

int M = dungeon.size(); int N = dungeon[0].size();

namespace so1 {
// https://leetcode.com/problems/dungeon-game/discuss/52774/C%2B%2B-DP-solution
int calculateMinimumHP(vector<vector<int> > &dungeon) {
    // int M = dungeon.size();
    // int N = dungeon[0].size();
    // hp[i][j] represents the min hp needed at position (i, j)
    // Add dummy row and column at bottom and right side
    vector<vector<int> > hp(M + 1, vector<int>(N + 1, INT_MAX));
    // 虚拟出一行和一列 并且设置为0
    hp[M][N - 1] = 1; hp[M - 1][N] = 1;
    for (int i = M - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
            hp[i][j] = need <= 0 ? 1 : need;
        }
    }
    return hp[0][0];
}
}

namespace so2 {
vector<vector<int> > hp(M + 1, vector<int>(N + 1, -1));
// 返回在(i, j)位置到重点的 需要的最小血量
int calculateMinimumHP(int y, int x) {
	if(y >= M || x >= N) return INT_MAX; // 因为最终会比较 min 所以一定要设置INT_MAX
    int& ret = hp[y][x];
    if (y == M-1 && x == N-1) return ret = 1 - dungeon[y][x];

	if(ret != -1) return ret;
	auto cand = min(calculateMinimumHP(y, x+1), calculateMinimumHP(y+1, x)) - dungeon[y][x];
    return ret = max(1, cand);
}
}



int main(int argc, char* argv[]) {
    {
        using namespace so2;
        std::cout << calculateMinimumHP(0,0) << std::endl;

        printVector(hp);
    }

    // std::cout << so2::Paths_iter() << std::endl;
	return 0;
}

