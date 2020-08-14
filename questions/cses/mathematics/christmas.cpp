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

inline ll submod(ll a, ll b){
	return (((a%MOD)-(b%MOD)+MOD)%MOD);
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

	int n; cin >> n;
	if (n == 1) {
		cout << "0\n";
		return 0;
	}
	ll ans = 0;
	for (int i = 2; i <= n; i++) {
		if (i&1) ans = submod(ans, pwr(fac[i], MOD-2));
		else ans = addmod(ans, pwr(fac[i], MOD-2));
	}
	ans = mulmod(ans, fac[n]);
	cout << ans << endl;
}