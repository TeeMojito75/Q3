#include <vector>
#include <iostream>
#include <map>
using namespace std;

typedef vector<int> VE;
typedef vector<VE> VVE;

int k_esim(int k, const VVE& V) {
    map<int,int> conjunt;
    for (int i = 0; i < V.size(); ++i) {
    	if (not V[i].empty()) conjunt.insert(make_pair(V[i][0], i));
    }

    	pair<int,int> pos;
	VE it(V.size(), 1);

	while (k > 0) {
	    pos.first = conjunt.begin()->first;
	    pos.second = conjunt.begin()->second;
	    if (V[pos.second].size() > it[pos.second]) {
	    	int aux = V[pos.second][it[pos.second]++];
		conjunt[aux] = pos.second;
	    }
	    conjunt.erase(conjunt.begin());
	    --k;
	}
	return pos.first;
}
