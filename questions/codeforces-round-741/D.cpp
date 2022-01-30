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

int q;
string s;
/*
0, 0		-1
1-, i        0
1+, i        1
1-1+, i, j   2
1+1-, i, j   4
*/
int prep[300005][20];

int comb(int a, int b) {
	int ret;

	if (a == -1) ret = b;
	else if (b == -1) ret = a;
	else {
		if (a == b) {
			if (a < 2) ret = -1;
			else ret = a;
		}
		else {
			if (a > b) {
				if (a + b == 1) ret = 4;
				else if (a + b == 2) ret = 0;
				else if (a + b == 4) ret = 1;
				else if (a + b == 3) ret = 0;
				else if (a + b == 5) ret = 1;
				else if (a + b == 6) ret = -1;
			}
			else {
				if (a + b == 1) ret = 2;
				else if (a + b == 2) ret = 1;
				else if (a + b == 4) ret = 0;
				else if (a + b == 3) ret = 1;
				else if (a + b == 5) ret = 0;
				else if (a + b == 6) ret = -1;
			}
		}
	}
	return ret;
}

void func() {
	int temp, v1, v2;
	for (int p = 0; p < 20; p++) {
		int l = 1<<p;
		if (l > n) break;
		for (int i = 0; i < n; i++) {
			if (i + l > n) break;

			if (p == 0) {
				if (s[i] == '+') temp = 1;
				else temp = 0;
				// temp[1] = i;
				prep[i][p] = temp;
				continue;
			}
			v1 = prep[i][p-1];
			v2 = prep[i+(l>>1)][p-1];
			temp = comb(v1, v2);
			prep[i][p] = temp;
		}
	}
}

int calc(int l, int r) {
	int ret = -1;
	int a = l;
	for (int p = 19; p > -1; p--) {
		if (a > r) break;
		if (a + (1<<p)-1 > r) continue;
		ret = comb(ret, prep[a][p]);
		a += 1<<p;
	}
	if (ret == -1) return 0;
	if (ret < 2) return 1;
	return 2;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	while (t--) {
		cin >> n >> q;
		cin >> s;

		func();

		int l, r;

		while (q--) {
			cin >> l >> r;
			cout << calc(l-1, r-1) << '\n';
		}

	}
}

