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
const int mx = 2e5+5;
ll fac[mx];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll inv2 = pwr(2, MOD-2);
	fac[0] = 1;
	for (int i = 1; i < mx; i++) {
		fac[i] = mulmod(i, fac[i-1]);
	}

	int t; cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;
		int x;
		ll freq[n];
		memset(freq, 0, sizeof(freq));
		freq[0] = 1;
		for (int i = 0; i < n-1; i++) {
			cin >> x;
			freq[x]++;
		}
		int sum = 0;
		bool pos = true;
		ll ans = 1;
		ll prs = 0;
		for (int i = 1; i < n && sum < n-1; i++) {
			if (freq[i] == 0 && sum < n-1) {
				pos = false;
				break;
			}
			sum += freq[i];
			ans = mulmod(ans, pwr(freq[i-1], freq[i]));
			prs += freq[i]*(freq[i]-1)/2;
		}
		if (!pos) cout << "0\n";
		else {
			m -= n-1;
			if (m > prs) cout << "0\n";
			else {
				ll ncr;
				if (m == 0) ncr = 1;
				else  {
					ll p1 = 1;
					for (int i = 0; i < m; i++) p1 = mulmod(p1, prs-i);
					ncr = mulmod(pwr(fac[m], MOD-2), p1);
				}
				cout << mulmod(ans, ncr) << endl;
			}
		}
	}
	
}

