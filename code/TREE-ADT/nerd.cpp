#include <algorithm>
#include <map>
using namespace std;

// 保存当前不被其他点支配的点的目录 
map<int, int> coords;
bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
} 
