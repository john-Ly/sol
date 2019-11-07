#include <iostream>
#include <vector>
#include <cstring>

// @TODO house robber问题 动态规划题型有一类(先求出最优化解 然后求出最优解的个数 ==> 最难的是打印出每个最优解)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define Size 4
#define MAX_NUMBER 20

using std::cout;
using std::vector;
int triangle[Size][Size] = {
		{9},
		{5,7},
		{1,3,2},
		{3,5,5,6},

//		{75},
//		{95,64},
//		{17,47,82},
//		{18,35,87,10},
//		{20, 4,82,47,65},
//		{19, 1,23,75, 3,34},
//		{88, 2,77,73, 7,63,67},
//		{99,65, 4,28, 6,16,70,92},
//		{41,41,26,56,83,40,80,70,33},
//		{41,48,72,33,47,32,37,16,94,29},
//		{53,71,44,65,25,43,91,52,97,51,14},
//		{70,11,33,28,77,73,17,78,39,68,17,57},
//		{91,71,52,38,17,14,91,43,58,50,27,29,48},
//		{63,66, 4,68,89,53,67,30,73,16,69,87,40,31},
//		{ 4,62,98,27,23, 9,70,98,73,93,38,53,60, 4,23},
	};

// P158 算法书
// path(x, y, sum) = 当前位置为(y, x) 路径中所有数值的总和为sum时, 返回当前路径延伸到最后一行时的最大值
// path 返回的是沿着x, y并且此时已解自问题的结果为sum的时, 到最后一行 整体的最大值

// path2(y, x) = 返回从(y, x)起始到最后一行的子路径(剩余子问题)总和的最大值
// 可能的路径个数和 三角形的行数 正相关(行数加1, 个数就会增加1倍)   n行三角形 == 2^ n-1
// time: O(2^ n)  @TODO P148 求解二项式系数的问题 时间复杂度 子问题的个数是 O(n^2)(还有杨辉三角)
int cache[Size][Size];
int path2(int y, int x) {
    int& ret = cache[y][x];
    // 制表要完整 否则count()利用不了
	if(y == Size-1) return ret = triangle[y][x];

	if(ret != -1) return ret;

	return ret = MAX(path2(y+1, x+1), path2(y+1, x)) + triangle[y][x];
}

// 有两个动态规划的问题 -- 优化问题(先求解最大的路径) + 各子问题最优解的个数
// 利用最大路径生成的 memo的数组来计算最有解的个数
// count(y, x) = 返回从(y, x)剩余子问题的最大路径的个数
int countCache[Size][Size];
int count(int y, int x) {
	int& ret = countCache[y][x];
    // 特别的 如果想要制表完整  还是要 ret=1
	if(y == Size-1) return ret = 1;
	if(ret != -1) return ret;

	ret = 0;
	if(path2(y+1, x+1) >= path2(y+1, x)) ret += count(y+1, x+1);
	if(path2(y+1, x+1) <= path2(y+1, x)) ret += count(y+1, x);
	// 相等的情况 利用代码简化了形式  >= 和 <= 包含了
	return ret;
}

// 解决三角形最大路径 迭代动规
// 二维数组C的下标含义 同上
int iterative() {
    vector<vector<int>> C(Size, vector<int>(Size, 0));
	// 计算初始部分
    // 这是 最后一行的路径长度(就是三角形最后一行自身的值)
	for(int x=0; x<Size; ++x)
		C[Size-1][x] =  triangle[Size-1][x];

	// 计算其他部分
	for(int y=Size-2; y>=0; --y)
	    for(int x=0; x<y+1; ++x)
			C[y][x] = MAX(C[y+1][x], C[y+1][x+1]) + triangle[y][x];
	return C[0][0];  // 从三角形的起点到最后一行的最大路径长度
}

//  解决三角形最大路径 迭代动规---滑动窗口 减少空间复杂度 因为只用到了相邻的一行信息 因此只需要两行数组
// int D[2][Size];
int iterative2() {
    vector<vector<int>> D(2, vector<int>(Size, 0));
	// 计算初始部分
	for(int x=0; x<Size; ++x)
		D[(Size-1)%2][x] =  triangle[Size-1][x];

	// 计算其他部分
	for(int y=Size-2; y>=0; --y)
	    for(int x=0; x<y+1; ++x)
			D[y%2][x] = MAX(D[(y+1)%2][x], D[(y+1)%2][x+1]) + triangle[y][x];
	return D[0][0];
}

int main(int argc, char* argv[]) {
    std::memset(cache, -1, sizeof(cache));
    std::memset(countCache, -1, sizeof(countCache));

	std::cout << path2(0,0) << std::endl;    // 24

	for(int x=0; x<Size; ++x) {
        for(int y=0; y<Size; ++y) {
            cout << cache[x][y] << '\t';
        }
        cout << '\n';
    }

	std::cout << iterative() << std::endl;   // 24
	std::cout << iterative2() << std::endl;  // 24
	std::cout << count(0,0) << std::endl;  // 0

	return 0;
}
