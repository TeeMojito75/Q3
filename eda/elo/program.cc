#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<string, int> player;

bool cmp(player p1, player p2) {
	if (p1.second != p2.second) return p1.second > p2.second;
	return p1.first < p2.first;
}

int main() {
	unordered_map<string, pair<int, bool>> server;
	string s;
	while (cin >> s) {
		if (s == "LOGIN") {
			cin >> s;
			auto p = server.insert(make_pair(s, make_pair(1200, true)));
			if (p.second == false) p.first->second.second = true;
		}
		else if (s == "LOGOUT") {
			cin >> s;
			auto it = server.find(s);
			if (it != server.end()) it->second.second = false;
		}
		else if (s == "PLAY") {
			string j1, j2;
			cin >> j1 >> j2;
			auto it1 = server.find(j1);
			auto it2 = server.find(j2);
			if (it1 == server.end() or it2 == server.end() or it1->second.second == false or it2->second.second == false) {
				cout << "jugador(s) no connectat(s)" << endl;
			}
			else {
				it1->second.first += 10;
				it2->second.first -= 10;
				if (it2->second.first < 1200) it2->second.first = 1200;
			}
		}
		else {
			cin >> s;
			auto it = server.find(s);
			cout << it->first << ' ' << it->second.first << endl;
		}
	}
	cout << endl << "RANKING" << endl;
	vector<player> ranking(server.size());
	auto it = server.begin();
	for (int i = 0; i < ranking.size(); ++i) {
		ranking[i].first = it->first;
		ranking[i].second = it->second.first;
		++it;
	}
	sort(ranking.begin(), ranking.end(), cmp);

	for (int i = 0; i < ranking.size(); ++i) cout << ranking[i].first << ' ' << ranking[i].second << endl;

}
