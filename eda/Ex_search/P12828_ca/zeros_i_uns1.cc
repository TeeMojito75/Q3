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

// i es la seguent posicio del vector A que assignarem
void cerca_ex(vector<int>& A, int i) {
	if (i == A.size()) escriu(A); // cas base
	else { // cas inductiu
		A[i] = 0; cerca_ex(A,i+1);
		A[i] = 1; cerca_ex(A,i+1);
	}	
}

void binari(int n) {
	vector<int> A(n);
	cerca_ex(A,0);
}

int main() {
	int n;
	cin >> n;
	binari(n);
}
