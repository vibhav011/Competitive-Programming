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

vector<int> freq(10);

int solve(int k, bool fst) {
	if (k == 1) {
		for (int i = 0; i < 10; i++) if (freq[i] > 1) return 0;
		int a = -1, b = -1;
		for (int i = 0; i < 10; i++) {
			if (freq[i]) {
				if (a == -1) a = i;
				else b = i;
			}
		}
		return b-a;
	}
	int ans = 1000000000000000000LL;
	int i = (fst) ? 1 : 0;
	for (; i < 10; i++) {
		if (freq[i] > 1) {
			freq[i] -= 2;
			ans = min(ans, solve(k-1, false));
			freq[i] += 2;
		}
	}
	i = (fst) ? 1 : 0;
	vector<int> freq2 = freq;
	int x = 0, y = 0;
	for (; i < 9; i++) {
		for (int j = i+1; j < 10; j++) {
			if (freq2[i] && freq2[j]) {
				x = j;
				y = i;
				freq2[i]--;
				freq2[j]--;
				int ctr = 0, ind = 0;
				while (ctr < k-1) {
					while (freq2[ind] == 0) ind++;
					x = 10*x + ind;
					freq2[ind]--;
					ctr++;
				}
				ctr = 0; ind = 9;
				while (ctr < k-1) {
					while (freq2[ind] == 0) ind--;
					y = 10*y + ind;
					freq2[ind]--;
					ctr++;
				}
				// cout << "i: " << i << " j: " << j << " dif: " << (x-y) << '\n';
				ans = min(ans, x-y);
				freq2 = freq;
			}
		}
	}
	return ans;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	
	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";
		string d; cin >> d;
		for (int i = 0; i < 10; i++) freq[i] = 0;
		int n = d.size();
		for (int i = 0; i < n; i++) freq[d[i]-'0']++;
		int ev = true;
		for (int i = 0; i < 10; i++) {
			if (freq[i]&1) {
				ev = false;
				break;
			}
		}
		if (ev) {
			cout << "0\n";
			continue;
		}
		int x = 0, y = 0;
		if (n&1) {
			for (int i = 1; i < 10; i++) {
				if (freq[i]) {
					x = i;
					freq[i]--;
					break;
				}
			}
			int ctr = 0, ind = 0;
			while (ctr < n/2) {
				while (freq[ind] == 0) ind++;
				x = 10*x + ind;
				freq[ind]--;
				ctr++;
			}
			ctr = 0; ind = 9;
			while (ctr < n/2) {
				while (freq[ind] == 0) ind--;
				y = 10*y + ind;
				freq[ind]--;
				ctr++;
			}
			cout << x-y << '\n';
			continue;
		}
		cout << solve(n/2, true) << '\n';

	}
}

