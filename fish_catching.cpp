#include <iostream>
#include <cstring> // memset()
using namespace std;

// http://www.ahathinking.com/archives/112.html
/*
  20个桶，每个桶中有10条鱼，用网从每个桶中抓鱼，每次可以抓住的条数随机
  每个桶只能抓一次，问一共抓到180条的排列有多少种>

      假设我们在前i个桶中抓取了k（0<=k<=10*i）条鱼
      那么抓取180条鱼的排列种数就等于在剩下的（20-i）个桶中
      抓取（180-k）条鱼的方法加上前i个桶中抓取k条鱼的方法。

  可以考虑对偶问题 减少问题的规模

  >>> 将20条鱼分到20个桶中有多少中不同的排列方法

 */

const int up_bound = 10;

// 存储子问题的解; 表示前i个桶放j条鱼的方法数
long cache[21][21];
int allocate(int bucketN, int fishN) {
	long& ret = cache[bucketN][fishN];
    // 0个桶 没法装鱼
	if (bucketN == 0)  {
        if(fishN == 0) return ret = 1;
        else return ret = 0;
    }

	if(ret != -1) return ret;
	ret = 0;
	for (int i=0; i<=up_bound; i++) {
        if (fishN-i < 0) break; // 鱼如果没了 就不要在算了
		ret += allocate(bucketN-1, fishN-i);
    }

	return ret;
}

int main( ) {
	memset(cache, -1, sizeof(cache));
	int bucketN = 20;
	int fishN = 20; // 20   对偶问题

    long ret = allocate(bucketN, fishN);
    cout << "result is " << ret << endl;

    return 0;
}
