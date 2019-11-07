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
    for (i=1;i<=N;i++) //把A中的每个元素分配
        C[A[i]]++;
    for (i=2;i<=K;i++) //统计不大于i的元素的个数
        C[i]+=C[i-1];
    for (i=N;i>=1;i--)
    {
        B[C[A[i]]]=A[i]; //按照统计的位置，将值输出到B中，将顺序输出到Order中
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
        A[i]=rand()%K+1; //生成1..K的随机数
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
