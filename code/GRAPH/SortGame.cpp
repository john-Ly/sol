#include <iostream>
#include <vector>
#include <queue>
#include <map>  // map 中的 key 必须是排列好的 map<vector<int>, int> vector 能够比较大小 
#include <algorithm>
#include <cmath>
using namespace std;

// 测试通过 

// instance-1
// 为了排序 perm 需要执行反转运算的最少次数 
int sortGame(const vector<int>& perm) {
	int n = perm.size();
	vector<int> sorted = perm;
	// 实现计算目标顶点 
	sort(sorted.begin(), sorted.end());
	
	queue<vector<int> > q;
	map<vector<int>, int> distance;
	
	distance[perm] = 0;
	q.push(perm);
	
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		
		if(here == sorted) return distance[here];
		int cost = distance[here];
		
		// *实时生成结构边线* ----  实际上是 所有边线的全排列(Permutation)
		// i j 起点和终点 两个循环 
		for(int i=0; i<n; ++i)
		    for(int j=i+2; j<=n; ++j) {
		    	// reverse 左闭右开 -- 所以 j可以 <= n
			    reverse(here.begin()+i, here.begin()+j);
			    // filter for the duplication
			    if(distance.count(here) == 0) {
			    	distance[here] = cost + 1;
			    	q.push(here);
				}
				// for each pass, start the original order
		    	reverse(here.begin()+i, here.begin()+j);
			}
	}
	// error
	return -1;
}

// instance-2
// 状态空间 --- 双向图 
map<vector<int>, int> toSort;
// 对 [0, ..., n-1]的所有排列求出 toSort[] 并保存
// 要对所有的 排列可能 进行存储, 有N!种 
// 然后进行 "保持比例" 的映射 

// 先存储所有的结果 -- 动态规划中的制表法 
void precalc(int n) {
	vector<int> perm(n);
	for(int i=0; i<n; ++i)
	    perm[i] = i;
	
	queue<vector<int> > q;
	q.push(perm);
	toSort[perm] = 0;
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];
		
		// 实时生成结构边线 
		for(int i=0; i<n; ++i) {
		    for(int j=i+2; j<=n; ++j) {
			    reverse(here.begin()+i, here.begin()+j);
			    // filter for the duplication
			    if(toSort.count(here) == 0) {
			    	toSort[here] = cost + 1;
			    	q.push(here);
				}
				// for each pass, start the original order
		    	reverse(here.begin()+i, here.begin()+j);
			}
		}
	}
}

int solve(const vector<int>& perm) {
	// 将perm 变换成 [0, ..., n-1] 
	int n = perm.size();
	vector<int> fixed(n);
	
	// 将大小关系 进行映射
	for(int i=0; i<n; ++i) {
		int smaller = 0;
		for(int j=0; j<n; ++j) {
			if(perm[j] < perm[i])
			    ++smaller;
		}
		// 有点类似插入排序(找出所有的逆序数)---这个程序 找出比当前数 i 小的 
		fixed[i] = smaller;
		// 0...n-1 排列数也是比较多 
	}
	
	// 映射成功后 查表
	// binary_search 效率还算高 
	return toSort[fixed];
}

// instance-3
// 使用 双向搜索法 -- 因为状态空间是 双向图 
// 返回 x 的符号 
int sgn(int x) {
	if(!x) return 0;
	return x>0 ? 1 : -1;
}

// 绝对值+1 
int incr(int x) {
	if(x<0) return x-1;
	return x+1;
}

// distance 记录 所有点到起点的距离 可以看做一个记录表 
int bidirectional(const vector<int>& perm) {
	int n = perm.size();
	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());
	if(perm == sorted) return 0;
	
	queue<vector<int> > q;
	map<vector<int>, int> distance;
	
	q.push(perm); distance[perm] = 1;
	q.push(sorted); distance[sorted] = -1;
	
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		
		int cost = distance[here];
		
		// 实时生成结构边线 
		for(int i=0; i<n; ++i) {
		    for(int j=i+2; j<=n; ++j) {
			    reverse(here.begin()+i, here.begin()+j);
			    // filter for the duplication
			    if(distance.count(here) == 0) {
			    	distance[here] = incr(cost);
			    	q.push(here);
				}
				// 相遇时 (用正负数区分搜索的正向和逆向 故初值为 1)
				else if( sgn(distance[here]) != sgn(cost) )
			        return abs(distance[here]) + abs(cost) - 1;
		    	reverse(here.begin()+i, here.begin()+j);
			}
		}
	}
	// error
	cout << "error" << endl;
	return -1;
}

// instance-4
// Iteratively Deeping Search, IDS
// BFS: 有 保存将要访问的顶点的目录
// DFS: 发现新顶点立即访问 不会发生队列占用太多空间 
// 使用 栈---可能对于两个结点访问的次数很多 但是有栈的深度限制
int best; 
void dfs(vector<int>& start, const vector<int>& finish, int steps) {
    int n = start.size();
	if(steps >= best) return;
	if(start == finish) {
		best = steps; return;
	}

	for(int i=0; i<n; ++i) {
	    for(int j=i+2; j<=n; ++j) {
		    reverse(start.begin()+i, start.begin()+j);
		    dfs(start, finish, steps+1);
		    reverse(start.begin()+i, start.begin()+j);
		}
	}
}

int ids(vector<int>& start, const vector<int>& finish, int growthStep) {
	for(int limit=4; ; limit += growthStep) {
		best = limit + 1;
		dfs(start, finish, 0);
		if(best <= limit)
		    return best;
	}
	return -1;
}

int main() {	
	vector<int> v({3, 4, 1, 2});
//	vector<int> v({1, 2, 3, 4, 8, 7, 6, 5});

    // instance-1 : time-0.03198s
	cout << "BFS:" << endl;
	cout << sortGame(v) << endl;
	
	// instance-2
	cout << "BFS faster version:" << endl;
	precalc(v.size());
	cout << solve(v) << endl;
	
	// instance-3 : time-0.03128s
	cout << "bidirectional:" << endl;
	cout << bidirectional(v) << endl;
	
	// instance-4 : time-0.008558s  time-0.008006s   time-0.00876s
	vector<int> finish(v);
	sort(finish.begin(), finish.end());
	cout << "Iteratively Deepening Search:" << endl;
	cout << ids(v, finish, 2) << endl;

    return 0;
}
