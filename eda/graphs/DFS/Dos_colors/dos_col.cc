#include <vector>
#include <iostream>
using namespace std;

typedef int vertex;
typedef vector<vertex> llista_adj;
typedef vector<llista_adj> graf;

/* Retorna false si hi ha un cicle a G, true altrament*/
bool dfs(const graf& bosc, vector<vertex>& colors, vertex v, int color) {
	 if (colors[v] == -1) {
			colors[v] = color;
			for (auto w : bosc[v]) {
					if (not dfs(bosc, colors, w, 1-color)) return false;
			}
			return true;
	 }
	 else return colors[v] == color;
}

bool dos_col(const graf& bosc) {	
	vector<vertex> vec_colors(bosc.size(), -1);
	for (int u = 0; u < bosc.size(); u++) {
		if (vec_colors[u] == -1) {
			if (not dfs(bosc, vec_colors, u, 0)) return false;
		}
	}
	return true;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		graf bosc(n, llista_adj(0));
		for (int i = 0; i < m; ++i) {
			vertex v1, v2;
			cin >> v1 >> v2;
			bosc[v1].push_back(v2);
			bosc[v2].push_back(v1);
		}
		if (n == 1 || n == 2 || dos_col(bosc)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}
