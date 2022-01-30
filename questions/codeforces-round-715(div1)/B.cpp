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

int dp[62];
int n_max;
const int inf = 1000000000000000000LL;

vector<int> solve(int n, int k) {
	// cout << n << ' ' << k << endl;
	vector<int> ans(n, -1);
	if (k == 1) {
		for (int i = 0; i < n; i++) ans[i] = i+1;
		return ans;
	}
	if (n <= 1) {
		if (n == 0) return ans;
		if (n == 1) {
			if (k == 1) {
				ans[0] = 1;
				return ans;
			}
			return ans;
		}
	}
	if (n >= n_max) {
		for (int i = 0; i < n-n_max+1; i++) ans[i] = i+1;
		vector<int> a2 = solve(n_max-1, k);
		for (int j = n-n_max+1; j < n; j++) ans[j] = a2[j-n+n_max-1]+n-n_max+1;
		return ans;
	}
	if (dp[n] < k) {
		// ans.clear();
		return ans;
	}
	int j = 1;
	int cur = 0;
	for (; j <= n; j++) {
		cur += dp[n-j];
		if (cur >= k) break;
	}
	k -= cur-dp[n-j];
	// int rem = k%dp[n-j];
	// int tim = (k-1)/dp[n-j]+1;
	// if (rem == 0) rem = dp[n-j];
	// cout << "Vals: " << j-1 << ", " << n-j << ", " << tim << ", " << rem << endl;
	// vector<int> a1 = solve(j-1, tim);
	vector<int> a2 = solve(n-j, k);
	ans[0] = j;
	for (int i = 1; i <= j-1; i++) ans[i] = j-i;
	for (int i = j; i < n; i++) ans[i] = a2[i-j]+j;
	return ans;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	n_max = 62;
	dp[0] = 1;
	for (int i = 1; i < n_max; i++) dp[i] = (1LL << (i-1));

	int t; cin >> t;
	
	while (t--) {
		int n, k;
		cin >> n >> k;
		vector<int> ans = solve(n, k);
		if (ans[0] != -1) for (int x : ans) cout << x << ' ';
		else cout << "-1";
		cout << endl;
	}
}

