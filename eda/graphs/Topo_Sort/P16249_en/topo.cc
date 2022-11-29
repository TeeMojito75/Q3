#include <vector>
#include <queue>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef vector<string> VS;


void topographical_sort(VS& solution, map<string, VS>& succ, map<string, int>& pred) {
	priority_queue<string, vector<string>, greater<string>> Q;
	map<string, int>::const_iterator it = pred.begin();
	while (it != pred.end()) {
		if (it->second == 0) Q.push(it->first);
		++it;
	}
	while (not Q.empty()) {
		string p = Q.top();
		solution.push_back(p);
		Q.pop();
		for (int j = 0; j < succ[p].size(); ++j) {
			--pred[succ[p][j]];
			if (pred[succ[p][j]] == 0) Q.push(succ[p][j]);
		}
	}
}

int main() {
	int n;
	while (cin >> n) {
		map<string, VS> succ;
		map<string, int> pred;

		for (int i = 0; i < n; ++i) {
			string p; cin >> p;
			succ.insert(make_pair(p,VS(0)));
			pred.insert(make_pair(p, 0));
		}
		int m; cin >> m;
		for (int i = 0; i < m; ++i) {
			string x, y; cin >> x >> y;
			++pred[y];
			succ[x].push_back(y);
		}
		VS solution;
		topographical_sort(solution, succ, pred);
		if (solution.size() != n) cout << "NO VALID ORDERING" << endl;
		else {
			for (int i = 0; i < solution.size(); ++i) cout << solution[i];
			cout << endl;
		}
	}
}
