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

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, k, q;
	cin >> n >> k >> q;
	int p2 = (mulmod(3, pwr(2, k))-2+MOD)%MOD;
	int a[n+2][k+1], w[2*k+1][k+1];
	for (int i = 0; i <= k; i++) a[0][i] = a[n+1][i] = 0;
	for (int i = 1; i <= n; i++) cin >> a[i][0];
	a[1][0] = 9;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			a[j][i] = 0;
			if (j > 1) a[j][i] = addmod(a[j][0], a[j-1][i-1]);
			if (j < n) a[j][i] = addmod(a[j][i], addmod(a[j][0], a[j+1][i-1]));
		}
	}
	// for (int i = 0; i < n+2; i++) cout << a[i][1] << ' ';
	// cout << '\n';
	for (int i = 0; i < 2*k+1; i++) w[i][0] = 0;
	w[k][0] = 1;
	w[0][k] = w[2*k][k] = 1;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= 2*k-1; j++) {
			w[j][i] = addmod(w[j-1][i-1], w[j+1][i-1]);
			if (j == k) w[j][i] = addmod(w[j][i], 2);
		}
	}
	int act[k+1];
	act[0] = 1;
	for (int i = 1; i <= k; i++) {
		int temp = 0;
		for (int j = k; j >= k-i; j--) temp = addmod(temp, w[j][i]);
		act[i] = addmod(act[i-1], temp);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = addmod(ans, a[i][k]);
	cout << ans << ' ' << p2 << endl;
	while (q--) {
		int u, b; cin >> u >> b;
		int d = b - a[u][0];
		a[u][0] = b;
		d = (d%MOD + MOD)%MOD;
		ans = addmod(ans, mulmod(p2, d));
		int sub = 0;
		if (u - k <= 0) {
			sub = addmod(sub, mulmod(d, act[k-u]));
			if (k-u-1 >= 0) sub = addmod(sub, mulmod(d, act[k-u-1]));
		}
		if (u + k > n) {
			u = n+1-u;
			sub = addmod(sub, mulmod(d, act[k-u]));
			if (k-u-1 >= 0) sub = addmod(sub, mulmod(d, act[k-u-1]));
		}
		if (u == 1 || u == n) sub = addmod(sub, d);
		ans = addmod(ans, (MOD-sub)%MOD);
		cout << ans << endl;
	}
}

