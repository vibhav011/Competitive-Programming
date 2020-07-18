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
	ios_base::sync_with_stdio(0); cin.tie(0);

	ll n, x, y;
	cin >> n >> x >> y;
	if (n < x+y-1 || n > x*y) {
		cout << "-1\n";
		return 0;
	}
	vector<vector<int> > ans(1, vector<int>());
	for (int i = 1; i <= x; i++) ans[0].pb(i);
	if (x < n) {
		int sz = (n-x)/(y-1);
		int rem = (n-x)%(y-1);
		int cur = x+1;
		for (int i = 1; i < y; i++) {
			vector<int> tmp;
			int ex = (rem) ? 1 : 0;
			for (int i = cur; i <= cur+sz+ex-1; i++) {
				tmp.pb(i);
			}
			rem -= ex;
			cur += sz+ex;
			ans.pb(tmp);
		}
	}
	for (int i = ans.size()-1; i >= 0; i--) {
		for (int j = 0; j < ans[i].size(); j++) cout << ans[i][j] << ' ';
	}
	cout << endl;
}
