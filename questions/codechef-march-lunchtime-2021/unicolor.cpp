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

int c, m;
int par[1001];
int siz[1001];
			 	
int find(int u) {
	int u2 = u;
	while (u^par[u]) u = par[u];
	par[u2] = u;
	return u;
}

int join (int u, int v) {
	int p1 = find(u);
	int p2 = find(v);
	if (siz[p1] < siz[p2]) {
		par[p1] = p2;
		siz[p2] += siz[p1];
		return p2;
	}
	else {
		par[p2] = p1;
		siz[p1] += siz[p2];
		return p1;
	}
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	while (t--) {
		cin >> c >> n >> m;
		vector<pair<pii, int> > rngs;

		for (int i = 0; i < c; i++) {
			int x; cin >> x;
			for (int j = 0; j < x; j++) {
				int l, r; cin >> l >> r;
				rngs.pb(mp(mp(l, r), i));
			}
		}
		sort(rngs.begin(), rngs.end());
		for (int i = 0; i < c; i++) {
			par[i] = i;
			siz[i] = 1;
		}
		int l, r;
		l = rngs[0].ff.ff;
		r = rngs[0].ff.ss;
		int typ = rngs[0].ss;
		set<int> dist;
		vector<pii> r2;

		for (int i = 1; i < rngs.size(); i++) {
			int a = rngs[i].ff.ff;
			int b = rngs[i].ff.ss;
			if (a <= r) {
				r = max(r, b);
				typ = join(typ, rngs[i].ss);
			}
			else {
				r2.pb(mp(l, r));
				dist.insert(typ);
				l = a;
				r = b;
				typ = rngs[i].ss;
			}
		}
		r2.pb(mp(l, r));
		dist.insert(typ);
		set<int> dist2;
		for (int u : dist) dist2.insert(find(u));

		// for (pii p : r2) cout << p.ff << ' ' << p.ss << '\n';

		int ans = pwr(m, dist2.size());
		for (int i = 0; i < r2.size()-1; i++) {
			ans = mulmod(ans, pwr(m, r2[i+1].ff-r2[i].ss-1));
		}
		ans = mulmod(ans, pwr(m, r2[0].ff-1));
		ans = mulmod(ans, pwr(m, n-r2[r2.size()-1].ss));

		cout << ans << '\n';
	}
}

