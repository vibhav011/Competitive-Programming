#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define fio fflush(stdout)

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

	int n; cin >> n;

	vector<pii> k, k2;
	int orig[n+1];

	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		k.pb(mp(x, i));
		orig[i] = x;
	}
	sort(k.begin(), k.end());
	bool ch = true;

	while (ch) {
		ch = false;
		int cnt = 0;
		for (pii p : k) {
			if (p.ff == 0) cnt++;
			else k2.pb(p);
		}
		if (cnt) ch = true;
		n -= cnt;
		k.clear();
		for (pii p : k2) {
			k.pb(mp(p.ff-cnt, p.ss));
		}
		k2.clear();
		cnt = 0;
		for (pii p : k) {
			if (p.ff == n) cnt++;
			else k2.pb(p);
		}
		if (cnt) ch = true;
		n -= cnt;
		k = k2;
		k2.clear();
	}
	vector<pair<int, pii> > difs;
	for (pii p : k) {
		for (pii q : k) {
			if (p == q) continue;
			difs.pb(mp(-abs(p.ff-q.ff), mp(p.ss, q.ss)));
		}
	}
	if (n == 2) {
		cout << "! 0 0" << endl; fio;
		return 0;
	}
	sort(difs.begin(), difs.end());
	for (auto z : difs) {
		int x = z.ss.ff;
		int y = z.ss.ss;
		if (orig[x] < orig[y]) swap(x, y);
		cout << "? " << x << ' ' << y << endl; fio;
		string s; cin >> s;
		if (s == "Yes") {
			cout << "! " << x << ' ' << y << endl; fio;
			return 0;
		}
	}
	cout << "! 0 0" << endl; fio;
	return 0;
}

