#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<char> > Matriu;

void escriu_tauler (Matriu& tauler) {
	for (int i=0; i < tauler.size(); ++i) {
		for (int j=0; j < tauler[0].size(); ++j) {
			cout << tauler[i][j];
		}
		cout << endl;
	}
	cout << "----------" << endl;
}

bool comprovar_posicions_disponibles (int i, int j, Matriu& tauler) {
	if (tauler[i][j] == 'K') return false;
	else if (i-1 >= 0 and tauler[i-1][j] == 'K') return false;
	else if (i+1 < tauler.size() and tauler[i+1][j] == 'K') return false;
	else if (j-1 >= 0 and tauler[i][j-1] == 'K') return false;
	else if (j+1 < tauler.size() and tauler[i][j+1] == 'K') return false;
	else if (i-1 >= 0 and j-1 >= 0 and tauler[i-1][j-1] == 'K') return false;
	else if (i+1 < tauler.size() and j-1 >= 0 and tauler[i+1][j-1] == 'K') return false;
	else if (i+1 < tauler.size() and j-1 >= 0 and tauler[i+1][j-1] == 'K') return false;
	else if (i-1 >= 0 and j+1 < tauler.size() and tauler[i-1][j+1] == 'K') return false;
	else return true;
}

void reis_pacifics (int k, int x, int y, int n, int r, Matriu& tauler) {
	if (k == r) escriu_tauler(tauler);
	else {
		bool primer = true;
		for (int i=x; i < n; ++i) {
			for (int j=0; j < n; ++j) {
				if (primer) {
					primer = false;
					j=y;
				}
				if (comprovar_posicions_disponibles(i, j, tauler)) {
					tauler[i][j] = 'K';
					reis_pacifics(k+1, i, j, n, r, tauler);
					tauler[i][j] = '.';
				}
			}
		}
	}
}

int main() {
	int n, r;
	cin >> n >> r;
	Matriu tauler (n, vector<char> (n, '.'));
	reis_pacifics(0, 0, 0, n, r, tauler);
}


