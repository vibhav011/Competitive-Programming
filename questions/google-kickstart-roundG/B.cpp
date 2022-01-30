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

int k;

int solve(const vector<pii> &v) {
	vector<int> all_v, v1, v2;

	for (pii x : v) {
		v1.pb(x.ff);
		v2.pb(x.ss);
		all_v.pb(x.ff);
		all_v.pb(x.ss);
	}
	assert(v1.size() == k && v2.size() == k && all_v.size() == 2*k);
	sort(all_v.begin(), all_v.end());
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	vector<int> pref(k, 0), suf(k, 0);

	for (int i = 1; i < k; i++) {
		pref[i] = pref[i-1] + i * (v2[i] - v2[i-1]);
		assert(pref[i] >= 0);
	}
	for (int i = k-2; i >= 0; i--) {
		suf[i] = suf[i+1] + (k-i-1) * (v1[i+1] - v1[i]);
		assert(suf[i] >= 0);
	}
	int ans = -1;
	int all_min = 1LL << 55LL;

	for (int x : all_v) {
		// if (x == all_v[2*k-1]) continue;
		int i1 = upper_bound(v2.begin(), v2.end(), x) - v2.begin(); i1--;
		int i2 = lower_bound(v1.begin(), v1.end(), x) - v1.begin();

		i1 = max(i1, 0LL);
		i2 = min(i2, k-1);
		
		int cur_min = suf[i2] + max((v1[i2]-x)*(k-i2), 0LL) + pref[i1] + max(0LL, (x - v2[i1])*(i1+1));
		// cout << "lol\n";
		// cout << x << ' ' << cur_min << '\n';
		if (cur_min < all_min) {
			all_min = cur_min;
			ans = x;
		}
	}
	return ans;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	
	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #"<<cn<<": ";

		cin >> k;
		vector<vector<int> > pts(k, vector<int>(4));
		for (int i = 0; i < k; i++) {
			cin >> pts[i][0] >> pts[i][1] >> pts[i][2] >> pts[i][3]; 
		}
		vector<pii> v(k);
		for (int i = 0; i < k; i++) {
			v[i].ff = pts[i][0];
			v[i].ss = pts[i][2];
		} 
		// for (pii l : v) cout << l.ff << ' ' << l.ss << '\n';
		int ans_x = solve(v);
		for (int i = 0; i < k; i++) {
			v[i].ff = pts[i][1];
			v[i].ss = pts[i][3];
		}
		// for (pii l : v) cout << l.ff << ' ' << l.ss << '\n';
		int ans_y = solve(v);

		cout << ans_x << ' ' << ans_y << '\n';
	}
}

