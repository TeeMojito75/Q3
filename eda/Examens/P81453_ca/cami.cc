#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector<VI> VVI;

void path(int xi, int xf, const VI& p) {
    if (xi == xf) cout << xi;
    else {
        path(xi, p[xf], p);
        cout << " " << xf;
    }
}

void bfs(const VVI& g, int xi, int xf) {
    int n = g.size();
    VI p(n, -1);
    VB mkd(n, false);
    VI cur, pos;

    cur.push_back(xi);
    while (not cur.empty()) {
        for(int x : cur) {
            if (x == xf) {
                path(xi, xf, p);
                cout << endl;
                return;
            }
            for (int y : g[x]) 
                if (not mkd[y]) {
                    pos.push_back(y);
                    mkd[y] = true;
                    p[y] = x;
                }
        }
        swap(pos, cur);
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        VVI g(n);
        for (int k = 0; k < m; ++k) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
        }
        for (int x = 0; x < n; ++x) sort (g[x].begin(), g[x].end());

        bfs(g, 0, n-1);
    }
}
