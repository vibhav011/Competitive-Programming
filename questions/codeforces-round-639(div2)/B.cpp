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

int bsh(int n) {
	ll a = 1, b = sqrt(n), c = (a+b)/2;

	while (!(c*(3*c+1)/2 <= n && (c+1)*(3*c+4)/2 > n)) {
		if (c*(3*c+1)/2 > n) b = c;
		else {
			if (a == c && b-a == 1) a = c+1;
			else a = c;
		}
		c = (a+b)/2;
	}
	return c;
}

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;

		int ans = 0;
		while (n >= 2) {
			int h = bsh(n);
			//cout << h << ' ';
			n -= h*(3*h+1)/2;
			ans++;
		}
		//cout << endl;
		cout << ans << endl;
	}
}