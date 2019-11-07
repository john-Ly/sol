#include <iostream>
#include <list>
#include <queue>
using namespace std;

// use list
void josephus(int n, int k) {
	list<int> survivors;
	for(int i=1; i<=n; ++i) survivors.push_back(i);
	
	// 表示当前自尽者的指针
	list<int>::iterator kill = survivors.begin();
	while(n>2) {
		// 第一个士兵自尽 erase()将返回已删除元素的下一个元素
		kill = survivors.erase(kill);
		if(kill == survivors.end())
			kill = survivors.begin();
		--n;
		
		// 移到 k-1 之后的士兵
		for(int i=0; i<k-1; ++i) {
			++kill;
			if(kill == survivors.end())
				kill = survivors.begin();
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}

void jose_queue(int n, int k) {
	queue<int> survivors;
	for(int i=1; i<=n; ++i) survivors.push(i);
	
	while(survivors.size() > 2) {
		survivors.pop();
		for(int i=0; i<k-1; ++i) {
			int tmp = survivors.front(); survivors.pop();
			survivors.push(tmp);
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}

int main() {
	int n = 40, k = 3;
	jose_queue(n, k);
	
	return 0;
}