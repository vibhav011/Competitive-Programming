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

const int M = 1e5+5;
int n;
vector<int> adj[M];
vector<int> cen;
int sz[M];
int c1, c2;

void dfs (int u, int prev) {
	sz[u] = 1;
	bool is_centroid = true;
	for (auto v : adj[u]) if (v != prev) {
			dfs(v, u);
			sz[u] += sz[v];
			if (sz[v] > n / 2) is_centroid = false;
	}
	if (n - sz[u] > n / 2) is_centroid = false;
	if (is_centroid) cen.push_back(u);
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		cin >> n;

		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			sz[i] = 0;
		}
		for (int i = 0; i < n-1; i++) {
			int u, v;
			cin >> u >> v;
			adj[u].pb(v);
			adj[v].pb(u);
		}
		cen.clear();
		dfs(1, 0);
		
		if (cen.size() == 1) {
			cout << "1 " << adj[1][0] << endl;
			cout << "1 " << adj[1][0] << endl;
			continue;
		}

		c1 = cen[0];
		c2 = cen[1];

		for (int i = 1; i <= n; i++) {
			sz[i] = 0;
		}

		dfs(c1, c2);

		int ind = 0, mx = 0;

		for (int i = 1; i <= n ; i++) {
			if (sz[i] > mx && i != c1) {
				mx = sz[i];
				ind = i;
			}
		}
		if (mx + n-sz[c1] > n/2) {
			cout << c1 << ' ' << ind << endl;
			cout << c2 << ' ' << ind << endl;
			continue;
		}

		for (int i = 1; i <= n; i++) {
			sz[i] = 0;
		}

		swap(c1, c2);
		dfs(c1, c2);

		ind = 0, mx = 0;

		for (int i = 1; i <= n ; i++) {
			if (sz[i] > mx && i != c1) {
				mx = sz[i];
				ind = i;
			}
		}
		cout << c1 << ' ' << ind << endl;
		cout << c2 << ' ' << ind << endl;

	}
}

