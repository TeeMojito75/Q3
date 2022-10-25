#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Mat;

Mat mult(Mat &a, Mat &b, int m){
    Mat aux;
    aux = Mat (2,vector<int> (2));
    aux[0][0] = (a[0][0]*b[0][0]+a[0][1]*b[1][0])%m;
    aux[0][1] = (a[0][0]*b[0][1]+a[0][1]*b[1][1])%m;
    aux[1][0] = (a[1][0]*b[0][0]+a[1][1]*b[1][0])%m;
    aux[1][1] = (a[1][0]*b[0][1]+a[1][1]*b[1][1])%m;
    return aux;
}


void fibonacci(Mat mat, Mat& mat2, int n, int m, int &res) {
	Mat aux(2, vector<int>(2));
	if (n == 0) {
		res = 0;
	}
	else if (n == 1) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				mat2[i][j] = mat[i][j]%m;
			}
		}
	}
	else if (n%2 == 0) {
		fibonacci(mat, aux, n/2, m, res);
		mat2 = mult(aux, aux, m);
	}
	else {
		fibonacci(mat, aux, n/2, m, res);
		aux = mult(aux, aux, m);
		mat2 = mult(aux, mat, m);
	}
	res = mat2[0][1];

}

int main() {
	Mat mat(2, vector<int>(2));	
	mat[0][0] = 1;
	mat[0][1] = 1;
	mat[1][0] = 1;
	mat[1][1] = 0; 
	int n, m;

	while(cin >> n >> m) {
	 Mat mat2(2, vector<int>(2));
	 int res = 0; 
	 fibonacci(mat, mat2, n, m, res);
	 cout << res << endl;
	}
}
