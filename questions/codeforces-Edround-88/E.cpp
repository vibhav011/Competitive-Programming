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
ll fac[500001];
ll facPwr[500001];

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

ll C(int n, int r)  {
	if (r == 0) return 1;
  	if (r > n) return 0; 
  
	return (((fac[n] * facPwr[r]) % MOD) * 
				facPwr[n-r]) % MOD;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	fac[0] = 1;
	for (int i=1 ; i<=500000; i++) fac[i] = (fac[i-1]*i)%MOD;

	facPwr[0] = 1;
	for (int i=1 ; i<=500000; i++) facPwr[i] = pwr(fac[i], MOD-2);

	ll n, k; cin >> n >> k;

	ll p = n/k;
	if (!p) cout << "0\n";
	else {
		ll ans = 0;
		for (int j = 1; j <= p; j++) {
			ans = (ans + C(n/j - 1, k-1)) % MOD;
		}
		cout << ans << endl;
	}
}