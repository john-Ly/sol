#include <iostream>
#include <bitset>
#include <queue>
#include <algorithm>
#include <cstring> // memset()
using namespace std;

// 测试通过 

// Assuming n-th disk is bottom disk (count down)
void tower(int n, char sourcePole, char destinationPole, char auxiliaryPole) {
   // Base case (termination condition)
   if(0 == n)
     return;
 
   // Move first n-1 disks from source pole
   // to auxiliary pole using destination as
   // temporary pole
   tower(n-1, sourcePole, auxiliaryPole,
      destinationPole);
 
 	// Move the remaining disk from source
    // pole to destination pole
    cout << "Move the disk " << n << "from " << sourcePole << " to " << destinationPole << endl;
 
   // Move the n-1 disks from auxiliary (now source)
   // pole to destination pole using source pole as
   // temporary (auxiliary) pole
   tower(n-1, auxiliaryPole, destinationPole, sourcePole);
}

const int MAX_DISCS = 12;
int get(int state, int index) {
	return (state >> (index*2)) & 3;
}

int set(int state, int index, int value) {
	return (state & ~(3 << (index*2))) | (value << (index*2));
}

int c[1<<(MAX_DISCS*2)];
// 有 discs 个圆盘, 各圆盘的起始位置和目标位置
// 保存于 begin和end时, 计算最少移动次数
//
// 使用1个 int 型整数 表示状态  (1个盘子在哪个柱子 可以使用两位; 12个盘子 最多占用24位)
int bfs(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	memset(c, -1, sizeof(c));
	
	q.push(begin);
	c[begin] = 0;
	
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		// 计算位于每根柱子顶端的圆盘序号
 		int top[4] = {-1, -1, -1, -1};
 		for (int i=discs-1; i>=0; i--)
 			top[get(here, i)] = i;
		// 把位于第 i 根柱子顶端的圆盘移动到第 j 根柱子上
 		for (int i=0; i<4; i++)
			// 第 i 根柱子上必须有圆盘
			if(top[i] != -1)
			    for(int j=0; j<4; ++j)
				// 第 j 根柱子必须为空, 或顶端圆盘更大
				    if (i != j && (top[j] == -1 || top[j] > top[i])) {
			   	        int there = set(here, top[i], j);
			   	        if(c[there] != -1) continue;
			   	        c[there] = c[here] + 1;
			   	        if (there == end) return c[there];
			   	        q.push(there);
				    }
	}
	// error
	cout << "error" << endl;
	return -1;
}

int sgn(int x) {
	if(!x) return 0;
	return x>0 ? 1 : -1;
}

// 绝对值+1 
int incr(int x) {
	if(x<0) return x-1;
	return x+1;
}

int bidir(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	// 注意初始化为 0; -1被使用 
	memset(c, 0, sizeof(c));
	
	q.push(begin); c[begin] = 1;
	q.push(end); c[end] = -1;
	
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		// 计算位于每根柱子顶端的圆盘序号
 		int top[4] = {-1, -1, -1, -1};
 		for (int i=discs-1; i>=0; i--)
 			top[get(here, i)] = i;
		// 把位于第 i 根柱子顶端的圆盘移动到第 j 根柱子上
 		for (int i=0; i<4; i++)
			// 第 i 根柱子上必须有圆盘
			if(top[i] != -1)
			    for(int j=0; j<4; ++j)
				// 第 j 根柱子必须为空, 或顶端圆盘更大
				    if (i != j && (top[j] == -1 || top[j] > top[i])) {
			   	        int there = set(here, top[i], j);
			   	        // 如果是尚未访问到的点 
			   	        if(c[there] == 0) {
			   	        	c[there] = incr(c[here]);
			   	        	q.push(there);
						} else if (sgn(c[there]) != sgn(c[here]))
						    return abs(c[there]) + abs(c[here]) - 1;
				    }
	}
	// error
	cout << "error" << endl;
	return -1;
}

int main() {
	// recursion hanoi
    // tower(3, 'S', 'D', 'A');
    
    // bfs
    //int discs = 3;
/*  std::bitset<6> b1("100010");
    int begin = b1.to_ulong();
    std::bitset<6> b2("111111");
    int end = b2.to_ulong();*/

    int discs = 10;
    std::bitset<20> b3("11110000100101101011");
    int begin = b3.to_ulong();
    std::bitset<20> b4("11111111111111111111");
    int end = b4.to_ulong();

/* 	int top[4] = {-1, -1, -1, -1};
	for (int i=discs-1; i>=0; i--) {
		cout << get(begin, i) << endl;
		top[get(here, i)] = i;
	}*/
	/* 
	top[0] = 1          |    |   |0   |
	op[2] = 0          | 1  |   |2   |
	*/ 
	
	cout << bfs(discs, begin, end) << endl;
	cout << bidir(discs, begin, end) << endl;
    return 0;
}
