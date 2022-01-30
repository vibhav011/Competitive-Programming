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

bool check_composite(int n, int a, int d, int s) {
	int x = pwr(a, d, n);
	if (x == 1 || x == n - 1)
		return false;
	for (int r = 1; r < s; r++) {
		x = x * x % n;
		if (x == n - 1)
			return false;
	}
	return true;
};

const int first12prime[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

bool isPrime(int n) {			// O(log n) time complexity
	if (n < 2)
		return false;

	int r = 0;
	int d = n - 1;
	while ((d & 1) == 0) {
		d >>= 1;
		r++;
	}

	for (int i = 0; i < 12; i++) {
		int a = first12prime[i];
		if (n == a)
			return true;

		if (check_composite(n, a, d, r))
			return false;
	}
	return true;
}

const int PM = 2e5+5;

vector<int> primes;
vector<bool> is_comp;

void sieve () {
	is_comp.resize(PM, false);
	for (int i = 2; i < PM; i++) {
		if (!is_comp[i]) primes.pb(i);
		for (int j = 0; j < primes.size() && primes[j]*i < PM; j++) {
			is_comp[primes[j]*i] = true;
			if (i % primes[j] == 0) break;
		}
	}
}

inline int sfunc(int a, int b) {
	return a+b;
}

int n;									// array size
int *stree;								// stree = new int[2 * n]

void build() {							// build the tree
	for (int i = n - 1; i > 0; --i) stree[i] = sfunc(stree[i<<1], stree[i<<1|1]);
}

void modify(int p, int value) {			// set value at position p
	for (stree[p += n] = value; p > 1; p >>= 1) stree[p>>1] = sfunc(stree[p], stree[p^1]);
}

int query(int l, int r) {				// query on interval [l, r)
	int res = 0;						// DEFAULT
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc(res, stree[l++]);
		if (r&1) res = sfunc(res, stree[--r]);
	}
	return res;
}

int m, n2;

vector<vector<int> >adj, adjT, sccNodes;
vector<set<int> > strong, strongT;
vector<int> vis, isLoop, label;
stack<int> st;
vector<int> tp;

void dfs1(int u) {
	if (vis[u]) return;
	vis[u]=1;
	for (int v : adj[u]) dfs1(v);
	st.push(u);
}

void dfs2(int u, int cur) {
	if (vis[u]) return;
	vis[u]=1;
	sccNodes[cur].pb(u);
	label[u] = cur;
	for (int v : adjT[u]) dfs2(v, cur);
}

void topo(int u) {
	if (vis[u]) return;
	vis[u]=1;
	for (int v : strong[u]) topo(v);
	tp.pb(u);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	while (t--) {
		cin >> n >> m;
		adj.assign(n+1, vector<int>());
		adjT.assign(n+1, vector<int>());
		sccNodes.assign(n+1, vector<int>());
		strong.assign(n+1, set<int>());
		strongT.assign(n+1, set<int>());
		vis.assign(n+1, 0);
		isLoop.assign(n+1, 0);
		label.assign(n+1, 0);
		st = stack<int> ();

		vector<int> ans(n+1, 0);

		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			if (a==b) isLoop[a] = 1;
			else {
				adj[a].pb(b);
				adjT[b].pb(a);
			}
		}
		for (int i = 1; i <= n; i++)
			dfs1(i);
		vis.assign(n+1, 0);

		int cur = 1;
		while (!st.empty()) {
			int u = st.top(); st.pop();
			dfs2(u, cur);
			cur++;
		}
		n2 = cur-1;
		for (int i = 1; i <= n; i++) {
			for (int v : adj[i]) {
				strong[label[i]].insert(label[v]);
				strongT[label[v]].insert(label[i]);
			}
		}
		vis.assign(n+1, 0);
		tp.clear();
		
		for (int i = 1; i <= n2; i++)
			topo(i);
		reverse(tp.begin(), tp.end());

		ans[label[1]] = 1;
		if (isLoop[1] || sccNodes[label[1]].size() > 1) ans[label[1]] = -1;
		for (int u : tp) {
			if (ans[u] != 0) continue;
			int pts = 0;
			int inf = 0;
			for (int v : strongT[u]) {
				if (ans[v] == -1) {
					inf = 1; break;
				}
				pts += ans[v];
			}
			if (inf) ans[u] = -1;
			else {
				if (pts == 0) ans[u] = 0;
				else {
					if (sccNodes[u].size() > 1 || isLoop[sccNodes[u][0]]) ans[u] = -1;
					else ans[u] = min(2LL, pts);
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			cout << ans[label[i]] << ' ';
		}
		cout << '\n';

	}
}

