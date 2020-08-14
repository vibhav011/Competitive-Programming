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
	int M = 1e6+1;
	ll fac[M];
	fac[0] = 1;
	for (int i = 1; i < M; i++)
		fac[i] = mulmod(i, fac[i-1]);

	int t; cin >> t;
	while (t--) {
		ll n, r;
		cin >> n >> r;
		cout << mulmod(fac[n], pwr(mulmod(fac[r], fac[n-r]), MOD-2)) << endl;
	}
}