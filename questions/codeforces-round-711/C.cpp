#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
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

int larg(int x) {
	int r = 0;
	while (x > 1) {
		r++;
		x >>= 1;
	}
	return (1LL << r);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;

		if (k == 1) { 
			cout << "1\n";
			continue;
		}

		int dp[n+2][k+1];
		// dp[1][k] = 1;
		// dp[1][k-1] = 1;
		dp[0][k] = 1;

		for (int i = 1; i <= n+1; i++) {
			dp[i][k] = 0;
		}

		int j = k-1;
		int ad = 1;
		int i = 1;
		int sm = 1;
		while (j > 0) {
			while (i != n+1 && i != 0) {
				dp[i][j] = sm;
				i += ad;
				if (i == 0 || i == n+1) break;
				sm += dp[i-ad][j+1];
				sm = sm%MOD;
			}
			if (i == n+1) {
				i = n;
				ad = -1;
				sm = 0;
			}
			if (i == 0) {
				i = 1;
				ad = 1;
				sm = 0;
			}
			j--;
		}
		int ans = 1;
		for (int i = 1; i <= k; i++) for (int j = 1; j <= n; j++) {
			// cout << dp[j][i] << '\n';
			ans += dp[j][i];
			ans = ans%MOD;
		}
		cout << ans << '\n';
		// cout << "yay\n";
	}
	
}

