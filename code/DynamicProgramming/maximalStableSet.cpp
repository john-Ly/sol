#include <iostream>
#include <bitset>
#include <string>
using namespace std;

// http://en.cppreference.com/w/cpp/utility/bitset/bitset

int n;
int explodes[4] = {	2,  1,  8,  4 };
				// 0010   1000
				   // 0001    0100

// ȷ�ϸ������ϵ��ȶ��� 
bool isStable(int set) {
	for(int i=0; i<n; ++i)
		// ����������ÿһ��Ԫ��
		//   ����Ԫ�� i        �Ƿ����Ԫ�� i �� *����*
		// �����0 ���� 1<<i 
	    if( (set & (1<<i)) && (set & explodes[i]) ) {
/*	    	std::bitset<4> b1(set & (1<<i));
	    	std::bitset<4> b2(set & explodes[i]);
	    	cout << i << " " << b1 << " "<< b2 << endl;*/
   		    return false;
		}
    return true;
}

// �����������ȶ����ĸ��� 
int countStableSet() {
	int ret = 0;
	// �������м��� n=4 ��2^4-1= 15�� 
	for(int set=1; set < (1<<n); ++set) {
		if(!isStable(set)) continue;
		// ȷ���Ƿ�������ȶ���֮ǰ, ��Ҫȷ�ϻ���û�пɷ��������
		bool canExtend = false;
		for(int add=0; add<n; ++add)
				// ������ add Ԫ��          ������ add Ԫ�ص� ���� 
		    if( (set & (1<<add)) == 0 && (set & explodes[add]) == 0 ) {
		    	canExtend = true;
		    	break;
			}
		if(!canExtend) ++ret;
	}
	return ret;
}

int main() {
	n = 4;
	// http://en.cppreference.com/w/cpp/io/manip/boolalpha
	cout << boolalpha << isStable(13) << endl;
	cout << countStableSet() << endl;

    return 0;
}
