#include <vector>
#include <string>
#include <iostream>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;

void read_sample(VVI& mat) {
	char s;
	for (int j = 0; j < 9; j++) {
		for (int k = 0; k < 9; k++) { 
			if ((cin >> s) == '.')  
		}
	}
}

void escriu(VVI& mat) {
	for (int j = 0;j < 9; j++) {    
		for (int k = 0; k < 9; k++)  {
			if (k < 8) cout << mat[j][k] << ' ';
			else cout << mat[j][k] << endl;
		}
	}
	cout << endl;
}







int main() {
	int n, i = 0; 
	cin >> n;
	cout << n << endl << endl;
	while (i < n) {
		VVS entrada(9, VS(9));
		read_sample(entrada);
		VVI mat(9, VI(9, 0));
		transform(entrada, mat);
		escriu(mat);
		i++;
	}
}

