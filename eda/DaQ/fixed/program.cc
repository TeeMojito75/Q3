#include <iostream>
#include <vector>
using namespace std;

int fixed_point(int a, const vector<int>& v, int i, int j) {
	if (i > j) return -1;
	int mid = (i + j)/2;
	if (v[mid] + a < mid+1) return fixed_point(a, v, mid+1, j);
	if (v[mid] + a > mid+1) return fixed_point(a, v, i, mid-1);
	int aux = fixed_point(a, v, i, mid-1);
	if (aux != -1) return aux;
	return mid+1;
}

int main() {
	int num_seq = 1, n1;
	while (cin >> n1) {
		vector<int> v(n1);
		for (int i = 0; i < n1; ++i) cin >> v[i];
		int n2;
		cin >> n2;
		cout << "Sequence #" << num_seq << endl;
		for (int i = 0; i < n2; ++i) {
			int a; cin >> a;
			int point = fixed_point(a, v, 0, v.size()-1);
			if (point == -1) cout << "no fixed point for " << a << endl;
			else cout << "fixed point for " << a << ": " << point << endl;
		}
		cout << endl;
		++num_seq;
	}
}

