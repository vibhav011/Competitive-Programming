#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while(t--) {
		int n; cin >> n;
		int a[n], c[n];
		for (int i = 0; i < n; i++) cin >> a[i];
		fill(c, c+n, 0);

		int p[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
		int colored = 0, m = 0, curcolor = 1;
		for (int i = 0; i < 11; i++) {
			bool col = false;
			for (int j = 0; j < n; j++) {
				if (a[j] % p[i] == 0 && !c[j]) {
					c[j] = curcolor;
					colored++;
					col = true;
				}
			}
			if (col) {
				m++;
				curcolor++;
			}
			if (colored == n) break;
		}
		cout << m << endl;
		for (int i = 0; i < n; i++) cout << c[i] << ' ';
		cout << endl;
	}
	return 0;
}