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

int main () {
	ll a, b, c, d;
	cin >> a >> b >> c >> d;
	ll ans = 0;
	for (ll x = b; x >= a; x--) {
		ll y1 = max(c+1-x, b);
		if (y1 > c) break;
		ll start = min(x + y1 - c, d-c+1);
		//c - y1 + 1;
		if (start + c - y1 > d-c+1) {
			ans += (d-c+1 + start)*(d-c - start + 2)/2 + (d-c+1)*(2*c-y1-d-1 +start); 
		}
		else {
			ans += (start*(c - y1 + 1) + (c-y1)*(c - y1 + 1)/2);
		}
	}
	cout << ans << endl;
}