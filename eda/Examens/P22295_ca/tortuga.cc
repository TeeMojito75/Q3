#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<char> VC;
typedef vector<VC> VVC;

const int N_DIRS = 4;
const int DR[N_DIRS] = { 0,-1, 0, 1};
const int DC[N_DIRS] = { 1, 0,-1, 0};

struct Punt {
    int f, c;
    Punt(int ff, int cc) : f(ff), c(cc) {}
};

bool ok(int r, int c, int n, int m) {
    return 0 <= r and r < n and 0 <= c and c < m;
}

void cerca(int rf, int cf, int n, int m, const VVC& t, vector<Punt>& v, VVB& seen) {
    Punt p = v.back();
    if (p.f == rf and p.c == cf) {
        for (int i = 0; i < v.size(); ++i) cout << t[v[i].f][v[i].c];
        cout << endl;
    }
    else {
        for (int k = 0; k < N_DIRS; ++k) {
            int ff = p.f + DR[k];
            int cc = p.c + DC[k];
            if (ok(ff, cc, n, m) and not seen[ff][cc]) {
                seen[ff][cc] = true;
                v.push_back(Punt(ff, cc));
                cerca(rf, cf, n, m, t, v, seen);
                v.pop_back();
                seen[ff][cc] = false;
            } 
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    VVC t (n, VC(m));
    VVB seen(n, VB(m, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> t[i][j];
    }
    int ri, ci, rf, cf;
    cin >> ri >> ci >> rf >> cf;
    seen[ri][ci] = true;
    vector<Punt> v(1, Punt(ri, ci));
    cerca(rf, cf, n, m, t, v, seen);
}
 