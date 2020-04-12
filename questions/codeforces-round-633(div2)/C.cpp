#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		ll a[n];
		for (int i = 0; i < n; i++) cin >> a[i];
		
		ll maxdif = 0;
		ll m = a[0];

		for (int i = 1; i < n; i++) {
			if (a[i] >= m) {
				m = a[i];
			}
			else {
				if (maxdif < m - a[i]) maxdif = m - a[i];
			}
		}
		int k = 0;
		while (maxdif) {
			k++;
			maxdif >>= 1;
		}
		cout << k << endl;
	}
}