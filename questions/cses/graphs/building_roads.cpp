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

int par[100005];
int siz[100005];

int find(int u) {
	int u2 = u;
	while (u^par[u]) u = par[u];
	return par[u2] = u;
}

int join (int u, int v) {
	int r1 = find(u);
	int r2 = find(v);

	if (r1 == r2) return r1;

	if (siz[r1] < siz[r2]) {
		par[r1] = r2;
		siz[r2] += siz[r1];
		return r2;
	}
	else {
		par[r2] = r1;
		siz[r1] += siz[r2];
		return r1;
	}
}
int n, m;

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		par[i] = i;
		siz[i] = 1;
	}
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		join(u, v);
	}
	vector<int> tc;
	for (int i = 1; i <= n; i++) {
		if (i == par[i]) tc.pb(i);
	}
	cout << tc.size()-1 << '\n';
	for (int i = 0; i < tc.size()-1; i++) cout << tc[i] << ' ' << tc[i+1] << '\n';
}

