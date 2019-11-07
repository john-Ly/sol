#include <iostream>
#include <vector>
using namespace std;

// http://blog.csdn.net/morewindows/article/details/8029996

/*
�鲢���� ����������� A ��������
1. ���������зֳ� L �� R �������� ��ʱ A �����������������
   a. ���������� L ��
   b. ���������� R ��
   c. �ϴ����ֵ�� L ��, ��С����ֵ�� R ��
2. a,b ���η�����
   �����ź���� L �� R ���й鲢����, ��ʣ��� R �ĵ�һ����ֵС��ʣ��� L �ĵ�һ����ֵ
   ������ĸ����͵��� L ��ʣ����ֵ�ĸ��� 
*/ 

// ���õݹ鷽ʽ�� A[left...right]���й鲢����
// ������Ӧ��Χ�� inversion ���� = ���������ƶ����� 
long long countMove(vector<int>& A, int left, int right) {
	// ��ʼ����: ���䳤�ȵ����������, �Ҳ������ inversion
	if(left == right) return 0;
	
	// �ָ��������ʹ�÷��η� 
	int mid = (left + right) / 2;
	long long ret = countMove(A, left, mid) + countMove(A, mid+1, right);
	
	// �ϲ���������ʱ���������������
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while(leftIndex <= mid || rightIndex <= right) {
		if(leftIndex <= mid && 
	 		(rightIndex > right || A[leftIndex] <= A[rightIndex])
					 ) {
			tmp[tmpIndex++] = A[leftIndex++];
 		} else {
 			// A[rightIndex]С������������е�����ʣ����ֵ
			// ����Щ��ֵ�ĸ�����ӵ� inversion
			ret += mid - leftIndex + 1;  		// ���merge_sort �ص㿼�ǣ����� 
			tmp[tmpIndex++] = A[rightIndex++];
 		}
	}
	for(int i=0; i<tmp.size(); ++i)
		A[left + i] = tmp[i];
	return ret;
}

int countNative(vector<int>& a) {
	int n = a.size(), cnt = 0;  
    int i, j;
    for (i = 0; i < n; i++)  
        for (j = i + 1; j < n; j++)  
            if (a[i] > a[j])
                cnt++;
    return cnt;
}

int main() {
	vector<int> a{5, 1, 4, 3, 2};
	cout << countNative(a) << endl;
	cout << countMove(a, 0, a.size()-1) << endl;
	for(auto i : a)
 		cout << i << " ";

	return 0;
}
