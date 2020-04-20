#include <iostream>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		int dist = 0;
		bool personAhead = false;
		bool socialDist = true;
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			if (!personAhead && temp == 1) {personAhead = true; continue;}
			if (personAhead) {
				dist++;
				if (temp == 1) {
					if (dist < 6) socialDist = false;
					dist = 0;
				}
			}
		}
		if (socialDist) cout << "YES\n";
		else cout << "NO\n";
	}
}