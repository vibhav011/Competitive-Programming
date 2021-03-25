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

const int PM = 2e7+5;
// int spf[PM];
vector<int> primes;
vector<int> spf;

void sieve () {
	spf.resize(PM, -1);
	for (int i = 2; i < PM; i++) {
		if (spf[i] == -1) {primes.pb(i); spf[i] = i;}
		for (int j = 0; j < primes.size() && primes[j]*i < PM; j++) {
			spf[primes[j]*i] = primes[j];
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

	sieve();
	int t; cin >> t;
	
	while (t--) {
		int c, d, x;
		cin >> c >> d >> x;
		vector<int> facs;
		int ss = sqrtl(x);
		for (int i = 1; i <= ss+2; i++) {
			if (x%i == 0) {
				int r = x/i;
				if (i < r) {
					facs.pb(i);
					facs.pb(r);
				}
				else if (i == r) facs.pb(i);
				else break;
			}
		}
		int ans = 0;
		for (int g : facs) {
			int ex = g+d;
			if (ex%c == 0) {
				int r = ex/c;
				int cur = 1;
				int cs = spf[r];
				if (r == 1) ans++;
				else {
					while (r > 1) {
						if (r%cs == 0) {
							r /= cs;
						}
						else {
							cur *= 2;
							cs = spf[r];
						}
					}
					ans += cur*2;
				}
			}
		}
		cout << ans << '\n';
	}
}

