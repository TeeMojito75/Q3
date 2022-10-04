#include <iostream>
#include <set>
using namespace std;

int main() {
	string word;
	set<string> s;
	auto set_it = s.end();

	while (cin >> word and word != "END") {
		auto it = s.insert(word).first;
		if (set_it == s.end()) set_it = it;
		else {
			int n = s.size();
			if (n%2 != 0 and *set_it < word) ++set_it;
			else if (n%2 == 0 and *set_it > word) --set_it;
		}
		cout << *set_it << endl;
	}
}
