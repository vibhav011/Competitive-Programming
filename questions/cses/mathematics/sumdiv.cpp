#include <bits/stdc++.h>
#define ll long long int

using namespace std;

const ll MOD = 1e9+7;

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return (((a%MOD)*(b%MOD))%MOD);
}

ll pwr(ll x, ll y) {
	ll res = 1;
	x = x%MOD;
	while (y > 0) {
		if (y&1) res = (res*x)%MOD;

		y = y>>1;
		x = (x*x)%MOD;
	}
	return res;
}

int main () {
	ll n; cin >> n;
	ll ans = 0;
	ll i = 1;
	while (i <= n) {
		ll r = n/(n/i);
		ans = addmod(ans, mulmod(mulmod(mulmod(r-i+1, r+i), pwr(2, MOD-2)), n/i));
		i = r+1;
	}
	cout << ans << endl;
}