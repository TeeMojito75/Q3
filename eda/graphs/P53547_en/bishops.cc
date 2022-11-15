#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> row;
typedef vector<row>	board;
typedef vector<pair<int,int>> where_to_start;

void is_possible_DFS(board& B, int i, int j, int& n, int& sum) {
	if (B[i][j] != -1) {
		sum += B[i][j]; ++n;
		B[i][j] = -1;
		is_possible_DFS(B, i-1, j-1, n, sum);
		is_possible_DFS(B, i-1, j+1, n, sum);
		is_possible_DFS(B, i+1, j-1, n, sum);
		is_possible_DFS(B, i+1, j+1, n, sum);
	}
}

bool is_possible(board& B, const where_to_start& V) {
	int legal_cells = V.size();
	int suma_prev = -1;
	for (auto v : V) {
		if (not legal_cells) return true;
		if (B[v.first][v.second] != -1) {
			int num = 0, sum = 0;
			is_possible_DFS(B, v.first, v.second, num, sum);
			legal_cells -= num;
			if (sum%num != 0) return false;
			if (suma_prev == -1) suma_prev = sum/num;
			if (sum/num != suma_prev) return false;
		}
	}
	return true;
}

int main() {
	int t;
	cin >> t;
	for (int k = 0; k < t; ++k) {
		int n, m;
		cin >> n >> m;
		board B(n+2, row(m+2, -1));
		where_to_start v(0);

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				string p; cin >> p;
				B[i][j] = (p == "X" ? -1 : stoi(p));
				if (B[i][j] != -1) v.push_back(make_pair(i,j)); 
			}
		}
		cout << "Case " << k+1 << ": "<< (is_possible(B, v) ? "yes" : "no") << endl;
	}
}
