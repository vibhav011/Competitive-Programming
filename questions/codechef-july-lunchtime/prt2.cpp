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

const int M = 3e5+5;
vector<int> adj[M];
int n, mn, vis[M];

void dfs(int root, int dist) {
	vis[root] = 1;
	bool go = false;
	for (int i = 0; i < adj[root].size(); i++) {
		if (!vis[adj[root][i]]) {dfs(adj[root][i], dist+1); go = true;}
	}
	if (!go) mn = min(mn, dist);
}

int main () {
	// incorrect
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		ll k;
		cin >> n >> k;
		ll a[n];
		for (int i = 1; i <= n; i++) {adj[i].clear(); vis[i] = 0;}
		for (int i = 0; i < n; i++) cin >> a[i];
		sort(a, a+n, greater<int>());
		for (int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].pb(v);
			adj[v].pb(u);
		}
		// pii dis[n+1];
		// fill(dis, dis+n+1, mp(0, -1));
		// vector<int> cur;
		// for (int i = 1; i <= n; i++) {
		// 	if (adj[i].size() == 1) {
		// 		dis[i].ss = cur.size();
		// 		cur.pb(i);
		// 	}
		// }
		// bool col = false;
		// int minPath;
		// int val = 1;
		// while (!col) {
		// 	for (int i = 0; i < cur.size(); i++) {
		// 		int l = cur[i];
		// 		if (dis[l].ss != )

		// 	}
		// }
		mn = n+1;
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() == 1) {
				dfs(i, 1);
				fill(vis, vis+n+1, 0);
			}
		}
		ll sum = 0, sum2 = 0;
		ll rem = k%(2*mn);
		ll ans = 0;
		for (int i = 0; i < rem/2; i++) ans += 2*a[i];
		if (k&1) ans += a[rem/2+1];
		for (int i = 0; i < mn; i++) sum += a[i];
		// for (int i = 0; i < k%mn; i++) sum2 += a[i];
		cout << 2*(k/(2*mn))*sum + ans << endl;
	}
}

