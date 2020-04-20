#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		int x, n, m;
		cin >> x >> n >> m;

		while (x > 0) {
			if (x > 20) {
				if (n > 0) {
					x = x/2 + 10;
					n--;
				}
				else if (m > 0) {
					x -= 10;
					m--;
				}
				else break;
			}
			else {
				if (m > 0) {
					x -= 10;
					m--;
				}
				else break;
			}
		}
		if (x > 0) cout << "NO\n";
		else cout << "YES\n";
	}
}