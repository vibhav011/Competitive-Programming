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

const ll MAX = 1e4;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int pow1[MAX], pow2[MAX], pow4[MAX], pow8[MAX];
	for (int i = 1; i < MAX; i += 2) {
		pow1[(i-1)/2] = i % MOD;
		pow2[(i-1)/2] = pwr(pow1[(i-1)/2], 2);
		pow4[(i-1)/2] = pwr(pow2[(i-1)/2], 2);
		pow8[(i-1)/2] = pwr(pow4[(i-1)/2], 2);
	}
	for (int i = 3; i < MAX; i += 2) {
		pow1[(i-1)/2] += pow1[(i-1)/2 - 1];
		pow2[(i-1)/2] += pow2[(i-1)/2 - 1];
		pow4[(i-1)/2] += pow4[(i-1)/2 - 1];
		pow8[(i-1)/2] += pow8[(i-1)/2 - 1];
		pow1[i/2] %= MOD; pow2[i/2] %= MOD; pow4[i/2] %= MOD; pow8[i/2] %= MOD;
	}

	int t; cin >> t;

	while (t--) {
		ll n; cin >> n;
		ll p = 1;
		ll pp = pwr(p , p);
		ll sum = 0;
		while (n <= p) {
			int terms = n/p;

			if (terms%2 == 0) terms--;
			if (terms == 1) {
				sum = (sum + pp)%MOD;
			}
			else {
				if (p == 1) {
					sum = addmod(sum, pow1[terms/2]);
				}
				else if (p == 2) {
					sum = addmod(sum, mulmod(pp, pow2[terms/2]));
				}
				else if (p == 4) {
					sum = addmod(sum, mulmod(pp, pow4[terms/2]));
				}
				else if (p == 8) {
					sum = addmod(sum, mulmod(pp, pow8[terms/2]));
				}
			}
			p *= 2;
			pp = pwr(p, p);
		}
		cout << sum << endl;
	}
	
}

