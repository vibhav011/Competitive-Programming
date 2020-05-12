#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second

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

int dp[100005];
int s[100005];
int n;

int ans (int ind) {
	if (dp[ind] != -1) return dp[ind];

	int mx = 0;

	for (int i = 2; ind * i <= n; i++) {
		if (s[ind*i] > s[ind]) mx = max(mx, ans(ind * i));
	}

	dp[ind] = 1+mx;
	return dp[ind];
}

int main () {
	int t; cin >> t;

	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> s[i];

		fill(dp, dp+100005, -1);

		int mx = 1;

		for (int i = 1; i <= n; i++) {
			mx = max(mx, ans(i));
		}

		cout << mx << endl;

	}
}