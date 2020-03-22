#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;

		int ms = 0;
		int w[n];

		for (int i = 0; i < n; i++) {
			cin >> w[i];
			if (w[i] > ms) ms = w[i];
		}

		vector <int> ind;

		for (int i = 0; i < n; i++) {
			if (ms == w[i]) ind.push_back(i);
		}

		sort(ind.begin(), ind.end());

		int diff = ind[ind.size()-1] - ind[0];

		cout << max(n/2 - diff, 0) << endl;

	}
}