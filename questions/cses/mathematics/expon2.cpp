#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

const ll mod = 1e9+7;

int main () {
	int t; cin >> t;

	while (t--) {
		ll a, b, c;
		cin >> a >> b >> c;

		ll res1 = 1;
		while (c > 0) {
			if (c&1)
				res1 = (res1*b)%(mod-1);
			b = (b*b)%(mod-1);
			c >>= 1;
		}
		ll res = 1;
		while (res1 > 0) {
			if (res1&1)
				res = (res*a)%mod;
			a = (a*a)%mod;
			res1 >>= 1;
		}
		cout << res << endl;
	}
}