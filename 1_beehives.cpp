#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
#include <stdio.h>
#include <map>
#include <stack>
#include <algorithm>

#define INF 1000000

//using namespace std;
int numTrees, numPaths;
int start[501], next[40001], to[40001], from[40001], visited[501], parent[501], m;


bool used[500];

void init() {
    memset(start, -1, sizeof(start));
    m = 0;
}

void add(int u, int v) {
    to[m] = v;
    from[m] = u;    
    next[m] = start[u];
    start[u] = m++;
}

int bfs(int src) {
    std::queue<int> q;

    int distance[501];
    for (int i = 0; i < 501; ++i) {
        distance[i] = INF;
    }
    
    int parent[501];
    distance[src] = 0;
    parent[src] = -1;

    q.push(src);
    int ret = INF;
    while (q.size()) {
        int curr = q.front(); q.pop();
        
        for (int e = start[curr]; ~e; e = next[e]) {
            int v = to[e];
            if (v == parent[curr]) continue;
            if (distance[v] == INF) {
                distance[v] = distance[curr] + 1;
                parent[v] = curr;
                q.push(v);
            } else {
                ret = std::min(distance[curr] + distance[v] + 1, ret);
            }
        }
        
    }
    
    return ret; 
}



int main() {
	

	int cases = 0;
	int lol;
	lol = scanf("%d", &cases);
	for (int test = 0; test < cases; test++) {
		init();
		
		lol = scanf("%d %d", &numTrees, &numPaths);
		int mn = INF;
		int u, v;

		for (int i = 0; i < numPaths; i++) {
            lol = scanf("%d %d", &u, &v);
            add(u, v);
            add(v, u);
                             
		}
		
        for (int i = 0; i < numTrees; ++i) 
            mn = std::min(bfs(i), mn);


	
		

		if (mn == INF) {
		    printf("Case %d: impossible\n", test + 1);
		} else {
		    printf("Case %d: %d\n", test + 1, mn);
		}
//		break;
//		if (test == 1) break;
   //     break;
        
	}
	return !lol;
}
