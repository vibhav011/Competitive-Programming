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

const int M = 2e5+5;
int n;
vector<int> adj[M];
int a[M];
ll siz[M];
int levs[M];
ll mx[M];

void dfs1(int u) {
	siz[u] = a[u];
	for (int v : adj[u]) {
		dfs1(v);
		siz[u] += siz[v];
	}
}
void dfs2(int u) {
	if (adj[u].size() == 0) {
		levs[u] = 1;
		return;
	}
	levs[u] = 0;
	for (int v : adj[u]) {
		dfs2(v);
		levs[u] += levs[v];
	}
}

void dfs(int u) {
	if (adj[u].size() == 0) {
		mx[u] = a[u];
		return;
	}
	ll mxtill = 0;
	for (int v : adj[u]) {
		dfs(v);
		mxtill = max(mxtill, mx[v]);
	}
	ll uni = siz[u]/levs[u];
	int extra = (siz[u]%levs[u] > 0);
	mx[u] = max(mxtill, uni+extra);
}


int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n; cin >> n;
	for (int i = 0; i < n-1; i++) {
		int p; cin >> p;
		adj[p].pb(i+2);
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i+1];
	}
	dfs1(1); dfs2(1);

	dfs(1);
	cout << mx[1] << endl;
	
}

