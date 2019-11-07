#include <iostream>
using namespace std;

// @TODO 此问题 可以看作背包问题  但是没有更进一步
// 因为输出了76中情况  虽然比全部的搜索空间小(暴力搜索)

#define N 7
int c1=152, c2=130;
int w[N]={90,80,40,30,20,12,10};
int x[N]={0};
int cnt=0;
int cw=0;
int best=0;

void backtrack(int depth) {
    if(depth == N) {
        for (int j=0; j<N; j++)
            cout << x[j] << ' ';
        cout << '\n';
        cnt++;
        if(cw > best) best = cw; // best要无限接近c1
        return;
    }

    // 一个货物只有存在和不存在两种情况
    if(cw+w[depth]<=c1) {  // w[depth] 货物可以存在
        x[depth] = 1; cw += w[depth];
        backtrack(depth+1);
        x[depth] = 0; cw -= w[depth];
    }
    backtrack(depth+1);    // w[depth] 不存在
}

/*
void Loading::getBest()
{
    init();
    backTrack(1);
    cout<<"the best = "<<best<<endl;
    delete[] w;
}

void Loading::init()
{
    cout<<"Please input n: ";
    cin >> n;
    cout<<"Please input the weight of the first ship: ";
    cin>>c;
    cout<<"Please input the weight of every packet: ";
    w = new int[n+1];
    w[0] = 0;
    for(int i = 1; i <= n; i++)
        cin>>w[i];

    cw = 0;
    best = 0;
}

void Loading::backTrack(int i)
{
    if(i > n)
    {
        if(cw > best)
            best = cw;
        return;
    }
    if(cw + w[i] <= c)
    {
        cw += w[i];
        backTrack(i+1);
        cw -= w[i];
    }
    backTrack(i+1);
}
*/

void sub(int depth) {
    if(depth == N) {
        for (int j=0; j<N; j++)
            cout << x[j] << ' ';
        cout << '\n';
        cnt++;
        if(cw > best) best = cw; // best要无限接近c1
        return;
    }

    // 一个货物只有存在和不存在两种情况
    if(cw+w[depth]<=c1) {  // w[depth] 货物可以存在
        x[depth] = 1; cw += w[depth];
        backtrack(depth+1);
        x[depth] = 0; cw -= w[depth];
    }
    backtrack(depth+1);    // w[depth] 不存在
}





// 总共有 2^7 = 128 中可能
int main() {
    backtrack(0);
    cout << cnt <<" case, and the best = "<<best<<endl;

    return 0;
}