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

ll fac(int k) {
	if (!k) return 1;
	return mulmod(k, fac(k-1));
}

int main () {
	int n, r;
	cin >> n >> r;
	cout << mulmod(fac(n+r-1), pwr(mulmod(fac(n-1), fac(r)), MOD-2)) << endl;
}