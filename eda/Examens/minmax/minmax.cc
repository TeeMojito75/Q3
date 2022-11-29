#include <iostream>
#include <vector>
using namespace std;

typedef int vertex;
typedef vector<vertex> llista_adj;
typedef vector<llista_adj> graf;

vector<bool> visitat;

int dfs(int x, const graf& bosc) {
	if (visitat[x]) return 0;
	visitat[x] = true;
	int res = 1;
	for (int i = 0; i < (int)bosc[x].size(); ++i) {
		res += dfs(bosc[x][i], bosc);
	}
	return res;
}

int main() {
	int n, m;
		while(cin >> n >> m) {
		graf bosc(n, llista_adj(0));
		for (int i = 0; i < m; ++i) {
			vertex v1, v2;
			cin >> v1 >> v2;
			bosc[v1].push_back(v2);
			bosc[v2].push_back(v1);
		}
		int mn = 100000;
		int mx = 0;

		visitat = vector<bool> (n, false);

		for (int x = 0; x < n; ++x) {
			if (not visitat[x]) {
				int q = dfs(x, bosc);
				mn = min(mn, q);
				mx = max(mx, q);
			}
		}
		cout << mn << ' ' << mx << endl;
	}
}
