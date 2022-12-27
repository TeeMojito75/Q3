#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void escriu(vector<int>& solucio, int idx, int x) {
	cout << x << " = ";
	bool primer = true;
	for (int i = 0; i < idx; i++) {
		if (solucio[i] != 0) {
			if (primer) {
				primer = false;
				if (i%2 != 0) cout << solucio[i] << 'p';
				else cout << solucio[i];
			}
			else {
				if (i%2 != 0) cout << " + " << solucio[i] << 'p';
				else cout << " + " << solucio[i];
			}
		}
	}
	cout << endl;
}

void backtrack(int idx, int valor, int x, vector<int>& monedes, vector<int>& solucio) {
	int n = monedes.size();
	if (valor == x) escriu(solucio, idx, x);
	else if (idx < 2*n) {
		if (valor < x) {
			int aux = solucio[idx];
			solucio[idx] = monedes[idx/2];
			valor += monedes[idx/2];
			backtrack(idx+1, valor, x, monedes, solucio);
			valor -= monedes[idx/2];
			solucio[idx] = aux;
			backtrack(idx+1, valor, x, monedes, solucio);
		}
	}
}

int main() {
	int x, n;
	while (cin >> x >> n) {
		vector<int> monedes(n);
		for (int i = 0; i < n; i++) cin >> monedes[i];
		sort(monedes.begin(), monedes.end());
		vector<int> solucio(2*n);
		backtrack(0,0,x,monedes, solucio);
		cout << "----------" << endl;
	}
}
