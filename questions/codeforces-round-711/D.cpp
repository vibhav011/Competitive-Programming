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

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m;
	cin >> n >> m;
	vector<pair<int, pii> > txy;
	for (int i = 0; i < n; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		if (t == 1) {
			x = ceil(x/100000.0);
		}
		txy.pb(mp(t, mp(x, y)));
	}
	vector<int> vis(m+1, -1);

	queue<pii> q;
	q.push(mp(0, 0));
	vis[0] = 0;

	while (!q.empty()) {
		pii p = q.front();
		q.pop();
		
		int t = txy[p.ss].ff, x = txy[p.ss].ss.ff, y = txy[p.ss].ss.ss;
		int cur = p.ff;
		if (p.ss < n-1)
			q.push(mp(cur, p.ss+1));
		if (p.ss == n-1) continue;
		double x1 = x/100000.0;
		for (int i = 1; i <= y; i++) {
			if (t == 1) {
				cur += x;
				if (cur > m) break;
				if (vis[cur] == -1) {
					vis[cur] = p.ss+1;
					q.push(mp(cur, p.ss+1));
				}
			}
			else {
				cur = ceil(cur * x1);
				if (cur > m) break;
				if (vis[cur] == -1) {
					vis[cur] = p.ss+1;
					q.push(mp(cur, p.ss+1));
				}
			}
		}
	}
	for (int i = 1; i <= m; i++) cout << vis[i] << ' ';
	cout << '\n';
	
}

