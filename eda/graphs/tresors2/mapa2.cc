#include <iostream>
#include <vector>
using namespace std;

typedef vector <vector<char>> GridGraph;
typedef vector <vector<bool>> Visited;

GridGraph read_grid_graph(int n, int m) {
    //n = nr. of rows, m = nr. of columns
    GridGraph c(n+2, vector<char>(m+2, 'X'));

    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < m+1; ++j) {
            cin >> c[i][j];
        }
    }
    return c;
}

void tresor_trobat(const GridGraph& c, Visited& vis,int n, int m, int& tresor) {
    if (vis[n][m] or c[n][m] == 'X') return ;      //empieza en visitad o pared, bruh
    if (c[n][m] == 't') ++tresor;  //tesoro encontrado

    vis[n][m] = true;

    tresor_trobat(c, vis, n+1, m, tresor);
    tresor_trobat(c, vis, n-1, m, tresor);
    tresor_trobat(c, vis ,n, m+1, tresor);
    tresor_trobat(c,vis,n,m-1, tresor);
}

int main() {
    int n, m;
    cin >> n >> m;

    GridGraph tablero = read_grid_graph(n, m);
    Visited vis(n+2, vector<bool>(m+2, false));

    //introduim posició inici
    cin >> n >> m;
    //funcion busqueda
    int tres = 0;
    tresor_trobat(tablero, vis, n, m, tres);
    cout << tres << endl;
}
