#include <algorithm>
#include <map>
using namespace std;

// ���浱ǰ����������֧��ĵ��Ŀ¼ 
map<int, int> coords;
bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
} 
