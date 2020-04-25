#include <bits/stdc++.h>
#define ll long long int
using namespace std;

const ll p = 998244353;

ll pwr(ll x, ll y) {
	ll res = 1;
	x = x%p;
	while (y > 0) {
		if (y&1) res = (res*x)%p;

		y = y>>1;
		x = (x*x)%p;
	}
	return res;
}

int main () {
	int t; cin >> t;

	while (t--) {
		int n;
		cin >> n;

		int a[n];

		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}

		sort(a, a+n);

		ll ans = 0;
		ll mlt = 1;

		int cur = 0;
		for (int i = 0; i < n; i++) {
			if (cur+1 < a[i]) {
				ans = (ans + (((cur+1) * ((mlt * pwr(2, n-i))%p))%p)) % p;
				break;
			}
			else {
				int j = i+1;
				bool found = false;
				for (; j < n; j++) {
					if (cur+1 < a[j]) {
						found = true;
						break;
					}
				}
				cur++;

				if (found) {
					ans = (ans + ((mlt * ((cur * pwr(2, n-j))%p))%p)) % p;
					mlt = (mlt * ((pwr(2, j-i) + p - 1)%p)) % p;
					i = j-1;
				}
				else {
					ans = (ans + ((mlt * cur)%p)) % p;
					mlt = (mlt * ((pwr(2, n-i) + p - 1)%p)) % p;
					ans = (ans + ((mlt * (cur+1))%p)) % p;
					break;
				}
			}
		}

		cout << ans << endl;
	}
}