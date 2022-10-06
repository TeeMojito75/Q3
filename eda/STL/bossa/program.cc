#include <iostream>
#include <map>
using namespace std;

int main() {
	map<string, int> bag;
	auto it = bag.end();
	string op, word;
	while (cin >> op) {
		
		if (op == "store") {
			cin >> word;
			it = bag.find(word);
			if (it == bag.end()) bag.insert(make_pair(word, 1));
			else ++it->second;
		}
		
		else if (op == "delete") {
			cin >> word;
			it = bag.find(word);
			if (it != bag.end()) {
				if (it->second == 1) bag.erase(it);
				else --it->second;
			}
		}

		else if (op == "maximum?") {
			if (bag.size() == 0) cout << "indefinite maximum" << endl;
			else {
				it = bag.end(); 
				--it;
				cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
			}
		}

		else {
			if (bag.size() == 0) cout << "indefinite minimum" << endl;
			else {
				it = bag.begin();
				cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
			}
		}
	}
}
