#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int n;
const int M = 100005;
vector<int> adj[M];
int vis[M], dep[M], par[M], maxdep[M];

void dfs(int u, int d) {
	dep[u] = d;
	vis[u] = 1;

	int mxval = 0;
	int ans = u;

	for (int v : adj[u]) {
		if (!vis[v]) {
			dfs(v, d+1);
			par[v] = u;
			if (dep[maxdep[v]] > mxval) {
				mxval = dep[maxdep[v]];
				ans = maxdep[v];
			}
		}
	}
	maxdep[u] = ans;
}

vector<int> dfs2(int u) {
	vis[u] = 1;
	vector<int> ret = {u, maxdep[u], dep[maxdep[u]]-dep[u]};
	int mx1 = 0, mx2 = 0, id1, id2;

	for (int v: adj[u]) {
		if (!vis[v]) {
			vector<int> temp = dfs2(v);

			if (dep[maxdep[v]] > mx1) {
				mx2 = mx1;
				id2 = id1;
				id1 = maxdep[v];
				mx1 = dep[maxdep[v]];
			}
			else if (dep[maxdep[v]] > mx2) {
				id2 = maxdep[v];
				mx2 = dep[maxdep[v]];
			}

			if (temp[2] > ret[2]) ret = temp;
		}
	}

	if (mx1+mx2-2*dep[u] > ret[2]) {
		ret[2] = mx1+mx2-2*dep[u];
		ret[1] = id2;
		ret[0] = id1;
	}

	return ret;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	
	while (t--) {
		cin >> n;
		for (int i = 0; i <= n; i++) {
			adj[i].clear();
			vis[i] = dep[i] = par[i] = 0;
		}

		for (int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].pb(v);
			adj[v].pb(u);
		}

		if (n == 2) {
			cout << "0\n";
			continue;
		}

		int dg = 1;

		while (adj[dg].size() == 1) dg++;

		dfs(dg, 0);

		for (int i = 0; i <= n; i++) {
			vis[i] = 0;
		}

		vector<int> v = dfs2(dg);

		int mx1 = dep[v[0]], mx2 = dep[v[1]], id1 = v[0], id2 = v[1];

		set<int> levs;
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() == 1) {
				levs.insert(i);
			}
		}

		levs.erase(id1);
		levs.erase(id2);

		// cout << "test " << id1 << ' ' << id2 << '\n';

		set<int> inpath;
		int p = id1;
		while (p != dg) {
			inpath.insert(p);
			p = par[p];			
		}
		p = id2;
		while (p != dg) {
			inpath.insert(p);
			p = par[p];
		}
		inpath.insert(dg);

		cout << n-1-mx1-mx2 << '\n';
		int last = id1;

		for (int x : levs) {
			// cout << "test " <<  x << '\n';
			do {
				cout << x << ' ' << par[x] << ' ' << x << ' ' << last << '\n';
				last = x;
				x = par[x];
			} while (inpath.find(x) == inpath.end());
		}

	}
}

