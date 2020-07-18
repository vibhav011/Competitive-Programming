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
bool check(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}
int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	m = 0;
	cin >> n;
	vector<pii> pts[26];
	int ans[26];
	fill(ans, ans+26, 30);

	int ar[n+2][1001];

	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		if (!m) m = s.size();
		for (int j = 0; j < m; j++) {
			pts[s[j]-'a'].pb(mp(i, j+1));
			ar[i][j+1] = s[j]-'a';
		}
	}
	//for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans[i][j] = -1;
	queue<int> q;
	//for (int i = 0; i < pts[c].size(); i++) q.push(pts[i]);
	q.push(ar[1][1]);
	int cur = 0;
	ans[ar[1][1]] = 0;
	
	while (!q.empty()) {
		int c = q.front(); 
		q.pop(); 
		//ans[c] = min(ans[c], cur);
		//cur++;
		for (int i = 0; i < pts[c].size(); i++) {
			int x = pts[c][i].ff;
			int y = pts[c][i].ss;
			if (check(x+1, y) && ans[ar[x+1][y]] == 30) {
				q.push(ar[x+1][y]);
				ans[ar[x+1][y]] = ans[ar[x][y]]+1;
			}
			if (check(x-1, y) && ans[ar[x-1][y]] == 30) {
				q.push(ar[x-1][y]);
				ans[ar[x-1][y]] = ans[ar[x][y]]+1;
			}
			if (check(x, y+1) && ans[ar[x][y+1]] == 30) {
				q.push(ar[x][y+1]);
				ans[ar[x][y+1]] = ans[ar[x][y]]+1;
			}
			if (check(x, y-1) && ans[ar[x][y-1]] == 30) {
				q.push(ar[x][y-1]);
				ans[ar[x][y-1]] = ans[ar[x][y]]+1;
			}
		}
	}
	// for (int i = 0 ; i < 26; i++) cout << ans[i] << ' ';
	// cout << endl;
	cout << ans[ar[n][m]] << endl;
}

