#include <bits/stdc++.h>
using namespace std;
int M = 1000000007;

int main () {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;

		int b[n];

		for (int i = 0; i < n; i++) cin >> b[i];

		long long int ans = 1;
		bool brk = false;

		for (int i = 1; i < n && !brk; i++) {
			int x = b[i-1]; int y = b[i];
			int bts = 32;

			while (bts--) {
				if ((x&1) && (y&1)) ans = (ans*2)%M;
				else if (x&1) {
					ans = 0;
					brk = true;
					break;
				}
				x = x >> 1;
				y = y >> 1;
			}
		}

		cout << ans << endl;

	}

}