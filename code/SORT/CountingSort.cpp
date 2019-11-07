#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
void CountingSort(int *A,int *B,int *Order,int N,int K)
{
    int *C=new int[K+1];
    int i;
    memset(C,0,sizeof(int)*(K+1));
    for (i=1;i<=N;i++) //��A�е�ÿ��Ԫ�ط���
        C[A[i]]++;
    for (i=2;i<=K;i++) //ͳ�Ʋ�����i��Ԫ�صĸ���
        C[i]+=C[i-1];
    for (i=N;i>=1;i--)
    {
        B[C[A[i]]]=A[i]; //����ͳ�Ƶ�λ�ã���ֵ�����B�У���˳�������Order��
        Order[C[A[i]]]=i;
        C[A[i]]--;
    }
}
int main()
{
    int *A,*B,*Order,N=15,K=10,i;
    A=new int[N+1];
    B=new int[N+1];
    Order=new int[N+1];
    for (i=1;i<=N;i++)
        A[i]=rand()%K+1; //����1..K�������
    printf("Before CS:\n");
    for (i=1;i<=N;i++)
        printf("%d ",A[i]);
    CountingSort(A,B,Order,N,K);
    printf("\nAfter CS:\n");
    for (i=1;i<=N;i++)
        printf("%d ",B[i]);
    printf("\nOrder:\n");
    for (i=1;i<=N;i++)
        printf("%d ",Order[i]);
    return 0;
}
