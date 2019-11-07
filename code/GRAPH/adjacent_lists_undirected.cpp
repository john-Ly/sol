/* #ifndef GRAPH_ADJACENT_LISTS_H */
/* #define GRAPH_ADJACENT_LISTS_H */

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <utility>
using namespace std;

// pair.first -> the edge's destination
// pair.second -> edge's weight
using edge = pair<int, int>;
using item = list<edge>;

// Adjacency List is a vector of list.
// Where each element is a pair<int, int>
class graph
{
private:
    struct vertex
    {
    	item entry;
    	string name;
        int id;

        vertex(int id, const string& name = "dummy")
          : id{ id }, name{ name } {
        }

        const string getVertexName() const{
            return this->name;
        }

        const int getVertexId() const{
            return this->id;
        }
        
        const int getsize() const{
            return this->entry.size();
        }
    };

public:
	graph(){}

    vector<vertex> adjacentList;
    mutable stack<int> ifTopoSort;
    
    void addVertex(string nameVertex){
        vertex v( numVertex(), nameVertex );
        adjacentList.push_back(v);
    }

    void addEdge(int id, int dest, int weight){
	    adjacentList[id].entry.push_back( std::make_pair(dest, weight) );
    }

    const int numVertex() const {
    	return adjacentList.size();
    }
    
    const int numRelatedVertex(int id) const {
    	return adjacentList[id].getsize();
    }

    const string whichVer(int id) const {
    	return adjacentList[id].getVertexName();
    }

	void dfs_driver(int here) const{
        int num = this->numVertex();
		vector<bool> visited = vector<bool>(num, false);
		// dfs(here, visited);
		dfsAll(visited);
	}
	
	// ways-1: using a visited array to store info
	void dfs(int here, vector<bool>& vi) const {
	    cout << "DFS visits vertex " << whichVer(here) << endl;
	    vi[here] = true;

		for (const auto i : this->adjacentList[here].entry) {
			int there = i.first;
	        if(!vi[there])
   			    dfs(there, vi);
	    }
	    
	    cout << "Pushing item: " << here << endl;
	    this->ifTopoSort.push(here);
	}
	
	void dfsAll(vector<bool>& vi) const {
	    for(int i=0; i<this->numVertex(); ++i){
	        if(!vi[i])
	            dfs(i, vi);
        	cout << (i+1) << "times to dfs" << endl;
        	// i+1 -- indicates the numbers of components in a graph. P 588
        }
	}
	
	// 11/09/16 08:37  
	// topological sort can conduct many reasonable results.(may against common sense) 
	void topologicalSort() const {
		dfs_driver(0);
		cout << endl;
		cout << "Topological Sort(ONLY IN DAG): " << endl;
		while(this->ifTopoSort.size()) {
 		    cout << this->ifTopoSort.top()+1 << " ";
		    ifTopoSort.pop();
		}
	}
	
	bool hasCycle(){
		return false;
	}
	
	/*
	vector<int> bfs_driver(int start) {
        int num = this->numVertex();
		vector<bool> discovered = vector<bool>(num, false);
		queue<int> q;
		// dfs(here, visited);
		return bfs(start, discovered);
	}
	
	vector<int> bfs(int start, vector<bool>& discovered) {
		static queue<int> q;
		static vector<int> order;
		discovered[start] = true;
		q.push(start);
		while(!q.empty()) {
			int here = q.front();
			q.pop();
			// access here
			order.push_back(here);
			for(int i=0; i<this->numRelatedVertex(here); ++i) {
				int there = 
			}
		}
	}
	*/

    void display(){
    	cout << "Adjacent List Graph:" << endl;
		for (const auto v : adjacentList) {
		    cout << v.getVertexId() << "(" << v.getVertexName() << "): ";
		    for (const auto i : v.entry) {
		    	int dest = i.first;
		    	cout << dest << "(" << whichVer(dest) << ") ";
		    }
		    cout << endl;
		}
    }
};

int main()
{
	graph gr;
	// For DFS
	gr.addVertex("1"); gr.addEdge(0, 1, 0);
	gr.addVertex("2"); gr.addEdge(1, 2, 0);
	gr.addVertex("3"); gr.addEdge(2, 3, 0);
	gr.addVertex("4"); gr.addEdge(3, 4, 0);
	gr.addVertex("5");
	gr.addVertex("6"); gr.addEdge(5, 6, 0); gr.addEdge(5, 7, 0); gr.addEdge(5, 8, 0);
	gr.addVertex("7"); gr.addEdge(6, 0, 0);
	gr.addVertex("8"); gr.addEdge(7, 1, 0);
	gr.addVertex("9"); gr.addEdge(8, 3, 0);
	gr.addVertex("10"); gr.addEdge(9, 2, 0);

//	gr.addVertex("0");
//	gr.addVertex("1");
//	gr.addVertex("2"); gr.addEdge(2, 3, 0);
//	gr.addVertex("3"); gr.addEdge(3, 1, 0);
//	gr.addVertex("4"); gr.addEdge(4, 0, 0); gr.addEdge(4, 1, 0);
//	gr.addVertex("5"); gr.addEdge(5, 0, 0); gr.addEdge(5, 2, 0);

	// For BFS
//	gr.addVertex("0"); gr.addEdge(0, 1, 0); gr.addEdge(0, 2, 0); gr.addEdge(0, 3, 0);
//	gr.addVertex("1");
//	gr.addVertex("2"); gr.addEdge(2, 3, 0);
//	gr.addVertex("3"); gr.addEdge(3, 1, 0);
//	gr.addVertex("4"); gr.addEdge(4, 0, 0); gr.addEdge(4, 1, 0);
//	gr.addVertex("5"); gr.addEdge(5, 0, 0); gr.addEdge(5, 2, 0);
	
    gr.display();
    
	cout << endl;
    
    //gr.dfs_driver(0);
    gr.topologicalSort();

    return 0;
}

//#endif
