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

int gcd (int a, int b) {
	if (a > b) swap(a, b);
	if (b%a == 0) return a;
	return gcd(b%a, a);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, k;
	cin >> n >> m >> k;
	int *a;
	if (k) a = new int[k];
	for (int i = 0; i < k; i++) cin >> a[i];

	if (m == 1 && k > 0) {
		cout << "-1\n";
		return 0;
	} 

	int cur = 1;
	bool pos = true;
	for (int i = 1; i < k && pos; i++) {
		if (a[i] == a[i-1]+1) cur++;
		else cur = 1;
		if (cur >= m) pos = false;
	}
	if (!pos) {
		cout << "-1\n";
		return 0;
	} 

	double invm = 1.0/m;

	vector<pair<double, double> > ans(n+m+1);					// a + bx
	bool hap = false;
	for (int i = n+m; i >= n; i--) ans[i].ff = ans[i].ss = 0;
	int j = k-1;
	for (int i = n-1; i >= 0; i--) {
		bool f = false;
		if (k > 0 && j >= 0) {
			if (i == a[j]) {
				f = true;
				hap = false;
				ans[i].ss = 1;
				j--;
			}
		}
		if (!f) {
			if (!hap) {
				hap = true;
				double s1 = 0, s2 = 0;
				for (int j = i+1; j <= i+m; j++) {
					s1 += ans[j].ff;
					s2 += ans[j].ss;
				}
				ans[i].ff = 1 + invm * s1;
				ans[i].ss = invm * s2;
			}
			else {
				ans[i].ff = ans[i+1].ff + invm * (ans[i+1].ff - ans[i+m+1].ff);
				ans[i].ss = ans[i+1].ss + invm * (ans[i+1].ss - ans[i+m+1].ss);
			}
		}
	}
	// cout << ans[1].ff << endl;
	cout.precision(5);
	cout << fixed;
	cout << ans[0].ff / (1 - ans[0].ss) << '\n';
}

