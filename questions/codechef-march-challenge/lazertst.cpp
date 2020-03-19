#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n, m, k, q;
		cin >> n >> m >> k >> q;
		int q1 = q;

		int l[q], r[q];
		int ans[q];

		while (q1--) {
			cin >> l[q-q1-1] >> r[q-q1-1];
		}
		if (k == 3) {
			cout << 2 << ' ';
			for (int i = 0; i < q; i++) cout << m-1 << ' ';
			cout << endl;
			fflush(stdout);
		}
		else {
			for (int i = 0; i < q; i++) {
				cout << 1 << ' ' << l[i] << ' ' << r[i] << ' ' << m/2 << endl;
				fflush(stdout);
				cin >> ans[i];
			}
			cout << 2 << ' ';
			for (int i = 0; i < q; i++) cout << ans[i] << ' ';
			cout << endl;
			fflush(stdout);
		}

		int ver; cin >> ver;
		if (ver == -1) break;

	}
}