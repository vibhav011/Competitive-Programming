// Wrong

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
	ll n, a, r, m, sum;
	cin >> n >> a >> r >> m;
	m = min(m, a+r);
	ll h[n];
	for (int i = 0; i < n; i++) {
		cin >> h[i];
		sum += h[i];
	}

	ll low = (sum/n)*n;

	ll ans1 = 0;
	ans1 += a*(low+n-sum);
	ll dif = low+n-sum;
	for (int i = 0; i < n; i++) {
		if (dif == 0) break;
		if (h[i] < low+n) {
			ll ad = min(low+n-h[i], dif);
			h[i] += ad;
			dif -= ad;
		}
	}
	for (int i = 0; i < n; i++) {
		if (h[i] < low+n) ans1 += m*(low+n-h[i]);
	}
	ll ans2 = 0;
	ans2 += r*(sum-low);
	dif = sum-low;
	for (int i = 0; i < n; i++) {
		if (dif == 0) break;
		if (h[i] > low) {
			ll sub = min(h[i]-low, dif);
			h[i] -= sub;
			dif -= sub;
		}
	}
	for (int i = 0; i < n; i++) {
		if (h[i] < low) ans2 += m*(low-h[i]);
	}
	cout << min(ans1, ans2) << endl;
}