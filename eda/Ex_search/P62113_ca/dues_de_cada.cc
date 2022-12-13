#include <vector>
#include <iostream>
using namespace std;

int x; //valor que cercam
int n; //n monedes


int main() {
	while (cin >> x >> n) {
		vector<int> monedes(2*n); //així guardam la moneda i la contrapart 
		for (int i = 0; i < n; ++i){cin >> monedes[i]; 
		vector<bool> usats(n);
		bactrack(monedes);
		
	}
}
