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
	int n, x; cin >> n >> x;
	
	int ans[x+1];
	fill(ans, ans+x+1, -1);
	int c[n];
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		if (c[i] <= x) ans[c[i]] = 1;
	}
	sort(c, c+n);
	
	ans[0] = 0;
	for (int i = 1; i <= x; i++) {
		if (ans[i] == 1) continue;
		for (int j = 0; j < n; j++) {
			if (c[j] > i) break;
			if (ans[i-c[j]] != -1) {
				if (ans[i] == -1) ans[i] = 1 + ans[i-c[j]];
				else ans[i] = min(ans[i], 1+ans[i-c[j]]);
			}
		}
	}
	cout << ans[x] << endl;
}

