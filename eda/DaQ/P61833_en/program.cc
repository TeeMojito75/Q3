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


void power_mat(Mat mat, Mat& mat2, int n, int m) {
	Mat aux(2, vector<int>(2));
	if (n == 0) {
		mat2[0][0] = 1;
		mat2[0][1] = 0;
		mat2[1][0] = 0;
		mat2[1][1] = 1;  
	}
	else if (n == 1) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				mat2[i][j] = mat[i][j]%m;
			}
		}
	}
	else if (n%2 == 0) {
		power_mat(mat, aux, n/2, m);
		mat2 = mult(aux, aux, m);
	}
	else {
		power_mat(mat, aux, n/2, m);
		aux = mult(aux, aux, m);
		mat2 = mult(aux, mat, m);
	}

}

int main() {
	Mat mat(2, vector<int>(2));
	int n, m;

	while(cin >> mat[0][0] >> mat[0][1] >> mat[1][0] >> mat[1][1] >> n >> m) {
	 Mat mat2(2, vector<int>(2));
	 power_mat(mat, mat2, n, m);
		cout << mat2[0][0] << ' ' << mat2[0][1] << endl;
		cout << mat2[1][0] << ' ' << mat2[1][1] << endl;
		cout << "----------" << endl;
	}
}
