#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> edge;
typedef vector<edge> adjacency_list;
typedef vector< adjacency_list> weighted_graph;

void Prim_algorithm(const weighted_graph& G, int& MST_weight) {
	vector<bool> visited(G.size(), false);	// none have been visited yet
	priority_queue <edge, vector<edge>, greater<edge>> candidates;	// where the first member of the edge represents it's weight, and the second the vertex it arrives to
	visited[0] = true;

	for (auto w : G[0]) candidates.push(w);
	int size = 1;

	while (size < G.size()) {
		int a = candidates.top().first;		// weight
		int b = candidates.top().second;	// vertex

		candidates.pop();

		if (not visited[b]) {
			visited[b] = true;

			for (auto q : G[b]) candidates.push(q);
			MST_weight += a;
			++size;
		}
	}
}

int main() {
	int n, m;

	while (cin >> n >> m) {
		int a,b,c;
		weighted_graph G(n);
		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> c;
			G[a - 1].push_back(edge(c,b - 1));		// dirección de arco con su peso
			G[b - 1].push_back(edge(c,a - 1));		// dirección de arco con su peso
		}
		int MST_weight = 0;
		Prim_algorithm(G, MST_weight);

		cout << MST_weight << endl;
	}
}
