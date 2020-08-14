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

ll max(ll* ar, int n) {
	ll ans = ar[0];
	for (int i = 1; i < n; i++) ans = max(ans, ar[i]);
	return ans;
}

ll dp[201][201][201];
int r, g, b;
ll ar[201], ag[201], ab[201];
ll ans(int a, int b, int c) {
	// a = max(a, 0), b = max(b, 0), c = max(c, 0);
	if (dp[a][b][c] != -1) return dp[a][b][c];
	if ((a == 0 && b == 0) || (a == 0 && c == 0) || (c == 0 && b == 0)) {
		dp[a][b][c] = 0;
		return dp[a][b][c];
	}
	if (a == 0) {
		ll ara[3] = {ans(a, b-1, c), ans(a, b, c-1), ans(a, b-1, c-1)+ab[c]*ag[b]};
		dp[a][b][c] = max(ara, 3);
		return dp[a][b][c];
	}
	else if (b == 0) {
		ll ara[3] = {ans(a-1, b, c), ans(a, b, c-1), ans(a-1, b, c-1)+ar[a]*ab[c]};
		dp[a][b][c] = max(ara, 3);
		return dp[a][b][c];
	}
	else if (c == 0) {
		ll ara[3] = {ans(a, b-1, c), ans(a-1, b, c), ans(a-1, b-1, c)+ar[a]*ag[b]};
		dp[a][b][c] = max(ara, 3);
		return dp[a][b][c];
	}
	ll ara[6] = {ans(a-1, b, c), ans(a, b-1, c), ans(a, b, c-1), ans(a-1, b-1, c)+ar[a]*ag[b], ans(a, b-1, c-1)+ab[c]*ag[b], ans(a-1, b, c-1)+ar[a]*ab[c]};
	dp[a][b][c] = max(ara, 6);
	return dp[a][b][c];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> r >> g >> b;

	for (int i = 1; i <= r; i++) cin >> ar[i];
	for (int i = 1; i <= g; i++) cin >> ag[i];
	for (int i = 1; i <= b; i++) cin >> ab[i];
	sort(ar+1, ar+r+1, greater<int>());
	sort(ag+1, ag+g+1, greater<int>());
	sort(ab+1, ab+b+1, greater<int>());

	dp[1][1][1] = max(ar[1]*ag[1], max(ar[1]*ab[1], ab[1]*ag[1]));
	for (int i = r; i>= 0; i--) {
		for (int j = g; j>= 0; j--) {
			for (int k = b; k>= 0; k--) {
				dp[i][j][k] = -1;
				// if (i == 0 || j == 0 || k == 0) dp[i][j][k] = 0;
			}
		}
	}

	dp[1][1][0] = ar[1]*ag[1];
	dp[1][0][1] = ar[1]*ab[1];
	dp[0][1][1] = ab[1]*ag[1];

	// for (int i = 1; i <= r; i++)
	// 	for (int j = 1; j <= g; j++)
	// 		dp[i][j][0] = ar[1]*ag[1];
	// for (int i = 1; i <= r; i++)
	// 	for (int j = 1; j <= b; j++)
	// 		dp[i][0][j] = ar[1]*ab[1];
	// for (int i = 1; i <= b; i++)
	// 	for (int j = 1; j <= g; j++)
	// 		dp[0][j][i] = ab[1]*ag[1];
	cout << ans(r, g, b) << endl;
}

