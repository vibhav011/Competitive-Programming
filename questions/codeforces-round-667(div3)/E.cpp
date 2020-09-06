#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y) {
	ll res = 1;
	x = x%MOD;
	while (y > 0) {
		if (y&1) res = (res*x)%MOD;

		y = y>>1;
		x = (x*x)%MOD;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

class BIT {
	int *bit;
	int N;

public:
	void update(int x, int val) {
		int ind = x;
		while (ind <= N) {
			bit[ind] += val;
			ind += (ind & (-ind));
		}
	}

	BIT(int ar[], int n) {
		bit = new int[n+1];
		N = n+1;
		for (int i = 1; i < N; i++) bit[i] = 0;
		for (int i = 1; i < N; i++) update(i, ar[i-1]);
	}

	int getSum(int x) {
		if (x < 0) return 0;

		int ind = x+1;
		int sum = 0;
		while (ind > 0) {
			sum += bit[ind];
			ind = (ind & (ind-1));
		}
		return sum;
	}

	int getValue(int x) {
		return getSum(x) - getSum(x-1);
	}

	void changeElem(int x, int val) {
		update(x+1, val-getValue(x));
	}
};

int bsh(int val, int ar[], int n) {		// return ind such that val >= ar[ind] and val < ar[ind+1]
	int a = 0, b = n - 1, c = (a+b)/2;
	if (val < ar[0]) return -1;
	if (val >= ar[b]) return b;

	while (!(val >= ar[c] && val < ar[c+1])) {
		if (val < ar[c]) b = c;
		else {
			if (b-a == 1 && c == a) a = b;
			else a = c;
		}
		c = (a+b)/2;
	}
	return c;
}

int s;

ll ans(ll n) {
	ll n2 = n;
	ll d = 10;
	ll dsum = 0;
	while (n2 > 9) {
		dsum += n2%10;
		n2 /= 10LL;
		d *= 10LL;
	}
	dsum += n2;
	if (dsum <= s) return 0;
	if (n2 > s) return d - n;
	if (n2 == s) {
		return d-n + ans(d);
	}
	s -= n2;
	return ans(n - n2*d/10);
}

const int N = 2e5+5;
int n, k;

int t[2 * N];

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}

int t2[2 * N];

void build2() {  // build the tree
  for (int i = n - 1; i > 0; --i) t2[i] = max(t2[i<<1], t2[i<<1|1]);
}

int query2(int l, int r) {  // max on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t2[l++]);
    if (r&1) res = max(res, t2[--r]);
  }
  return res;
}


int x[N];
// int freq[N];

void func() {
	// int mx = 0, st, en;
	vector<pii> prs(n);
	for (int i = 0; i < n; i++) {
		int a = x[i];
		int b = a+k;
		
		int lo = i+1, hi = n, m = (hi+lo)/2;
		int pos = i;
		while (lo < hi) {
			if (x[m] == b) break;
			if (x[m] > b) hi = m;
			else {
				pos = m;
				lo = m+1;
			}
			m = (hi+lo)/2;
		}
		if (m == n) m--;
		else if (x[m] > b) m = pos;
		int sm = query(i, m+1);
		
		t2[n+i] = sm;
		prs[i].ff = sm;
		prs[i].ss = m;
	}
	build2();
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int an = prs[i].ff;
		an += query2(prs[i].ss+1, n);
		ans = max(ans, an);
	}
	cout << ans << endl;
}


int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int T; cin >> T;
	while (T--) {
		cin >> n >> k;
		map<int, int> fr;
		int xx;
		for (int i = 0; i < n; i++) {
			cin >> xx;
			fr[xx]++;
		}
		int yyy;
		for (int i = 0; i < n; i++) cin >> yyy;
		n = fr.size();
		int ind = 0;
		for (pii p : fr) {
			x[ind] = p.ff;
			t[n+ind] = p.ss;
			ind++;
		}
		build();

		func();

	}
}

