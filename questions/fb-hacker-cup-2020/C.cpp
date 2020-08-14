#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define mll map<ll, ll> 

using namespace std;

ll MOD = 998244353;

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

int bsh(ll val, pll ar[], int n) {		// return ind such that val >= ar[ind] and val < ar[ind+1]
	int a = 0, b = n, c = (a+b)/2;
	if (val < ar[0].ff || val >= ar[n-1].ff) return -1;

	while (a < b) {
		if (val == ar[c].ff) return c;
		if (val < ar[c].ff) b = c;
		else a = c+1;
		c = (a+b)/2;
	}
	return -1;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		printf("Case #%d: ", cn);
		int n; cin >> n;
		pii ph[n];
		for (int i = 0; i < n; i++) cin >> ph[i].ff >> ph[i].ss;
		sort(ph, ph+n);
		// vector<int> ar_rt[n];			// right fell trees
		// vector<int> ar_lt[n];			// left fell trees
		// for (int i = 0; i < n; i++) {
		// 	int ind1 = bsh(ph[i].ff + ph[i].ss, ph, n);
		// 	int ind2 = bsh(ph[i].ff - ph[i].ss, ph, n);
		// 	if (ind1 != -1) ar_rt[ind1].pb(i);
		// 	if (ind2 != -1) ar_lt[ind2].pb(i);
		// }
		mll dp_lt, dp_rt;
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			ll p = ph[i].ff + ph[i].ss;
			dp_rt[p] = max(dp_rt[p], ph[i].ss + dp_rt[ph[i].ff]);
		}
		for (int i = n-1; i >= 0; i--) {
			ll p = ph[i].ff - ph[i].ss;
			dp_lt[p] = max(dp_lt[p], ph[i].ss + dp_lt[ph[i].ff]);
		}
		mll::iterator it1, it2;
		it1 = dp_rt.begin(), it2 = dp_lt.begin();

		while (it1 != dp_rt.end() || it2 != dp_lt.end()) {
			if (it1->ff < it2->ff) {
				ans = max(ans, it1->ss);
				it1++;
			}
			else if (it1->ff > it2->ff) {
				ans = max(ans, it2->ss);
				it2++;
			}
			else {
				ans = max(ans, it2->ss + it1->ss);
				it1++; it2++;
			}
		}
		cout << ans << endl;
	}
}

