#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int x, k; cin >> x >> k;

		int pfactors = 0;
		while (x > 1) {
			bool found = false;
			for (int i = 2; i < sqrt(x+1); i++) {
				if (x%i == 0) {
					pfactors++;
					x = x/i;
					found = true;
					break;
				}
			}
			if (!found) {
				pfactors++;
				break;
			}
		}
		if (pfactors >= k) cout << "1\n";
		else cout << "0\n";
	}
}