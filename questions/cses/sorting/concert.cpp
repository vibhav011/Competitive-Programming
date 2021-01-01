#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int n;									// array size
pii *stree;								// stree = new int[2 * n]

pii sfunc (pii &a, pii &b) {
	if (a.ff <= b.ff) return b;
	return a;
}

void build() {							// build the tree
	for (int i = n - 1; i > 0; --i) stree[i] = sfunc(stree[i<<1], stree[i<<1|1]);
}

void modify(int p, pii value) {			// set value at position p
	for (stree[p += n] = value; p > 1; p >>= 1) stree[p>>1] = sfunc(stree[p], stree[p^1]);
}

pii query(int l, int r) {				// query on interval [l, r)
	pii res = mp(-1, -1);						// DEFAULT
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc(res, stree[l++]);
		if (r&1) res = sfunc(res, stree[--r]);
	}
	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int m; cin >> n >> m;
	vector<int> h(n);
	for (int i = 0; i < n; i++) cin >> h[i];
	sort(h.begin(), h.end());
	stree = new pii[2*n];
	for (int i = 0; i < n; i++) {
		stree[i+n] = mp(h[i], i);
	}
	build();
	while (m--) {
		int x; cin >> x;
		int ind = upper_bound(h.begin(), h.end(), x) - h.begin();
		
		pii res = query(0, ind);
		cout << res.ff << '\n';
		modify(res.ss, mp(-1, -1));
	}
}

