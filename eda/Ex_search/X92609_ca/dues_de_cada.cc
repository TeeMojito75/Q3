#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void backtrack(int i, int valor, int x, int& sols, const vector<int>& monedes, vector<bool>& n1, vector<bool>& n2) {
	if (valor == x) sols++;
	else if (valor <= x and i < monedes.size() and monedes[i]+valor <= x) {
		if (not n1[i]) {
			n1[i] = true;
			backtrack(i, valor+monedes[i], x, sols, monedes, n1, n2);
			n1[i] = false;
		}

		else if (not n2[i]) {
			n2[i] = true;
			backtrack (i+1, valor+monedes[i], x, sols, monedes, n1, n2);
			n2[i] = false;
		}

		backtrack(i+1, valor, x, sols, monedes, n1, n2);
	}
}

int main() {
	int x, n;
	while (cin >> x >> n) {
		vector<int> monedes(n);
		for (int i = 0; i < n; i++) cin >> monedes[i];
		sort(monedes.begin(), monedes.end());
		vector<int> solucio(2*n);
		vector<bool> n1(n, false); vector<bool> n2(n, false);
		int sols = 0;
		backtrack(0, 0, x, sols, monedes, n1, n2);
		cout << sols << endl; 
	}
}
