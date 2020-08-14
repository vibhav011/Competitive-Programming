#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define mll map<ll, ll> 

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

const int M = 1e6+5;
const ll inf = 1e15;
ll t[2*M];
int n;

void build() {
	for (int i = n-1; i > 0; i--)
		t[i] = min(t[i<<1], t[i<<1|1]);
}
void modify(int p, ll value) {
	p += n;
	t[p] = min(inf, value+t[p]);
	for (; p > 1; p >>= 1)
		t[p>>1] = min(t[p], t[p^1]);
}
ll query(int l, int r) {
	ll res = inf;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = min(res, t[l++]);
		if (r&1) res = min(res, t[--r]);
	}
	return res;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int T; cin >> T;
	for (int cn = 1; cn <= T; cn++) {
		printf("Case #%d: ", cn);
		int m; cin >> n >> m;
		ll c[n];
		for (int i = 0; i < n; i++) {
			cin >> t[n+i];
			if (!t[n+i]) t[n+i] = inf;
			c[i] = t[n+i];
		}
		build();
		if (m >= n-1) {
			cout << "0\n";
			continue;
		}
		for (int i = m+1; i < n; i++) {
			modify(i, query(i-m, i));
		}
		if (t[2*n-1] == inf) cout << "-1\n";
		else cout << t[2*n-1] - c[n-1] << endl;
	}
}

