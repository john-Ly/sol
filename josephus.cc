#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

// use list
void josephus(int n, int k) {
	list<int> survivors;
	for(int i=1; i<=n; ++i) survivors.push_back(i);

	auto kill = survivors.begin();
	while(n>2) {
		kill = survivors.erase(kill);
		if(kill == survivors.end()) kill = survivors.begin();
		--n;

		// 移到 k-1 之后的士兵
		for(int i=0; i<k-1; ++i) {
			++kill;
			if(kill == survivors.end()) kill = survivors.begin();
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}

namespace jo_dp_que {
// 圆圈中剩下的数
// f[1] = 0
// f[i] = (f[i-1]+m) % i;  i>1
int LastRemaining_Solution(int n, int m) {
    if(n < 1 || m < 1){ return -1; }

    int last = 0;
    for(int i = 2; i <= n; i++){
        last = (last + m) % i;
    }
    return last;
}
void jose_queue(int n, int k) {
	queue<int> survivors;
	for(int i=0; i<n; ++i) survivors.push(i);

	while(survivors.size() > 1) {
		for(int i=0; i<k-1; ++i) {
			int tmp = survivors.front(); survivors.pop();
			survivors.push(tmp);
		}
		survivors.pop();
	}
	cout << survivors.front() << endl;
}
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

// @BAD
void jose_list(int n, int k) {
	list<int> survivors;
	for(int i=1; i<=n; ++i) survivors.push_back(i);

	while(n > 2) {
		survivors.pop_front(); n--;
        k = k % n; // @TODO 迭代器的间接 导致不能直接 处理k, 当k=3, n<3时 会出现问题
        auto nx = std::next(survivors.begin(), k-1);
        std::rotate(survivors.begin(), nx, survivors.end());
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}

int main() {
	int n = 40, k = 3;
	jose_queue(n, k);
	jose_list(n, k);
    josephus(n, k);

	return 0;
}