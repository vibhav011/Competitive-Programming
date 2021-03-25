#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y, ll mod = MOD) {
	ll res = 1;
	x = x%mod;
	while (y > 0) {
		if (y&1) res = (res*x)%mod;

		y = y>>1;
		x = (x*x)%mod;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

inline ll submod(ll a, ll b){
	return ((a-b+MOD)%MOD);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	vector<pii> a;
	int b[n+2];
	vector<bool> f(n+2, false);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		a.pb(mp(x, i+1));
		b[i+1] = x;
	}
	sort(a.begin(), a.end());
	int ans = 1;
	for (pii p : a) {
		int i = p.ss;
		int z = 0;
		if (f[i-1]) z++;
		if (f[i+1]) z++;
		if (z < 2)
			ans = mulmod(ans, max(0LL, p.ff-z));
		else {
			int mn = min(b[i-1], b[i+1]);
			ans = mulmod(pwr(mulmod(b[i-1], b[i+1]), MOD-2), mulmod(ans, addmod(mulmod(mn, p.ff-1), mulmod(submod(mulmod(b[i-1], b[i+1]), mn), max(0LL, p.ff-2)))));
		}
		f[i] = true;
	}
	cout << ans << '\n';
}

