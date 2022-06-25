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
	return max(a,b);
}

inline int sfunc2(int a, int b) {
	return min(a,b);
}

int n;									// array size
int *stree, *stree2;								// stree = new int[2 * n]

void build() {							// build the tree
	for (int i = n - 1; i > 0; --i) stree[i] = sfunc(stree[i<<1], stree[i<<1|1]);
}
void build2() {							// build the tree
	for (int i = n - 1; i > 0; --i) stree2[i] = sfunc2(stree2[i<<1], stree2[i<<1|1]);
}

void modify(int p, int value) {			// set value at position p
	for (stree[p += n] = value; p > 1; p >>= 1) stree[p>>1] = sfunc(stree[p], stree[p^1]);
}

void modify2(int p, int value) {			// set value at position p
	for (stree2[p += n] = value; p > 1; p >>= 1) stree2[p>>1] = sfunc2(stree2[p], stree2[p^1]);
}

int query(int l, int r) {				// query on interval [l, r)
	int res = 0;						// DEFAULT
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc(res, stree[l++]);
		if (r&1) res = sfunc(res, stree[--r]);
	}
	return res;
}

int query2(int l, int r) {				// query on interval [l, r)
	int res = 1LL << 40;						// DEFAULT
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc2(res, stree2[l++]);
		if (r&1) res = sfunc2(res, stree2[--r]);
	}
	return res;
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;
    stree = new int[500005];
    stree2 = new int[500005];
	
	while (t--) {
        cin >> n;
        vector<int> a(n), rev(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            stree[n+i] = a[i];
            stree2[n+i] = a[i];
            rev[a[i]-1] = i;
        }
        build(); build2();
        vector<int> dp(n);
        stack<pii> s;
        s.push(mp(a[0], 0));
        vector<int> chhota(n, n), bada(n, n);
        for (int i = 1; i < n; i++) {
            if (s.empty()) {
                s.push(mp(a[i], i));
                continue;
            }
            pii cur = s.top();
            while (cur.ff > a[i]) {
                chhota[cur.ss] = i;
                s.pop();
                if (s.empty()) break;
                cur = s.top();
            }
            s.push(mp(a[i], i));
        }

        while (!s.empty()) s.pop();
        s.push(mp(a[0], 0));
        for (int i = 1; i < n; i++) {
            if (s.empty()) {
                s.push(mp(a[i], i));
                continue;
            }
            pii cur = s.top();
            while (cur.ff < a[i]) {
                bada[cur.ss] = i;
                s.pop();
                if (s.empty()) break;
                cur = s.top();
            }
            s.push(mp(a[i], i));
        }

        for (int i = n-2; i>= 0; i--) {
            // cout << "Iter " << i << endl;
            if (a[i+1] > a[i]) {
                int j = chhota[i];
                int mx = query(i, j);
                // cout << mx << endl;
                dp[i] = 1 + dp[rev[mx-1]];
            } else {
                int j = bada[i];
                int mn = query2(i, j);
                // cout << mn << endl;
                dp[i] = 1 + dp[rev[mn-1]];
            }
        }

        cout << dp[0] << '\n';
    }

    delete[] stree;
    delete[] stree2;
}

