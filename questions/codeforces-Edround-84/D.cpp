#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int p[n+1], c[n+1];
		bool taken[n+1];
		for (int i = 1; i <= n; i++) {
			cin >> p[i];
			taken[i] = false;
		}
		for (int i = 1; i <= n; i++) cin >> c[i];

		vector<vector<int> > cycles;

		for (int i = 1; i <= n; i++) {
			if (!taken[p[i]]) {
				cycles.push_back(vector<int>());
				int last = cycles.size()-1;
				cycles[last].push_back(c[p[i]]);
				taken[p[i]] = true;
				int j = p[p[i]];

				while (j != p[i]) {
					cycles[last].push_back(c[j]);
					taken[j] = true;
					j = p[j];
				}
			}
		}
		int k = 0;
		bool found = false;
		while (!found) {
			k++;
			for (int i = 0; i < cycles.size(); i++) {
				int sz = cycles[i].size();
				if (sz % k == 0) {	
					bool sameColor = false;
					int j = 0;
					while (!sameColor && j < k) {
						sameColor = true;
						for (int l = k; l < sz; l+=k) {
							if (cycles[i][(j+l)%sz] != cycles[i][(j+l-k)%sz]) {
								sameColor = false;
								break;
							}
						}
						j++;
					}
					if (sameColor) {found = true; break;}
				}
			}
		}
		cout << k << endl;
	}
}