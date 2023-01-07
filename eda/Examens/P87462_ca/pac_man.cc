#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> VC;
typedef vector<VC> VVC;

struct Pos {
    int i, j;
    Pos() {}
    Pos(int i2, int j2) : i(i2), j(j2) {}
};

const int FI[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int FJ[8] = {-1,  0,  1,-1, 1,-1, 0, 1};
const int DI[4] = {-1, 0, 0, 1};
const int DJ[4] = {0, -1, 1, 0};

bool dfs_menjar(VVC& tauler, Pos p) {
    int i = p.i, j = p.j;
    if (tauler[i][j] == 'X') return false;
    if (tauler[i][j] == 'B') return true;
    tauler[i][j] = 'X';
    return dfs_menjar(tauler, Pos(i+1, j)) or dfs_menjar(tauler, Pos(i-1, j)) or dfs_menjar(tauler, Pos(i, j+1)) or dfs_menjar(tauler, Pos(i, j-1));
}

int main() {
    int f, c;
    while (cin >> f >> c) {
        VVC tauler(f, VC(c));
        Pos p_inicial;
        vector<Pos> fantasmes;

        for (int i = 0; i < f; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> tauler[i][j];
                if (tauler[i][j] == 'P') p_inicial = Pos(i, j);
                else if (tauler[i][j] == 'F') fantasmes.push_back(Pos(i,j));
            }
        }

        //Posem a X aquelles caselles adjacents a F
        for (int i = 0; i < fantasmes.size(); ++i) {
            for (int k = 0; k < 8; ++k) 
                tauler[fantasmes[i].i + FI[k]][fantasmes[i].j + FJ[k]] = 'X';
        }
        if (dfs_menjar(tauler, p_inicial)) cout << "si" << endl;
        else cout << "no" << endl;
    }
}
