#include <iostream>
#include <set>
#include <string>
#include <sstream>
using namespace std;

int max_long(const set<int>& nums) {
	if (nums.empty()) return 0;
	if (nums.size() == 1) return 1;
	int total = 1;
	auto it1 = nums.begin();
	auto it2 = it1;
	++it2;
	while (it2 != nums.end()) {
		if ((*it1 + *it2)%2 != 0) ++ total;
		++it1;
		++it2;
	}
	return total;
}


int main() {
	string s;
	while (getline(cin, s)) {
		istringstream ss(s);
		set<int> nums;
		int x;
		while (ss >> x) nums.insert(x);
		cout << max_long(nums) << endl;
	}
}
