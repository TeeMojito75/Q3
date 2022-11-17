#include <vector>
#include <queue>
#include <iostream>
using namespace std;

typedef vector<vector<int>> graph;

void topographical_sort(graph& G) {
	vector<int> pred(G.size(), 0);
	for (int i = 0; i < G.size(); ++i) {
		for (int j = 0; j < G[i].size(); ++j) {
			++pred[G[i][j]];
		}
	}

	priority_queue<int, vector<int>, greater<int>> order;
	for (int i = 0; i < G.size(); ++i) {
		if (pred[i] == 0) order.push(i);
	}
	while (not order.empty()) {
		cout << order.top();
		int x = order.top();
		order.pop();
		for (int i = 0; i < G[x].size(); ++i) {
			--pred[G[x][i]];
			if(pred[G[x][i]] == 0) order.push(G[x][i]);
		}
		if(not order.empty()) cout << " ";
	}
	cout << endl;
}

int main() {
	int n,m;

	while (cin >> n >> m) {
		int a,b;
		graph elems(n, vector<int>(0));

		for (int i = 0; i < m; ++i) {
			cin >> a >> b;
			elems[a].push_back(b);		// a should appear before b
		}
		topographical_sort(elems);
	}
}
