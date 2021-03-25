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
	return min(a, b);
}
inline int sfunc2(int a, int b) {
	return max(a, b);
}

int n;									// array size
int *stree, *stree2;								// stree = new int[2 * n]

void build() {							// build the tree
	for (int i = n - 1; i > 0; --i) stree[i] = sfunc(stree[i<<1], stree[i<<1|1]);
}

int query(int l, int r) {				// query on interval [l, r)
	int res = n+1;						// DEFAULT
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc(res, stree[l++]);
		if (r&1) res = sfunc(res, stree[--r]);
	}
	return res;
}

void build2() {							// build the tree
	for (int i = n - 1; i > 0; --i) stree2[i] = sfunc2(stree2[i<<1], stree2[i<<1|1]);
}

int query2(int l, int r) {				// query on interval [l, r)
	int res = -n-1;						// DEFAULT
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc2(res, stree2[l++]);
		if (r&1) res = sfunc2(res, stree2[--r]);
	}
	return res;
}

int gcd (int a, int b) {
	if (a > b) swap(a, b);
	if (b%a == 0) return a;
	return gcd(b%a, a);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	
	while (t--) {
		int m;
		cin >> n >> m;
		string s;
		cin >> s;
		stree = new int[2*n];
		stree2 = new int[2*n];
		stree[n-1] = 0;
		for (int i = 0 ; i < n; i++) {
			if (s[i] == '+') stree[n+i] = stree[n+i-1] + 1;
			else stree[n+i] = stree[n+i-1] - 1;
			stree2[n+i] = stree[n+i];
		}
		build(); build2();

		int a1, a2, a3, b1, b2, b3;

		while (m--) {
			int l, r;
			cin >> l >> r;
			l--; r--;
			if (l == 0 && r == n-1) {
				cout << "1\n";
				continue;
			}
			a1 = query(0, l);a3 = query(r+1, n);
			b1 = query2(0, l);b3 = query2(r+1, n);
			if (r == n-1) {
				cout << max(0LL, b1-a1+1) + ((a1 <= 0 && b1 >= 0) ? 0LL : 1LL) << '\n';
				continue;
			}
			if (l == 0) {
				a3 -= stree[n+r];
				b3 -= stree[n+r];
			}
			else {
				a3 -= stree[n+r]-stree[n+l-1];
				b3 -= stree[n+r]-stree[n+l-1];
			}
			int ans = 0;
			bool z = false;


			if (b1 < a3 || b3 < a1) {
				if (b1 >= a1) {
					ans += b1-a1+1;
					if (a1 <= 0 && b1 >= 0) z = true;
				}
				if (b3 >= a3) {
					ans += b3-a3+1;
					if (a3 <= 0 && b3 >= 0) z = true;
				}
			}
			else {
				a2 = min(a1, a3);
				b2 = max(b1, b3);
				if (b2 >= a2) {
					ans += b2-a2+1;
					if (a2 <= 0 && b2 >= 0) z = true;
				}
			}
			if (!z) ans++;
			cout << ans << '\n';
		}
		delete[] stree;
		delete[] stree2;
	}
}

