#include <iostream>
#include <set>
using namespace std;

struct ShorterString {
    bool operator()(const string& a, const string& b) const {
        if (a.size() != b.size()) return a.size() < b.size();
     	return a < b;	
    }
};

int main() {
   int games = 1;
   string w;

   while (w != "QUIT") {
       set<string> has;
       set<string, ShorterString> had;
       while (cin >> w and w != "END" and w != "QUIT" ) {
           auto it1 = has.find(w);
           if (it1 == has.end()) {
               has.insert(w);
               auto it2 = had.find(w);
               if (it2 != had.end()) had.erase(it2);
           }  
           else {
               had.insert(w);
               has.erase(it1);
           }
       }
       if (games > 1) cout << endl;
       cout << "GAME #" << games << endl;
       cout << "HAS:" << endl;
       for (auto elem : has) cout << elem << endl;
       cout << endl << "HAD:" << endl;
       for (auto elem : had) cout << elem << endl;
          ++games;
   }
}
