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

struct coor {
	int a, b, c;
	coor () {
		a = b = c = 0;
	}
	coor& operator-(const coor &q) {
		this->a += -q.a;
		this->b += -q.b;
		this->c += -q.c;
		return *this;
	}
	coor& operator=(const coor &q) {
		this->a = q.a;
		this->b = q.b;
		this->c = q.c;
		return *this;
	}
};

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	vector<pii> pts(n);
	for (int i = 0; i < n; i++) {
		cin >> pts[i].ff >> pts[i].ss;
	}
	int m; cin >> m;
	vector<pair<coor, coor> > ss(m+1);
	ss[0].ff.a = 1;
	ss[0].ss.b = 1;
	for (int i = 1; i <= m; i++) {
		int t; cin >> t;
		int p;
		if (t == 1) {
			ss[i].ff = ss[i-1].ss;
			ss[i].ss = ss[i].ss - ss[i-1].ff;
		}
		else if (t==2) {
			ss[i].ff = ss[i].ff - ss[i-1].ss;
			ss[i].ss = ss[i-1].ff;
		}
		else if (t==3) {
			cin >> p;
			ss[i].ff = ss[i].ff - ss[i-1].ff;
			ss[i].ss = ss[i-1].ss;
			ss[i].ff.c += 2*p;
		}
		else if (t==4) {
			cin >> p;
			ss[i].ff = ss[i-1].ff;
			ss[i].ss = ss[i].ss - ss[i-1].ss;
			ss[i].ss.c += 2*p;
		}
	}
	int q; cin >> q;
	while (q--) {
		int a, b;
		cin >> a >> b;
		b--;
		cout << ss[a].ff.a * pts[b].ff + ss[a].ff.b * pts[b].ss + ss[a].ff.c << ' '
			 << ss[a].ss.a * pts[b].ff + ss[a].ss.b * pts[b].ss + ss[a].ss.c << '\n';
	}
}

