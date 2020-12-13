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

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;

		string ar[n+2];
		for (int i = 0; i < n; i++) {
			cin >> ar[i+1];
			ar[i+1] = "#" + ar[i+1];
		}
		ll ans = 0;
		ll dp[n+2][m+2];
		for (int i = 0; i < n+2; i++) {
			dp[i][0] = 0;
			dp[i][m+1] = 0;
		}
		for (int i = 0; i < m+2; i++) {
			dp[0][i] = 0;
			dp[n+1][i] = 0;
		}
		// for (int i = 0; i < m; i++) {
		// 	dp[n-1][i] = 0;
		// 	if (ar[n-1][i] == '*') dp[n-1][i] = 1;
		// 	ans += dp[n-1][i];
		// }
		for (int i = n; i > 0; i--) {
			for (int j = 1; j <= m; j++) {
				if (ar[i][j] == '.') dp[i][j] = 0;
				else {
					dp[i][j] = 1 + min(dp[i+1][j], min(dp[i+1][j-1], dp[i+1][j+1]));
				}
				ans += dp[i][j];
			}
		}
		cout << ans << endl;
	}
	
}

