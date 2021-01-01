#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;
int cnt;
vector<int> adj[200005];
bool vis[200005];
int par[200005], siz[200005];
void dfs (int u) {
	if (vis[u]) return;
	vis[u] = true;
	cnt++;
	for (int i = 0; i < adj[u].size(); i++) dfs(adj[u][i]);
}

int cat(int p) {
	int q = p;
	while (par[p]^p) p = par[p];
	par[q] = p;
	return p;
}

void join(int a, int b) {
	a = cat(a);
	b = cat(b);
	if (siz[a] > siz[b]) swap(a, b);
	par[a] = b;
	siz[b] += siz[a];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m, k;
		cin >> n >> m >> k;
		for (int i = 0; i <= n; i++) {vis[i] = false; adj[i].clear();};
		cnt = 0;
		vector<pair<int, pii> > ed(m);
		int ind = 0, cur = 1e9;
		for (int i = 0; i < m; i++) {
			int x, y, s;
			cin >> x >> y >> s;
			ed[i].ss.ff = x;
			ed[i].ss.ss = y;
			ed[i].ff = s;
			if (abs(s-k) < cur) {
				cur = abs(s-k);
				ind = i;
			}
			if (s <= k) {
				adj[x].pb(y);
				adj[y].pb(x);
			}
		}
		dfs(1);

		if (cnt == n) {
			cout << abs(ed[ind].ff-k) << endl;
			continue;
		}

		ll ans = 0;
		for (int i = 0; i <= n; i++) {
			par[i] = i;
			siz[i] = 1;
		}

		sort(ed.begin(), ed.end());
		cur = 0, ind = 0;
		while (cur < n-1) {
			int p = cat(ed[ind].ss.ff);
			int q = cat(ed[ind].ss.ss);
			if (p^q) {
				join(p, q);
				cur++;
				if (ed[ind].ff >= k) ans += ed[ind].ff-k;
			}
			ind++;
		}
		cout << ans << endl;
	}
}

