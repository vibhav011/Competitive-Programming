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

int n, m;
vector<int> adj[100005];
int vis[100005];
int typ[100005];
bool pos;

void dfs(int u, int t) {
	if (vis[u]) {
		if (typ[u]^t) {
			pos = false;
		}
		return;
	}
	vis[u] = 1;
	typ[u] = t;
	for (int v : adj[u]) {
		dfs(v, 3-t);
	}
}
signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	fill(vis, vis+n+1, 0);

	pos = true;

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) dfs(i, 1);
	}

	if (!pos) cout << "IMPOSSIBLE\n";
	else {
		for (int i = 1; i <= n; i++) cout << typ[i] << ' ';
		cout << '\n';
	}
}

