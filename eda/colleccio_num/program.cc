#include <iostream>
#include <queue>
using namespace std;

int main() {
	char p;
	priority_queue<int> coa;
	while (cin >> p) {
	    if (p =='S') {
				int afegir;
				cin >> afegir;
				coa.push(afegir);
			}
	    
			if (p =='A') {
				if (coa.empty()) cout << "error!" << endl;
				else cout << coa.top() << endl;
			} 

	    if (p =='R') {	
				if (coa.empty()) cout << "error!" << endl;
				else coa.pop();
			}

	    if (p =='I') {
				if (coa.empty()) cout << "error!" << endl;
				else {
					int afegir;
				  cin >> afegir;	
				  int val = coa.top();
					coa.pop();
					val += afegir;
					coa.push(val);
				}
			}

	    if (p =='D') {	
				if (coa.empty()) cout << "error!" << endl;
			  else {	
					int afegir;
					cin >> afegir;	
					int aux = coa.top();
					aux = aux - afegir;
			  	coa.pop();
					coa.push(aux); 
				}
		}
	}
}
