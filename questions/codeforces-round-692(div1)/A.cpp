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

int num_cycles(int u, vector<int> &adj, vector<bool> &vis) {
	if (vis[u] || adj[u] == -1) return 0;
	vis[u] = true;
	if (vis[adj[u]]) return 1;
	return num_cycles(adj[u], adj, vis);
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;
		vector<pii> pts;
		for (int i = 0; i < m; i++) {
			int x, y;
			cin >> x >> y;
			if (x != y)
				pts.pb(mp(x, y));
		}
		m = pts.size();

		if (m == 0) {
			cout << "0\n";
			continue;
		}
		sort(pts.begin(), pts.end());
		vector<int> adj(m, -1), inc(m, -1);
		for (int i = 0; i < m; i++) {
			int ind = lower_bound(pts.begin(), pts.end(), mp(pts[i].ss, 0)) - pts.begin();
			if (ind != m) {
				if (pts[ind].ff == pts[i].ss) {
					adj[i] = ind;
					inc[ind] = i;
				}
			}
		}
		// for (int i = 0; i < m; i++) cout << adj[i] << ' ';
		// cout << endl;
		int cyc = 0;
		vector<bool> vis(m, false);
		for (int i = 0; i < m; i++) {
			if (inc[i] == -1)
				cyc += num_cycles(i, adj, vis);
		}
		for (int i = 0; i < m; i++) {
			if (!vis[i])
				cyc += num_cycles(i, adj, vis);
		}
		cout << m + cyc << endl;
	}
	
}

