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

bool tresor_trobat(const GridGraph& c, Visited& vis,int n, int m) {
    if (vis[n][m]) return false;      //empieza en visitad, bruh
    if (c[n][m] == 't') return true;  //tesoro encontrado
    if (c[n][m] == 'X') return false; //empieza en X

    vis[n][m] = true;

    if (tresor_trobat(c, vis, n+1, m) or tresor_trobat(c, vis, n-1, m) or tresor_trobat(c, vis ,n,m+1) or tresor_trobat(c,vis,n,m-1)) return true;

    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    GridGraph tablero = read_grid_graph(n, m);
    Visited vis(n+2, vector<bool>(m+2, false));

    //introduim posició inici
    cin >> n >> m;
    //funcion busqueda
    if (tresor_trobat(tablero, vis, n, m)) cout << "yes" << endl;
    else cout << "no" << endl;
}
