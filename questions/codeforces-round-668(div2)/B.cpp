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

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		int a[n];
		vector<int> pos, neg;
		
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			if (a[i] > 0) pos.pb(i);
			if (a[i] < 0) neg.pb(i);
		}

		int fir = pos.size()-1;
		int las = 0;

		ll ans = 0;
		for (int i = 0; i < n; i++) {
			if (!a[i]) continue;
			if (a[i] < 0) {
				int m = -a[i];
				a[i] = 0;
				// cout << i << ' ' << m << endl;
				ans += m;
				while (m > 0) {
					if (a[pos[fir]] > m) {
						a[pos[fir]] -= m;
						m = 0;
					}
					else {
						m -= a[pos[fir]];
						a[pos[fir]] = 0;
						fir--;
					}

				}
				// for (int i = 0 ; i < n; i ++) cout << a[i] << ' ';
				// cout << endl;
			}
			else {
				int m = a[i];
				a[i] = 0;
				// cout << i << ' ' << m << endl;
				
				while (m > 0) {
					// if (!a[neg[las]]) {
					// 	las++;
					// 	continue;
					// }
					if (-a[neg[las]] > m) {
						a[neg[las]] += m;
						m = 0;
					}
					else {
						m += a[neg[las]];
						a[neg[las]] = 0;
						las++;
					}

				}
				// for (int i = 0 ; i < n; i ++) cout << a[i] << ' ';
				// cout << endl;
			}
		}
		cout << ans << endl;
		
	}
	
}

