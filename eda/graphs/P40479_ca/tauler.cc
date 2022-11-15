#include <iostream>
#include <vector>
using namespace std;

using VB = vector <bool>;
using VC = vector <char>;
using VVB = vector <VB>;
using VVC = vector <VC>;

int n,m;
VVB visit;
VVC G;


void write() {
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << G[i][j];
        cout << endl;
    }
    cout << endl;
}

void DFS(int x, int y, char c) {

    if (x >= 0 and x < n and y >= 0 and y < m) {
        if (G[x][y] == '#')
            return;
        if (not visit[x][y]) {
            visit[x][y] = true;
            G[x][y] = c;
            DFS(x+1,y,c);
            DFS(x-1,y,c);
            DFS(x,y+1,c);
            DFS(x,y-1,c);
        }

    }
}

void solu() {
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) {
            if (G[i][j] == '#')
                visit[i][j] = true;
            else if ((G[i][j] != '.') and not visit[i][j]){
                DFS(i,j,G[i][j]);
            }

        }
    }
}


int main() {
    while (cin >> n >> m) {
        G = VVC(n,VC(m));
        visit = VVB(n,VB(m,false));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> G[i][j];

        pinta_tauler(tauler,);
        write();
    }
}


