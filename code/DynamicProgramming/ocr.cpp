#include <iostream>
#include <vector>
#include <cmath>    // log()
#include <cstring> // memset()
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
/////////////////////// 
// @TODO 未完 程序
/////////////////////// 
 
// 将矩阵转化成 有向图 边即跃迁的概率
int n, m;
// 分类器返回的句子
int R[] = {0, 1, 2, 3, 4};
// T[i][j] 单词 j 出现在 i 后面的概率 -- 对数值
double T[5][5] = {
	   {0.1,0.6,0.1,0.1,0.1},
	   {0.1,0.1,0.6,0.1,0.1},
	   {0.1,0.1,0.1,0.6,0.1},
	   {0.2,0.2,0.2,0.2,0.2},
	   {0.2,0.2,0.2,0.2,0.2}};
// T[i][j] 单词 j 出现在 i 后面的概率
double M[5][5] = {
	   {0.8,0.1,0.0,0.1,0.0}, 
	   {0.1,0.7,0.0,0.2,0.0},
	   {0.0,0.1,0.8,0.0,0.1},
	   {0.0,0.0,0.0,0.5,0.5},
	   {0.0,0.0,0.0,0.5,0.5}};
int choice[6][6];  // 初始化为 1 

// 返回填满 Q[segment] 之后的剩余空间而能得到的最大 g() 乘积的对数值 
// 假定 Q[segment-1] = previousMatch 
double cache[11][11];
double recognize(int segment, int previousMatch) {
	if(segment == n) return 0;
	
	double& ret = cache[segment][previousMatch];
	if(ret != 1.0) return ret;
	
	ret = std::exp(-200); // log(0) 对应于 负无穷大
	int& choose = choice[segment][previousMatch];
	// 找出对应于 R[segment]的单词 
	for(int thisMatch=previousMatch+1; thisMatch<m; ++thisMatch) {
		if(previousMatch == -1) {
			// g(thisMatch) = T(previousMatch, thisMatch) * M(thisMatch, R[segment])
			double cand = T[previousMatch+1][thisMatch]
	  			   		+ M[thisMatch][ R[segment] ]
	  			   		+ recognize(segment+1, thisMatch);
			if(ret < cand) {
				ret = cand;
				choose = thisMatch;
			}
		}
	}
    return ret;
}

// 被输入单词的目录 
string corpus[] = {"I", "am", "a", "boy", "buy"};
string reconstruct(int segment, int previousMatch) {
	int choose = choice[segment][previousMatch];
 	cout << choose << endl;
	string ret = corpus[choose];
	if(segment < n-1)
	    ret = ret + "-" + reconstruct(segment+1, choose);
    return ret;
}

int main() {
	// 概率 对数处理 
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j) {
		    T[i][j] = std::log(T[i][j]);
		    M[i][j] = std::log(M[i][j]);
		}
	memset(cache, 1, sizeof(cache));
	
    n = 4; m = 5;

    cout << reconstruct(0, -1) << endl;

    return 0;
}
