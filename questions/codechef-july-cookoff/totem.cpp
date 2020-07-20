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

int bsh(pll ar[], ll n, ll val) {		// return ind such that val >= ar[ind] and val < ar[ind+1]
	ll a = 1, b = n - 1, c = (a+b)/2;
	if (val >= ar[0].ff) return 0;
	// if (val >= ar[b]) return b;

	while (!(val >= ar[c].ff && val < ar[c-1].ff)) {
		if (val < ar[c].ff) {
			if (b-a == 1 && c == a) a = b;
			else a = c;
		}
		else {
			b=c;
		}
		c = (a+b)/2;
	}
	return c;
}


const ll num = 5342931457063200;
const ll ar[13] = {41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
vector<int> adj[101];
ll ans[101];
int cnt;
bool vis[101];

void dfs(int root, int ind) {
	vis[root] = true;
	ans[root] = num*ar[ind];
	for (int i = 0; i < adj[root].size(); i++) {
		if (vis[adj[root][i]]) continue;
		dfs(adj[root][i], (ind+1)%13);
	}
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		int x = max(n, m);
		int y = min(n, m);
		int ar[x][y];
		int d = x+5;
		if (x == y) {
			for (int i = 0; i < x; i++) ar[i][x-1] = d;
			y--;
		}

		for (int j = 0; j < y; j++) {
			for (int i = 0; i < x; i++) {
				if (x-i <= y+j+1) ar[i][j] = (y+j+1-x+i)%x;
				else ar[i][j] = d;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cout << ((n >= m) ? ar[i][j] : ar[j][i]) << ' ';
			cout << endl;
		}
	}
}

