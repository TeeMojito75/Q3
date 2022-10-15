#include <iostream>
#include <vector>
using namespace std;


bool bsearch(double x, const vector<double>& v, int e, int d) {
	if (e > d) return false;
	int m = (e + d)/2;
	if (v[m] == x) return true;

	if ((m > 0 and v[m-1] == x) or (m < v.size()-1 and v[m+1] == x)) return true;

	if (v[m] > x) return bsearch(x, v, e, m-1);
	return bsearch(x, v, m+1, d);
}

bool resistant_search(double x, const vector<double>& v) {
	if (v.empty()) return false;
	return bsearch(x, v, 0, v.size()-1);
}

int main() {
    
    int x;
    
    cin >> x;
    
    vector<double> v(8);
    
    for (int i=0; i < 8; i++) cin >> v[i];
    
    cout << resistant_search(x, v);
}

