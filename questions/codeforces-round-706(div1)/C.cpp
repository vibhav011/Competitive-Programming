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

int m;
string s[500];
int vis[500][500];

int cnt = 1;

void dfs(int u, int v) {
	if (u < 0 || u >= n || v < 0 | v >= m) return;
	if (s[u][v] != 'X' || vis[u][v]) return;
	vis[u][v] = cnt;
	dfs(u-1, v);
	dfs(u+1, v);
	dfs(u, v-1);
	dfs(u, v+1);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);		

	int t; cin >> t;
	
	while (t--) {
		cin >> n >> m;

		for (int i = 0; i < n; i++) cin >> s[i];

		if (n == 1) {
			for (int i = 0; i < m; i++) s[0][i] = 'X';
			cout << s[0] << '\n';
			continue;
		}
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s[i][j] == 'X') {
					for (int k = i-1; k >= 0; k--) {
						if (s[k][j] == 'X') break;
						s[k][j] = 'X';
						if (j > 0) if (s[k][j-1] == 'X') break;
						if (j < n-1) if (s[k][j+1] == 'X') break;
					}	
				}
			}
		}
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) vis[i][j] = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (vis[i][j]==0 && s[i][j] == 'X') dfs(i, j);
				cnt++;
			}
		}

		int last = 0;
		for (int i = 0; i < m; i++) {
			if (vis[0][i] != 0) {
				if (last == 0) last = vis[0][i];
				else if (last != vis[0][i]) {
					for (int j = i-1; j >= 0; j--) {
						if (s[0][j] == 'X') break;
						if (!(s[0][j+1] == 'X' && s[1][j] == 'X')) s[0][j] = 'X';
						if (s[0][j] == 'X' && s[1][j] == 'X' && vis[0][i]!=vis[1][j]) break;
					}
				}
			}
		}

		for (int i = 0; i < n; i++) cout << s[i] << '\n';
	}
}

