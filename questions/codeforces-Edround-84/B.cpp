#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;

		vector <int> choices[n+1];

		for (int i = 0; i < n; i++) {
			int k; cin >> k;
			for (int j = 0; j < k; j++) {
				int x; cin >> x;
				choices[i+1].push_back(x);
			}
		}
		bool kingdom_occupied[n+1];
		for (int i = 1; i <=n; i++) kingdom_occupied[i] = false;
		int dt[n+1];
		for (int i = 1; i <= n; i++) dt[i] = 0;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < choices[i].size(); j++) {
				if (!kingdom_occupied[choices[i][j]]) {
					dt[i] = choices[i][j];
					kingdom_occupied[choices[i][j]] = true;
					break;
				}
			}
		}

		int x = -1, y = -1;
		bool notFound = true;

		for (int i = n; i >= 1 && notFound; i--) {
			if (!kingdom_occupied[i]) {
				for (int j = n; j >= 1; j--) {
					if (dt[j] == 0) {
						x = j; y = i;
						notFound = false;
						break;
					}
				}
			}
		}
		if (x == -1) cout << "OPTIMAL" << endl;
		else cout << "IMPROVE\n" << x << ' ' << y << endl;
	}
}