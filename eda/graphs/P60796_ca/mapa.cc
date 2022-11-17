#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;
typedef pair< pair<int,int>, int> pos;

bool BFS_dmin(VVC& mapa, int& d_min, int i, int j) {
	queue<pos> Q;
	d_min = 0;
	if (mapa[i][j] != 'X') Q.push(make_pair(make_pair(i, j), 0));
	while (not Q.empty()) {
		pos aux = Q.front();
		Q.pop();
		i = aux.first.first; j = aux.first.second; d_min = aux.second;

		if (mapa[i][j] == 't') return true;
		mapa[i][j] = 'X';
		
		char valors[4] = {mapa[i][j-1], mapa[i-1][j], mapa[i][j+1], mapa[i+1][j]};
		if (valors[0] != 'X') Q.push(make_pair(make_pair(i, j-1), d_min+1));
		if (valors[1] != 'X') Q.push(make_pair(make_pair(i-1, j), d_min+1));
		if (valors[2] != 'X') Q.push(make_pair(make_pair(i, j+1), d_min+1));
		if (valors[3] != 'X') Q.push(make_pair(make_pair(i+1, j), d_min+1));
	}
	return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	VVC mapa(n+2, VC(m+2, 'X'));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) cin >> mapa[i][j];
	}
	int d_min, i, j;
	cin >> i >> j;
	if (BFS_dmin(mapa, d_min, i, j)) cout << "distancia minima: " << d_min << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
}
