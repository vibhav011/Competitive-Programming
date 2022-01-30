#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
// #define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 1000000007;

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

const int inf = 1LL << 50LL;
int g[10][10], vis[10][10];
int r, c, f, s, cnt1, cnt2;

bool check(int i, int j) {
	if (i < 0 || i >= r || j < 0 || j >= c) return false;
	return true;
}

void dfs(int i, int j) {
	if (!check(i, j)) return;
	if (g[i][j] == 0) return;
	if (vis[i][j]) return;
	vis[i][j] = 1;
	bool dif = false;
	if (check(i-1, j)) {
		if (g[i-1][j] != g[i][j] && g[i-1][j]) dif = true;
	}
	if (check(i+1, j)) {
		if (g[i+1][j] != g[i][j] && g[i+1][j]) dif = true;
	}
	if (check(i, j+1)) {
		if (g[i][j+1] != g[i][j] && g[i][j+1]) dif = true;
	}
	if (check(i, j-1)) {
		if (g[i][j-1] != g[i][j] && g[i][j-1]) dif = true;
	}
	if (dif) {
		if (g[i][j] == 1) cnt1++;
		else cnt2++;
	}
	dfs(i-1, j);
	dfs(i+1, j);
	dfs(i, j+1);
	dfs(i, j-1);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";

		cin >> r >> c >> f >> s;
		string s1[r], s2[r];

		for (int i = 0; i < r; i++) cin >> s1[i];
		for (int i = 0; i < r; i++) cin >> s2[i];


		int ans = 0;
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				vis[i][j] = 0;
				if (s1[i][j] == s2[i][j]) g[i][j] = 0;
				else {
					ans++;
					if (s1[i][j] == 'M') g[i][j] = 1;
					else g[i][j] = 2;
				}
			}
		}

		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (g[i][j] && !vis[i][j]) {
					cnt1 = 0; cnt2 = 0;
					dfs(i, j);
					ans -= min(cnt1, cnt2);
				}
			}
		}
		cout << ans << '\n';

	}

}

