#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll> 
#define int ll
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int *stree;
int n;

inline int sfunc (int a, int b) {
	return a+b;
}

void build () {
	for (int i = n-1; i > 0; i--) stree[i] = sfunc(stree[i<<1], stree[i<<1|1]);
}

void modify (int ind, int val) {
	for (stree[ind+=n] = val; ind > 0; ind >>= 1) stree[ind>>1] = sfunc(stree[ind], stree[ind^1]);
}

int query (int l, int r) {
	int res = 0;
	for (l+=n, r+=n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = sfunc(res, stree[l++]);
		if (r&1) res = sfunc(res, stree[--r]);
	}
	return res;
}

signed main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int q;
	cin >> n >> q;
	stree = new int[2*n];
	for (int i = 0; i < n; i++) cin >> stree[n+i];
	build();
	while (q--) {
		int a, b, c; cin >> a >> b >> c;
		if (a == 1) modify(b-1, c);
		else cout << query(b-1, c) << '\n';
	}
}

