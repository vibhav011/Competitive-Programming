#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
// #define ss second
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

const int inf = 1LL << 50LL;

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	
	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";

		int a[3];
		cin >> a[0] >> a[1] >> a[2];
		sort(a, a+3);
		int L = 360LL*12LL*10000000000LL;
		int M = 120000000000LL;
		int NN = 1000000000LL;

		int h, m, s, theta, theta2;
		bool fn = false;
		for (int i = 0; i < 3 && !fn; i++) {
			for (int j = 0; j < 3 && !fn; j++) {
				for (int k = 0; k < 3 && !fn; k++) {
					if (i == j || j == k || i == k) continue;
					h = a[i];
					m = a[j];
					s = a[k];
					int mh = (m-h+L)%L;
					int sm = (s-m+L)%L;
					int sh = (s-h+L)%L;
					if ((mh*708)%L == (sm*11)%L && (mh*719)%L == (sh*11)%L) {
						fn = true;
						theta = (((((12*h-m+L)%L)*17)%L)*3049)%L;
						theta2 = (theta*17408)%L;
						theta2 = (theta2*17408)%L;
						theta = ((theta*32763)%L + (theta2%L))%L;
						// 303071227-303038464;
						// cout << "lol\n";
						// cout << h << ' ' << m << ' ' << s << ' ' << theta << '\n';
					}
					// if (h*12%L == m && m*60%L == s) fn = true;
				}
			}
		}

		h = (h-theta+L)%L;
		m = (m-theta+L)%L;
		s = (s-theta+L)%L;

		// if (h >= L/2) {
		// 	h -= L/2;
		// 	m = (m+L-L/2)%L;
		// 	s = (s+L-L/2)%L;
		// }
		int hh = h/(30*M);
		int mm = 5*m/(30*M);
		int ss = 5*s/(30*M);

		cout << hh << ' ' << mm << ' ' << ss << ' ' << h-hh*60*60*NN-mm*60*NN-ss*NN << '\n';
		
	}
}

