#include <iostream>
#include <map>
using namespace std;

typedef map<string,int> LL;

int main() {
	LL llista;
	string nom, accio;
	while (cin >> nom >> accio) {
		if (accio == "enters"){
			auto it = llista.find(nom);
			if (it != llista.end()) cout << nom << " is already in the casino" << endl;
			else llista.insert( make_pair(nom, 0) );
		}
		else if (accio == "wins") {
			auto it = llista.find(nom);
			int valor;                                                                                       
      cin >> valor; 
			if (it == llista.end()) cout << nom << " is not in the casino" << endl;  
			else it->second += valor; 
			
		}
		else {
			auto it = llista.find(nom);    
			if (it == llista.end()) cout << nom << " is not in the casino" << endl;
			else {
				cout << nom << " has won " << it->second << endl;
				llista.erase(it);
			}
		}

	}
	cout << "----------" << endl;
	if (not llista.empty()) {
		for (auto it = llista.begin(); it != llista.end(); ++it) {
			cout << it->first << " is winning " << it->second << endl;
		}
	}

}
