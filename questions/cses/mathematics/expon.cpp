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
		ll a, b;
		cin >> a >> b;

		ll res = 1;
		while (b > 0) {
			if (b&1)
				res = (res*a)%mod;
			a = (a*a)%mod;
			b >>= 1;
		}
		cout << res << endl;
	}
}