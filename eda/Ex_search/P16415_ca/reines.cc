#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> t;
// mc[j] si ja hi ha reina a la columna j,
// md1[k] si ja hi ha reina a la diagonal i+j = k, etc.
vector<int> mc, md1, md2;

int diag1(int i, int j) { return i+j; }
int diag2(int i, int j) { return i-j + n-1; }

int reines(int i) {
	if (i == n) {
	return 1;
	}
	else {
		int res = 0;
		for (int j = 0; j < n; ++j)
			if (not mc[j] and
				not md1[diag1(i, j)] and
				not md2[diag2(i, j)]) {
				t[i] = j;
				mc[j] = md1[diag1(i, j)] = md2[diag2(i, j)] = true;
				res += reines(i+1);
				mc[j] = md1[diag1(i, j)] = md2[diag2(i, j)] = false;
			}
	return res;
	}
}

int main() {
	cin >> n;
	t = vector<int>(n);
	mc = vector<int>(n, false);
	md1 = md2 = vector<int>(2*n-1, false);
	int res = reines(0);
	cout << res << endl;
}
