#include <bits/stdc++.h>
#include <unordered_set>
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

int lg(int k) {
	int ans = -1;
	while (k) {
		ans++;
		k >>= 1;
	}
	return ans;
}

bool next_str(string &cur) {
	bool ret = false;
	for (int i = cur.size()-1; i >= 0; i--) {
		if (cur[i] == '0') {
			cur[i] = '1';
			ret = true;
			break;
		}
		cur[i] = '0';
	}
	return ret;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
	
	while (t--) {
		int n, k;
		cin >> n >> k;
		string s; cin >> s;
		int x = min(20LL, k);
		int rest = k-x;
		unordered_set<string> banned;

		int num1 = 0;
		for (int i = 0; i < rest; i++)
			if (s[i] == '1') num1++;

		for (int i = rest; i < n-x+1; i++) {
			if (i > rest) num1 += s[i-1] - s[i-rest-1];
			if (num1 == rest) {
				string ss = "";
				for (int j = i; j < i+x; j++) {
					ss += (char) ('0'+'1'-s[j]);
				}
				banned.insert(ss);
			}
		}
		if (banned.size() < (1 << x)) {
			cout << "YES\n";
			string prev(rest, '0');
			string cur(x, '0');
			while (banned.find(cur) != banned.end()) next_str(cur);
			cout << prev + cur << '\n';
		} else cout << "NO\n";
	}
}
