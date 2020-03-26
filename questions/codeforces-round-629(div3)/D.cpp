#include <bits/stdc++.h>
using namespace std;

int main() {
	int q; cin >> q;

	while (q--) {
		int n; cin >> n;

		int t[n];
		int c[n];
		c[0] = 1;
		int a;

		bool consFound = false;
		bool allEqual = true;

		for (int i = 0; i < n; i++) {
			cin >> t[i];

			if (i > 0) {
				if (t[i] != t[i-1]) allEqual = false;
				else if (!consFound) {
					a = i-1;
					consFound = true;
				}
			}
		}

		if (!consFound && t[0] == t[n-1]) {
			consFound = true; a = n-1;
		}

		if (allEqual) {
			cout << 1 << endl;
			for (int i = 0; i < n; i++) cout << 1 << ' ';
			cout << endl;
		}
		else if (n % 2 == 0) {
			cout << 2 << endl;
			for (int i = 0; i < n; i++) cout << (i%2 + 1) << ' ';
			cout << endl;
		}
		else {
			if (consFound) {
				cout << 2 << endl;
				for (int i = 0; i < n; i++) {
					if (i <= a) cout << (i%2 + 1) << ' ';
					else cout << (2 - i%2) << ' ';
				}
				cout << endl;
			}
			else {
				cout << 3 << endl;
				for (int i = 0; i < n-1; i++) {
					cout << (i%2 + 1) << ' ';
				}
				cout << 3 << endl;
			}
		}

	}
}