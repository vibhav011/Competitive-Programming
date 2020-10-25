#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

ll MOD = 1e9+7;

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

	ll fac[1001];
	fac[0] = 1;
	for (int i = 1; i < 1001; i++) {
		fac[i] = mulmod(fac[i-1], i);
	}
	int n, x, p;
	cin >> n >> x >> p;
	ll ans = 1;
	int a[n];
	for (int i = 0; i < n; i++) a[i] = -1;
	a[p] = 0;
	int les = x-1, gr = n-x;
	int lo = 0, hi = n, mid;
	while (lo < hi) {
		mid = (lo+hi)/2;
		if (mid <= p) {
			if (a[mid] == -1) {
				a[mid] = 0;
				ans = mulmod(ans, les);
				les--;
			}
			else if (a[mid] == 2) {
				ans = 0;
				break;
			}
			lo = mid+1;
		}
		else if (mid > p) {
			if (a[mid] == -1) {
				a[mid] = 2;
				ans = mulmod(ans, gr);
				gr--;
			}
			else if (a[mid] == 0) {
				ans = 0;
				break;
			}
			hi = mid;
		}
		if (!ans) break;
	}
	int left = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == -1) left++;
	}
	cout << mulmod(ans, fac[left]) << endl;
	
}

