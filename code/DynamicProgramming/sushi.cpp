#include <iostream>
#include <vector>
#include <cstring> // memset()
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_BUDGET 20000

int n = 6;  // ��Ʒ������
int m;      // �ʽ�Ԥ�� 
int price[6] = {2500, 3000, 4000, 5000, 10000, 15000};  // ��Ʒ�ļ۸� 
int pref[6] = {7, 9, 10, 12, 20, 1};                    // ��Ʒ�ĵȼ� 
string name[6] = {"egg", "fish-1", "fish-2", "fish-3", "cow", "chicken"};
int cache[MAX_BUDGET+1];

// Ԥ��Ϊ budget ʱ�ܹ��ó������ȼ�֮�� 
int sushi(int budget) {
	int& ret = cache[budget];
	if(ret != -1) return ret;
	
	ret = 0; 
	for(int dish=0; dish<n; ++dish) {
		if(budget < price[dish]) continue;
		ret = MAX(ret, sushi(budget-price[dish]) + pref[dish] );
	}
    return ret;
}

int cache[MAX_BUDGET+1];
// �������� 
int sushi2() {
	ret = 0;
	for(int budget=1; budget<=m; ++budget) {
		c[budget] = 0;
		for(int dish=0; dish<n; ++dish) {
			if(budget >= price[dish])
				c[budget] = MAX(c[budget], c[budget-price[dish]] + pref[dish] );
		}
		ret = MAX(ret, c[budget]);
	} 
    return ret;
}

int main( ) {
	memset(cache, -1, sizeof(cache));
	m = 543975612;
	
    cout << sushi(budget) << endl;

    return 0;
}
