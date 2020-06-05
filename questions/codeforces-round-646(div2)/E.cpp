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
const int N = 2e5+5;

vector<int> adj[N];
ll wrong[2][N], cost[N], a[N], b[N], c[N];;
bool vis[N];

void dfs(int node) {
	if (vis[node]) return;
	vis[node] = true;
	if (adj[node].size() == 1 && node != 1) {
		if (b[node] != c[node]) wrong[b[node]][node] = 1;
		//else wrong[0][node] = 0;
		cost[node] = 0;
		return;
	}
	for (int i = 0; i < adj[node].size(); i++) {
		if (!vis[adj[node][i]]) a[adj[node][i]] = min(a[adj[node][i]], a[node]);
		dfs(adj[node][i]);
	}
	if (b[node] != c[node]) wrong[b[node]][node] = 1;
	//else wrong[node] = 0;
	ll cst = 0, extra0 = wrong[0][node], extra1 = wrong[1][node];
	for (int i = 0; i < adj[node].size(); i++) {
		wrong[0][node] += wrong[0][adj[node][i]];
		wrong[1][node] += wrong[1][adj[node][i]];
		int minn = min(wrong[0][adj[node][i]], wrong[1][adj[node][i]]);
		if (cost[adj[node][i]] < 2 * minn * a[node]) cst += cost[adj[node][i]];
		else cst += 2*minn * a[node];
		extra0 += wrong[0][adj[node][i]] - minn;
		extra1 += wrong[1][adj[node][i]] - minn;
	}
	cost[node] = cst + 2*min(extra0, extra1) * a[node];

}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	int zo[2]; zo[0] = zo[1] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i];
		if (b[i] != c[i]) zo[b[i]]++;
	}
	for (int i = 0; i < n-1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	if (zo[0] != zo[1]) {
		cout << "-1\n";
		return 0;
	}
	memset(wrong, 0, sizeof(wrong));
	//fill(wrong, wrong+N, -1);
	fill(vis, vis+N, false);
	dfs(1);
	
	cout << cost[1] << endl;
	//sort(aa.begin(), aa.end());

}

