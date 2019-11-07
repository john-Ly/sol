// C++ program for Huffman Coding
#include <iostream>
#include <vector>
using namespace std;

// ��������: �������ź���� locations ��, �Ƿ���ڷ���ʹ�����ѡ�� cameras ������
// ����������ļ�����ܴﵽ gap ����
bool decision(const vector<double>& locations, int cameras, double gap) {
	// ÿ���ܹ����������ʱ�������̰���㷨
	double limit = -1;
	int installed = 0;
	for(int i=0; i<locations.size(); ++i) {
		if(limit <= locations[i]) {
			++installed;
			// ������ location[i]+gap ֮���λ�ò��ܼ��������
			limit = locations[i] + gap; 
		}
	}
	// �����ܹ����� cameras �����ϵ�������ͳɹ�
	return installed >= cameras; 
}

double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	// ѭ������ʽ: decision(lo) && ��decision(hi)
	for(int it=0; it<100; ++it) {
		double mid = (lo + hi) / 2.0;
		// ����ܹ��ﵽ mid ����, ��𰸾�������[mid, hi]
		if(decision(location, cameras, mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main() {
	vector<double> locations {0, 70, 90, 120, 200, 210, 220, 240};
	int m = 4;
    cout << optimize(locations, m) << endl;
 
    return 0;
}
