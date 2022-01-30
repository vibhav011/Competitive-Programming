#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define Tulip signed main

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

const int MX = 2e5+5;
int m;
vector<int> adj[MX];
int v[MX], t[MX], gp[MX], vis[MX];
bool bip;

void dfs(int r, int g) {
	if (vis[r] || !bip) return;
	vis[r] = 1;
	gp[r] = g;

	for (int x : adj[r]) {
		if (gp[x] != 0 && gp[x] == g) {
			bip = false;
			return;
		}
		dfs(x, 3-g);
	}
}

Tulip () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T; cin >> T;

	while (T--) {
		cin >> n >> m;
		int sv = 0, st = 0;
		for (int i = 1; i <= n; i++) {
			cin >> v[i];
			sv += v[i];
		}
		for (int i = 1; i <= n; i++) {
			cin >> t[i];
			st += t[i];
			adj[i].clear();
			gp[i] = vis[i] = 0;
		}
		for (int i = 0; i < m; i++) {
			int x, y; cin >> x >> y;
			adj[x].pb(y);
			adj[y].pb(x);
		}
		if (abs(sv)%2 != abs(st)%2) {
			cout << "NO\n";
			continue;
		}
		bip = true;
		dfs(1, 1);
		if (!bip) {
			cout << "YES\n";
			continue;
		}

		int ch = 0;
		for (int i = 1; i <= n; i++) {
			if (gp[i] == 1) {
				ch += v[i];
				ch -= t[i];
			}
			else {
				ch -= v[i];
				ch += t[i];
			}
		}
		cout << (ch ? "NO\n" : "YES\n");
	}
}

