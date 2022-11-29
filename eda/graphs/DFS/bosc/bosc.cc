#include <vector>
#include <iostream>
using namespace std;

typedef int vertex;
typedef vector<vertex> llista_adj;
typedef vector<llista_adj> graf;

/* Retorna false si hi ha un cicle a G, true altrament*/
bool dfs(const graf& bosc, vertex pare, vertex v, vector<bool>& visitat) {
	visitat[v] = true;
	for (auto w : bosc[v]) {
		bool aux = visitat[w];
		if (not aux and not dfs(bosc, v, w, visitat)) return false;
		if (aux and w != pare) return false;
	}
	return true; 
}

bool es_bosc(const graf& bosc, int& arbres) {
	int n = bosc.size();
	vector<bool> visitat(n, false);
	for (int v = 0; v < n; ++v) {
		if (not visitat[v]) {
			++arbres;
			if (not dfs(bosc, v, v, visitat)) return false;
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
		int total = 0;
		if (es_bosc(bosc, total)) cout << total << endl;
		else cout << "no" << endl;
	}
}
