#include <iostream>
#include <vector>
using namespace std;

void escriu(vector<int> A) {
	cout << '(';
	for (int i = 0; i < A.size(); ++i) {
		if (i < A.size() - 1) cout << A[i] << ',';
		else cout << A[i];
	}
	cout << ')' << endl;
}

void escriu_permutacions2(int n, vector<int>& A, int idx, vector<bool>& usat) {
	if (idx == A.size()) escriu(A);
	else {
		for (int k = 1; k <= n; ++k) {
			if (not usat[k]) {
				A[idx] = k;
				usat[k] = true;
				escriu_permutacions2(n,A,idx+1,usat);
				usat[k] = false; // restaurem sota backtrack
			}
		}
	}
}

int main() {
	int n; cin >> n;
	vector<int> A(n);
	vector<bool> usat(n+1, false);
	escriu_permutacions2(n, A, 0, usat);
}
