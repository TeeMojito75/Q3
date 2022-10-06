#include <iostream>
#include <queue>
using namespace std;

string order;

struct cmp {
    bool operator()(string& a, string& b) {
    	string s = order.substr(0,a.size());
	if (a.size() != b.size()) return a.size() > b.size();
	if (a == b) return true;
	if (a == s) return false;
	if (b == s) return true;

	if (a < b) {
	    if (a < s and s < b) return true;
	    return false;
	}
	else {
	    if (a > s and s > b) return false;
	    return true;
	}
	return true;
    }
};


int main() {
    while (cin >> order) {
    	int tickets = 0;
	string event, supp;
	priority_queue<string, vector<string>, cmp> records;

	while (cin >> event and event != "E") {
	    if (event == "T") ++tickets;
	    else if (event == "S") {
	    	cin >> supp;
		if (tickets != 0) {
		    --tickets;
		    cout << supp << endl;
		}
		else {
		    records.push(supp);
		}
	    }
	    while (tickets != 0 and not records.empty()) {
	    	cout << records.top() << endl;
		records.pop();
		--tickets;
	    }
	}
	cout << tickets << " ticket(s) left" << endl;
	cout << records.size() << " supporter(s) with no ticket" << endl;
	cout << endl;
    }
}









