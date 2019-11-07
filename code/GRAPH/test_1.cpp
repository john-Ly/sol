#include<iostream>
#include<vector>
#include<list>
#include<utility>
using namespace std;

vector<vector<int> > adj;
vector<bool> visited;

void dfs(int here) {
    cout << "DFS visits " << here << endl;
    visited[here] = true;

    for(int i=0; i<adj[here].size(); ++i){
        int there = adj[here][i];
        if(!visited[there])
            dfs(there);
    }
}

void dfsAll() {
    visited = vector<bool>(adj.size(), false);
    for(int i=0; i<adj.size(); ++i){
        if(!visited[i])
            dfs(i);
}

int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'C'},
        {'A', 'D'},
        {'A', 'F'},
        {'B', 'C'},
        {'C', 'D'},
        {'E', 'G'},
        {'F', 'G'}};
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);

    adj.push_back();

}
