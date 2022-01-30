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

int n, k, q;									// array size

int a[600000];
string s;

int sfunc(int a, int b, int r) {
	if (s[n-1-r] == '0') return b;
	if (s[n-1-r] == '1') return a;
	return a+b;
}

void build() {							// build the tree
	for (int i = n - 1; i > 0; --i) a[i] = sfunc(a[i<<1], a[i<<1|1], i);
}

void modify(int p, char c) {			// set value at position p
	s[p] = c;
	for (p = n-1-p; p >= 1; p >>= 1) a[p] = sfunc(a[p<<1], a[p<<1|1], p);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> k;
	n = 1 << k;
	cin >> s;
	cin >> q;
	for (int i = n; i < 2*n; i++) a[i] = 1;
	build();
	while (q--) {
		int p; char c;
		cin >> p >> c;
		p--;
		modify(p, c);
		cout << a[1] << '\n';
	}
}

