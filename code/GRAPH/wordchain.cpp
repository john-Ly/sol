#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Directed Graph
// for find the Euler circle, use adjacency matrix
// the content in each cell shoulb be represent the numbers of edge between two vertexes
vector<vector<int> > adj;
vector<int> indegree, outdegree;
vector<string> graph[26][26];

// make a directed graph   a --> b
void makeGraph(const vector<string>& words) {
	for(int i=0; i<26; i++)
	    for(int j=0; j<26; j++)
		    graph[i][j].clear();
		    
	adj = vector<vector<int> >(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);
	for(int i=0; i<words.size(); i++) {
		int a = words[i][0] - 'a';					// the first letter
		int b = words[i][words[i].size()-1] - 'a';  // the last letter
		
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

void getEulerCircuit(int here, vector<int>& circuit) {
	for(int there=0; there<adj.size(); ++there)
        while(adj[here][there] > 0){
        	adj[here][there]--;
        	getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit(){
	vector<int> circuit;
    // Euler Trail (locate the start)
    // the start point : outdegree[i] == indegree[i]+1
	for(int i=0; i<26; ++i)
        if(outdegree[i] == indegree[i]+1) {
            getEulerCircuit(i, circuit);
            return circuit;
        }

    // Euler circle : can start any point
	for(int i=0; i<26; ++i)
        if(outdegree[i]) {
            getEulerCircuit(i, circuit);
            return circuit;
        }

    // or nothing 
	return circuit;
	// actually is the copy of circuit(space-wasted) 
}

string solve(const vector<string>& words) {
    makeGraph(words);
    vector<int> circuit = getEulerTrailOrCircuit();
    
//    for(auto i : circuit){
// 		cout << i << "-";
// 	}                       actually the times of resursively call.
    
    // common sense
    if(circuit.size() != words.size()+1)
        return "IMPOSSIBLE";
    std::reverse(circuit.begin(), circuit.end()); // from <algorithm>

    string ret;
    for(int i=1; i<circuit.size(); i++) {
        int a = circuit[i-1], b = circuit[i];
        if(ret.size()) ret += "";
        ret += graph[a][b].back();
        graph[a][b].pop_back();
    }
    return ret;
}

int main() {
    vector<string> words;
//    words.push_back("dog");
//    words.push_back("god");
//    words.push_back("dragon");
//    words.push_back("need");
    words.push_back("aa");
    words.push_back("ab");
    words.push_back("bb");
    
    cout << solve(words) << endl;

    return 0;
}
