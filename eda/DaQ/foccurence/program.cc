#include <iostream>
#include <vector>
using namespace std;

int bsearch(const vector<double>& A, const double& x, int l, int u) {
if (l > u) return -1;
int m = (l + u)/2;
if (x < A[m])
return bsearch(A, x, l, m - 1);
if (x > A[m])
return bsearch(A, x, m + 1, u);

if (m - 1 >= 0) {
	int m1 = bsearch(A, x, l, m - 1);
	if (m1 != -1) return m1;
	}
return m;
}

int first_occurrence(double x, const vector<double>& v) {
 if (v.empty() or x < v[0] or v[v.size()-1] < x) return -1;
	return bsearch(v, x, 0, v.size()-1);
}


int main() {
	double x = 10;
	vector<double> a(10);
	for (int i = 0; i < 10; ++i) cin >> a[i];
	int r = first_occurrence(x, a);
	cout << r << endl;
}



