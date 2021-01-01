#include <bits/stdc++.h>
#define ll long long
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 1000000007;

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

const int M = 5e5+5;

int par[M], siz[M];
int n, m;

int cat(int x) {
	int y = x;
	while (x != par[x]) x = par[x];
	return par[y] = x;
}

void connect(int u, int v) {
	int a = cat(u);
	int b = cat(v);
	if (siz[a] < siz[b]) swap(a, b);
	par[b] = a;
	siz[a] += siz[b];
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i <= m; i++) {
		par[i] = i;
		siz[i] = 1;
	}
	vector<int> ans;

	for (int i = 0; i < n; i++) {
		int k, u, v; cin >> k;
		if (k == 1) {
			u = 0; cin >> v;
		}
		else if (k == 2) {
			cin >> u >> v;
		}
		else continue;
		if (cat(u)^cat(v)) {
			connect(u, v);
			ans.pb(i+1);
		}
	}

	int s = ans.size();
	cout << pwr(2, s) << ' ' << s << endl;
	for (int i = 0; i < s; i++) cout << ans[i] << ' ';
	cout << endl;

	return 0;
}

