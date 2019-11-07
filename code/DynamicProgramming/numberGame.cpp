#include <iostream>
#include <vector>
#include <algorithm>  // max, sort
#include <utility>  // pair
#include <cstring> // memset()
using namespace std;

const int EMPTY = -987654321;
int n, board[15] = {7, -5, 8, 5, 1, -4, -8, 6, 7, 9};

int cache[15][15];
int play(int left, int right) {
	//初始部分 : 棋盘上没有数字
	if(left > right) return 0;
	
	int& ret = cache[left][right];
	if(ret != EMPTY) return ret;
	
	ret = max(board[left] - play(left+1, right),
 		board[right] - play(left, right - 1));
 		
	if(right - left + 1 >= 2) {
		ret = max(ret, -play(left+2, right));
		ret = max(ret, -play(left, right-2));
	}
	
	return ret;
}

int main() {
	memset(cache, EMPTY, sizeof(cache));
    n = 10;
 
    cout << play(0, 9) << endl;

    return 0;
}
