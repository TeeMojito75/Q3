#include <vector>
#include <string>
#include <iostream>
using namespace std;

void escriu_permutacions(int idx, int n, vector<string>& paraules, string& sol, vector<vector<bool>>& usat) {
	if (idx == 2*n) cout << sol << endl;
	else {
		int k2 = idx%2;
		for (int i = 0; i < n; ++i) {
			if (not usat[k2][i]) {
				sol[idx] = paraules[k2][i];
				usat[k2][i] = true;
				escriu_permutacions(idx+1, n, paraules, sol, usat);
				usat[k2][i] = false;
			}
		}
	}
}

int main() {
	int n; cin >> n;
	vector<string> paraules(2);
	cin >> paraules[0] >> paraules[1];
	string sol(2*n, ' ');
	vector<vector<bool>> usat(2, vector<bool>(n, false));
	escriu_permutacions(0, n, paraules, sol, usat);
}
