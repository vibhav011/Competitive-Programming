#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 1e9+7;

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
string s;
bool vis[7][7];
int ans, x, y;
map<char, pii> dir;
int v[7][7];

bool check(int x, int y) {
	if (x < 0 || x > 6 || y < 0 || y > 6) return false;
	if (vis[x][y]) return false;
	return true;
}

void bfs (int x, int y) {
	v[x][y] = 1;
	if (check(x+1, y) && !v[x+1][y]) bfs(x+1, y);
	if (check(x-1, y) && !v[x-1][y]) bfs(x-1, y);
	if (check(x, y+1) && !v[x][y+1]) bfs(x, y+1);
	if (check(x, y-1) && !v[x][y-1]) bfs(x, y-1);
}

bool reachable(int x, int y) {
	if (vis[6][0]) return false;
	memset(v, 0, sizeof(v));
	bfs(6, 0);
	if (v[x][y]) return true;
	return false;
}

void calc(int ind) {
	if (ind == 48) {
		ans++;
		return;
	}
	// if (s[ind] != '?') {
	// 	pii p = dir[s[ind]];
	// 	if (check(x+p.ff, y+p.ss)) {
	// 		if (ind < 47 && x+p.ff == 7 && y+p.ss == 0) return;
	// 		x += p.ff;
	// 		y += p.ss;
	// 		vis[x][y] = true;
	// 		calc(ind+1);
	// 	}
	// 	return;
	// }
	string d (1, s[ind]);
	if (s[ind] == '?') d = "DULR";
	for (int i = 0; i < d.size(); i++) {
		pii p = dir[d[i]];
		if (check(x+p.ff, y+p.ss)) {
			if (!reachable(x+p.ff, y+p.ss)) return;
			int x2 = x, y2 = y;
			x += p.ff;
			y += p.ss;
			vis[x][y] = true;
			calc(ind+1);
			x = x2;
			y = y2;
			vis[x+p.ff][y+p.ss] = false;
		}
	}
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> s;
	memset(vis, false, sizeof(vis));
	vis[0][0] = true;
	ans = 0;
	dir['D'] = mp(1, 0); dir['U'] = mp(-1, 0);
	dir['R'] = mp(0, 1); dir['L'] = mp(0, -1);
	calc(0);
	cout << ans << endl;
}

