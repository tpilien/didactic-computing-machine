#include <iostream>
#include <cmath>

#define INF 1000000000

using namespace std;

int trees[500][500];

void init() {
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
		  trees[i][j] = INF;
		}
	}

}

int main() {
	

	int cases = 0;
	cin >> cases;
	for (int test = 0; test < cases; test++) {
		init();
		int numTrees, numPaths;
		cin >> numTrees >> numPaths;
		int from, to;
		for (int i = 0; i < numPaths; i++) {
      cin >> from >> to;
      trees[from][to] = 1;
      trees[to][from] = 1;
		}


	}
	return 0;
}
