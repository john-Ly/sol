#include <iostream>
#include <vector>
#include <cmath>    // log()
#include <cstring> // memset()
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
/////////////////////// 
// @TODO δ�� ����
/////////////////////// 
 
// ������ת���� ����ͼ �߼�ԾǨ�ĸ���
int n, m;
// ���������صľ���
int R[] = {0, 1, 2, 3, 4};
// T[i][j] ���� j ������ i ����ĸ��� -- ����ֵ
double T[5][5] = {
	   {0.1,0.6,0.1,0.1,0.1},
	   {0.1,0.1,0.6,0.1,0.1},
	   {0.1,0.1,0.1,0.6,0.1},
	   {0.2,0.2,0.2,0.2,0.2},
	   {0.2,0.2,0.2,0.2,0.2}};
// T[i][j] ���� j ������ i ����ĸ���
double M[5][5] = {
	   {0.8,0.1,0.0,0.1,0.0}, 
	   {0.1,0.7,0.0,0.2,0.0},
	   {0.0,0.1,0.8,0.0,0.1},
	   {0.0,0.0,0.0,0.5,0.5},
	   {0.0,0.0,0.0,0.5,0.5}};
int choice[6][6];  // ��ʼ��Ϊ 1 

// �������� Q[segment] ֮���ʣ��ռ���ܵõ������ g() �˻��Ķ���ֵ 
// �ٶ� Q[segment-1] = previousMatch 
double cache[11][11];
double recognize(int segment, int previousMatch) {
	if(segment == n) return 0;
	
	double& ret = cache[segment][previousMatch];
	if(ret != 1.0) return ret;
	
	ret = std::exp(-200); // log(0) ��Ӧ�� �������
	int& choose = choice[segment][previousMatch];
	// �ҳ���Ӧ�� R[segment]�ĵ��� 
	for(int thisMatch=previousMatch+1; thisMatch<m; ++thisMatch) {
		if(previousMatch == -1) {
			// g(thisMatch) = T(previousMatch, thisMatch) * M(thisMatch, R[segment])
			double cand = T[previousMatch+1][thisMatch]
	  			   		+ M[thisMatch][ R[segment] ]
	  			   		+ recognize(segment+1, thisMatch);
			if(ret < cand) {
				ret = cand;
				choose = thisMatch;
			}
		}
	}
    return ret;
}

// �����뵥�ʵ�Ŀ¼ 
string corpus[] = {"I", "am", "a", "boy", "buy"};
string reconstruct(int segment, int previousMatch) {
	int choose = choice[segment][previousMatch];
 	cout << choose << endl;
	string ret = corpus[choose];
	if(segment < n-1)
	    ret = ret + "-" + reconstruct(segment+1, choose);
    return ret;
}

int main() {
	// ���� �������� 
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j) {
		    T[i][j] = std::log(T[i][j]);
		    M[i][j] = std::log(M[i][j]);
		}
	memset(cache, 1, sizeof(cache));
	
    n = 4; m = 5;

    cout << reconstruct(0, -1) << endl;

    return 0;
}
