#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e8;
typedef pair<int,int> PI;
typedef vector<PI> VPI;
typedef vector<VPI> graf;

int dijkstra(const graf& G, int s, int d, vector<int>& cami) {
	vector<int> D(G.size(), INF);
	vector<bool> finished(G.size(), false);
	priority_queue<PI, vector<PI>, greater<PI>> Q;
	D[s] = 0;
	cami[s] = s;
	Q.push(make_pair(0,s));
	
	while (not Q.empty()) {
		int v = Q.top().second;
		Q.pop();
		if (not finished[v]) {
			finished[v] = true;
			for (auto w : G[v]) {
				int dist = D[v] + w.second;
				if (dist < D[w.first]) {
					D[w.first] = dist;
					Q.push(make_pair(D[w.first], w.first));
					cami[w.first] = v; 
				}
			}
		}
	}
	return D[d];
}

//La funció recursiva facilita el mostrar el camí en l'ordre que toca.
void print_path(const vector<int>& cami, int s, int u) {
	if (u == s) cout << s;
	else {
		print_path(cami, s, cami[u]);
		cout << ' ' << u;
	}
}

int main() {
	int n;
	while (cin >> n) {
		int m; cin >> m;
		graf G(n, VPI(0));
		for (int i = 0; i < m; ++i) {
			int u, v, c;
			cin >> u >> v >> c;
			G[u].push_back(make_pair(v,c));
		}
		int x, y; cin >> x >> y;
		vector<int> cami(G.size(),-1);
		int min_cost = dijkstra(G, x, y, cami);
		if (min_cost != INF) {
			print_path(cami, x, y);	
			cout << endl;
		}
		else cout << "no path from " << x << " to " << y << endl;
	}
}
