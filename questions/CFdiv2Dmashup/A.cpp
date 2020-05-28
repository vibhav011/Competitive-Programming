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

int a[5005][5005], dp[5005][5005], msort[5005];
int n, m;

void mySort(int ar[]) {
	fill(msort, msort+m+1, 0);
	for (int i = 1; i <= n; i++) msort[ar[i]]++;
	
	int ind = 1;
	for (int i = 0; i <= m && ind <= n; i++) {
		while (msort[i]--)
			ar[ind++] = i;
	}
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;

	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		char c; cin >> c;
		a[i][j] = c - '0';
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = m; j > 0; j--) {
			if (j == m && a[i][j]) dp[j][i] = 1;
			else {
				if (a[i][j]) dp[j][i] = 1+dp[j+1][i];
				else dp[j][i] = 0; 
			}
		}
	}
	
	for (int i = 1; i <= m; i++) mySort(dp[i]);

	int ans = 0;
	
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) ans = max(ans, dp[i][j]*(n-j+1));
	}

	cout << ans << endl;
}

