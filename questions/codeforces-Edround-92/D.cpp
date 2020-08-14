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
		ll n, k, l[2], r[2];
		cin >> n >> k >> l[0] >> r[0] >> l[1] >> r[1];
		ll init, mn, mx;
		if (r[0] <= l[1] || l[0] >= r[1]) {
			init = 0;
			int f = (l[0] <= l[1]) ? 0 : 1;
			int s = 1-f;
			mn = l[s] - r[f];
			mx = r[s] - l[f];
		}
		else if ((l[1]-l[0])*(r[0]-r[1]) >= 0) {
			init = min(r[1]-l[1], r[0]-l[0]);
			mn = 0;
			mx = abs(r[1]-r[0]) + abs(l[1]-l[0]);
		}
		else {
			mn = 0;
			if (l[0] <= l[1]) {init = r[0]-l[1]; mx = l[1]-l[0]+r[1]-r[0];}
			else {init = r[1]-l[0]; mx = -(l[1]-l[0]+r[1]-r[0]);}
		}
		// cout << init << ' ' << mn << ' ' << mx<< endl;
		if (init*n >= k) {
			cout << "0\n";
			continue;
		}

		k -= init*n;
		if (mx >= k) {
			cout << mn + k << endl;
			continue;
		}
		ll ans = (1ll << 55);
		for (ll i = 1; i <= n; i++) {
			if ((i-1)*mx >= k) break;
			if (i *mx >= k) ans = min(ans, i*mn + k);
			else ans = min(ans, (mn+mx)*i + 2*(k-i*mx));
		}
		cout << ans << endl;
		// ll tim = k/mx;
		// ll rem = k%mx;
		// if (tim < n || (tim == n && rem == 0)) {
		// 	cout << min(tim*(mn+mx) + mn + rem, mn+ ((tim) ? mx + 2*(k-mx) : k)) << endl;
		// } 
		// else {
		// 	cout << min(n*(mn+mx) + 2*(k-n*mx), mn+mx+2*(k-mx)) << endl;
		// }

	}
}

