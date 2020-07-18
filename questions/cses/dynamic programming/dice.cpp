#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 1e9+7;

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

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

int main () {
	int n; cin >> n;
	int ans[n+1];
	ans[0] = 1;
	for (int i = 1; i <= n; i++) {
		ans[i] = 0;
		for (int j = 1; j <= 6; j++) {
			if (i-j < 0) break;
			ans[i] = addmod(ans[i], ans[i-j]);
		}
	}
	cout << ans[n] << endl;
}

