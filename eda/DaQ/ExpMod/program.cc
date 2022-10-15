#include <iostream>
using namespace std;

int potencia(int x, int n, int m) {
	if (n == 0) return 1;
	else {
		int  y = potencia(x, n/2, m);
		if (n%2 == 0) return (y*y)%m;
		else return (((y*y)%m)*x)%m;
	}
}

int main() {
	int x, n, m;
	while (cin >> x >> n >> m) {
	int pot = potencia(x,n,m);
	cout << pot << endl; 
	}
}
