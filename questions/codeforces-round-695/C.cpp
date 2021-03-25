#include <bits/stdc++.h>
#define ll long long
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

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll n[3], x;
	cin >> n[0] >> n[1] >> n[2];
	ll nt = n[0]+n[1]+n[2];
	vector<ll> a[3];
	ll sum[3] = {0, 0, 0};
	for (int i = 0; i < n[0]; i++) {
		cin >> x;
		a[0].pb(x);
		sum[0] += x;
	}
	for (int i = 0; i < n[1]; i++) {
		cin >> x;
		a[1].pb(x);
		sum[1] += x;
	}
	for (int i = 0; i < n[2]; i++) {
		cin >> x;
		a[2].pb(x);
		sum[2] += x;
	}
	sort(a[0].begin(), a[0].end());
	sort(a[1].begin(), a[1].end());
	sort(a[2].begin(), a[2].end());

	ll total = sum[0]+sum[1]+sum[2];
	ll absmin = min(a[0][0], min(a[1][0], a[2][0]));

	if (nt == 3) {
		cout << total - absmin << endl;
		return 0;
	}
	if (int(n[0] == 1)+int(n[1] == 1)+int(n[2] == 1) == 2) {
		cout << total - 2*min(sum[0], min(sum[1], sum[2])) << endl;
		return 0;
	}
	if (int(n[0] == 1)+int(n[1] == 1)+int(n[2] == 1) == 1) {
		ll p = 0;					// 1
		if (n[1] == 1) p = 1; if (n[2] == 1) p = 2;
		ll q = (p+1)%3;
		ll r = 3-p-q;
		cout << total - 2*min(sum[p], min(a[q][0]+a[r][0], min(sum[q], sum[r]))) << endl;
		return 0;
	}
	cout << total - 2*min(sum[0], min(a[0][0]+a[1][0]+a[2][0]-max(a[0][0], max(a[1][0], a[2][0])), min(sum[1], sum[2]))) << endl;
	return 0;
}

