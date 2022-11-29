#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef pair<int,int> coord;

int BFS_dmax(const VVC& mapa, int i, int j) {
	queue<coord> Q;
	vector<vector<int>> dist(mapa.size(), vector<int>(mapa[0].size(), -1));
	
	int res = -1;
	if (mapa[i][j] != 'X') Q.push(make_pair(i,j));
	dist[i][j] = 0;

	while (not Q.empty()) {
		coord aux = Q.front();
		i = aux.first; j = aux.second;
		Q.pop();
		if (mapa[i][j] == 't') res = dist[i][j];
		if (dist[i][j-1] == -1 and mapa[i][j-1] != 'X')  {
			Q.push(make_pair(i,j-1)); dist[i][j-1] = dist[i][j] + 1;
		}
		if (dist[i-1][j] == -1 and mapa[i-1][j] != 'X') {
			Q.push(make_pair(i-1,j)); dist[i-1][j] = dist[i][j] + 1;
		}
		if (dist[i][j+1] == -1	and mapa[i][j+1] != 'X') {
			Q.push(make_pair(i,j+1)); dist[i][j+1] = dist[i][j] + 1;
		}
		if (dist[i+1][j] == -1 and mapa[i+1][j] != 'X') {
			Q.push(make_pair(i+1,j)); dist[i+1][j] = dist[i][j] + 1;
		}
	}
	return res;
}

int main() {
	int n, m;
	cin >> n >> m;
	VVC mapa(n+2, VC(m+2, 'X'));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> mapa[i][j];
	}
	int i, j;
	cin >> i >> j;
	int d_max = BFS_dmax(mapa, i, j);
	if (d_max != -1 ) cout << "distancia maxima: " << d_max << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
}
