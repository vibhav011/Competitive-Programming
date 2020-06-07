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

int n, m;
int gr[50][50];

void bfs(int a, int b) {
	if (a < 0 || b < 0 || a > n-1 || b > m-1) return;
	if (gr[a][b] == 1 || gr[a][b] == -1) return;
	gr[a][b] = 1;
	bfs(a-1, b);
	bfs(a+1, b);
	bfs(a, b-1);
	bfs(a, b+1);
	return;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	
	while (t--) {
		cin >> n >> m;
		bool imp = false;
		memset(gr, 0, sizeof(gr));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				char c; cin >> c;
				if (c == '#') gr[i][j] = -1;
				else if (c == 'G') {
					if (gr[i][j] == -1) imp = true;
					gr[i][j] = 2;
				}
				else if (c == 'B') {
					gr[i][j] = -1;
					if (gr[max(0, i-1)][j] == 2) {
						imp = true;
					}
					if (gr[min(n-1, i+1)][j] == 2) {
						imp = true;
					}
					if (gr[i][max(0, j-1)] == 2) {
						imp = true;
					}
					if (gr[i][min(m-1, j+1)] == 2) {
						imp = true;
					}
					gr[max(0, i-1)][j] = -1;
					gr[min(n-1, i+1)][j] = -1;
					gr[i][max(0, j-1)] = -1;
					gr[i][min(m-1, j+1)] = -1;
				}
			}
		}
		if (imp) {
			cout << "No\n";
			continue;
		}
		// for (int i = 0; i < n; i++) {
		// 	for (int j = 0; j < m; j++) {
		// 		cout << gr[i][j] << ' ';
		// 	}
		// 	cout << endl;
		// }
		if (gr[n-1][m-1] == 0) bfs(n-1, m-1);
		bool pos = true;
		for (int i = 0; i < n && pos; i++) for (int j = 0; j < m; j++) {
			if (gr[i][j] == 2) {
				pos = false;
				break;
			}
		}
		if (pos) cout << "Yes\n";
		else cout << "No\n";
	}
}

