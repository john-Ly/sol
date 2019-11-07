#include <iostream>
#include <vector>
#include <cstring> // memset()
using namespace std;

vector<int> b { 10, 22, 9, 33, 21, 50, 41, 60 };
vector<int> a { 4, 2, 3, 7, 6, 9, 8, 10 };
int cnt;

int cache[11], choices[11];
// choices[i] = 存放S[i...]的最大的lis中下一个index的值
int lis4(int start) {
	int& ret = cache[start+1];
	if(ret != -1) return ret;

	ret = 1;
	int bestNext = -1;
	for(int next=start+1; next<a.size(); ++next) {
	    if(start == -1 || a[start]<a[next]) {
	    	int cand = lis4(next) + 1;
	    	if(cand > ret) {
                cnt++;
	    		ret = cand;
	    		bestNext = next;
			}
		}
		//  ret = MAX(ret, 1+lis2(next));
		// 只要在这个特殊路径进行标记 标记的是 顺序(序号)
	}
    // cout << bestNext << ' ';
	choices[start+1] = bestNext;
	return ret;
}

int lis5(int start) {
	int& ret = cache[start];
	if(ret != -1) return ret;

	ret = 1;
	int bestNext = -1;
	for(int next=start+1; next<a.size(); ++next) {
	    if(a[start]<a[next]) {
	    	int cand = lis5(next) + 1;
	    	if(cand > ret) {
	    		ret = cand;
	    		bestNext = next;
			}
		}
		//  ret = MAX(ret, 1+lis2(next));
		// 只要在这个特殊路径进行标记 标记的是 顺序(序号)
	}
    cout << bestNext << ' ';
	choices[start] = bestNext;
	return ret;
}

// choice实质维护一个静态链表
void reconstruct(int start, vector<int>& seq) {
	if(start != -1) seq.push_back(a[start]);
	int next = choices[start+1];
	if(next != -1) reconstruct(next, seq);
}

int main() {
	memset(cache, -1, sizeof(cache));
    // int maxLen = 0;
    // for(int i=0; i<a.size(); i++) {
    //     auto t = lis5(i);
    //     if(t>maxLen) maxLen = t;
    // }
    int maxLen = lis4(-1) - 1;

    cout << "longest: " << maxLen << endl;

    // cout << "choices: ";
    // for(int i=0; i<11; i++) {
    //     cout << choices[i] << " ";
    // }
    // cout << endl;
    // cout << cnt << endl;

    vector<int> tmp;
    reconstruct(-1, tmp);
    for(auto i : tmp) cout << i << " ";
    cout << endl;

    return 0;
}