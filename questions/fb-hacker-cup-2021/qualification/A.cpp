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

string s, ab;
int mdis[26][26];
bool rable[26][26][26];
vector<int> adj[26];
int k;

void calc_rable() {
	for (int k = 0; k < 26; k++) {
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				if (k == 0) {
					rable[i][j][k] = (i==j);
					continue;
				}
				rable[i][j][k] = rable[i][j][k-1];
				for (int u : adj[i]) rable[i][j][k] = rable[i][j][k] || rable[u][j][k-1];
			}
		}
	}
}

int calc_dist(int a, int b) {
	if (a == b) return mdis[a][a] = 0;
	if (mdis[a][b] != -1) return mdis[a][b];

	mdis[a][b] = INT_MAX;
	for (int i = 1; i < 26; i++) {
		if (rable[a][b][i]) {
			mdis[a][b] = i;
			break;
		}
	}
	return mdis[a][b];
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int T; cin >> T;
	
	for (int cn = 1; cn <= T; cn++) {
		cout << "Case #" << cn << ": ";
		cin >> s;
		// cin >> k;

		for (int i = 0; i < 26; i++) adj[i].clear();
		// for (int i = 0; i < k; i++) {
		// 	cin >> ab;
		// 	int u = ab[0]-'A';
		// 	int v = ab[1]-'A';
		// 	adj[u].pb(v);
		// }
		set<char> vow({'A', 'E', 'I', 'O', 'U'});
		vector<int> cons;
		for (int i = 0; i < 26; i++) {
			if (vow.find((char) i+'A') == vow.end()) cons.pb(i);
		}

		for (int i = 0; i < 26; i++) {
			if (vow.find((char) i+'A') == vow.end())
				for (char c : vow) adj[i].pb(c-'A');
			else
				for (int j : cons) adj[i].pb(j);
		}
		calc_rable();

		for (int i = 0; i < 26; i++) for (int j = 0; j < 26; j++) mdis[i][j] = -1;

		int ans = INT_MAX;

		for (int i = 0; i < 26; i++) {
			int temp = 0;
			for (char c: s) {
				int x = calc_dist(c-'A', i);
				if (x == INT_MAX) {
					temp = x;
					break;
				}
				else temp += x;
			}
			ans = min(ans, temp);
		}
		cout << (ans == INT_MAX ? -1 : ans) << '\n';
	}
}

