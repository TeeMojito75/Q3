#include <iostream>
#include <vector>
using namespace std;

void escriu(vector<int> A) {
	int n = A.size();
	for (int i = 0; i < n; ++i) {
		if (i < n-1) cout << A[i] << ' ';
		else cout << A[i];
	}
	cout << endl;
}

//A: cadena parcial (mida n)
//idx: primera casella no omplerta de A
//u: nombre d'1s que hi ha en A[0...idx-1] (ja portem posats)
//z: nombre d'0s que hi ha en A[0...idx-1] (ja portem posats)
//k: nombre total d'1s que volem
void cadenes3 (vector<int>& A, int idx, int z, int u, int k) {
	if (idx == A.size()) escriu(A);
	else {
		if (z < A.size() - k) { //No tots els 0s posats
			A[idx] = 0; cadenes3(A, idx+1, z+1, u, k);
		}

		if (u < k) {
			A[idx] = 1; cadenes3(A, idx+1, z, u+1, k);
		}
	}
}

int main() {
	int n, k; cin >> n >> k;
	vector<int> A(n);
	cadenes3(A, 0, 0, 0, k);
}
