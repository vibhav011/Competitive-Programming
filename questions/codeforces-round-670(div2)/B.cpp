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

bool custSort(pll &p1, pll &p2) {
	return (p1.ff > p2.ff);
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int k = 5;
		
		vector<pll> a;
		for (int i = 0; i < n; i++) {
			ll x; cin >> x;
			int sign = 0;
			if (x) sign = (x > 0) ? 1 : -1;
			a.pb(mp(abs(x), sign));
		}
		sort(a.begin(), a.end(), custSort);
		//for (int i = 0; i < n; i++) {printf("(%lld, %lld)", a[i].ff, a[i].ss);}
		ll ans = 1;
		int pos = 0, neg = 0;
		int pi = -1, ni = -1;
		bool z = false;
		for (int i = 0; i < k; i++) {
			ans = ans * a[i].ff;
			if (a[i].ss == 1) {pos++; pi = i;}
			else if (a[i].ss == -1) {neg++; ni = i;}
			else {z = true; break;}
		}
		//cout << ans << endl;
		if (z || (neg&1) == 0 || n == k) {
			if (neg&1) cout << -ans << endl;
			else cout << ans << endl;
			continue;
		}

		if (pi == -1) {
			bool cont = false;
			for (int i = k; i < n; i++) {
				if (a[i].ss == 1) {
					ans = a[i].ff * (ans/a[k-1].ff);
					// ans = mulmod(a[i].ff, mulmod(ans, pwr(a[k-1].ff, MOD-2)));
					cout << ans << endl;
					cont = true;
					break;
				}
				if (a[i].ss == 0) {
					cout << "0\n";
					cont = true;
					break;
				}
			}
			if (cont) continue;
			ans = 1;
			for (int i = n-1; i >= n-k; i--) {
				ans = ans*a[i].ff;
			}
			cout << -ans << endl;
			continue;
		}

		bool contt = false;
		int fpi = -1, fni = -1;
		for (int i = k; i < n; i++) {
			if (fpi > 0 && fni > 0) break;
			if (a[i].ss == 0 && i == k) {
				cout << "0\n";
				contt = true;
				break;
			}
			if (a[i].ss == 1 && fpi == -1) fpi = i;
			if (a[i].ss == -1 && fni == -1) fni = i;
		}
		if (contt) continue;

		if (fpi == -1) {
			ans = a[fni].ff * (ans/a[pi].ff);
			// ans = mulmod(a[fni].ff, mulmod(ans, pwr(a[pi].ff, MOD-2)));
			cout << ans << endl;
			continue;
		}
		if (fni == -1) {
			ans = a[fpi].ff * (ans/a[ni].ff);
			// ans = mulmod(a[fpi].ff, mulmod(ans, pwr(a[ni].ff, MOD-2)));
			cout << ans << endl;
			continue;
		}

		if (a[fni].ff*a[ni].ff > a[fpi].ff*a[pi].ff) {
			ans = a[fni].ff * (ans/a[pi].ff);
			// ans = mulmod(a[fni].ff, mulmod(ans, pwr(a[pi].ff, MOD-2)));
		}
		else {
			ans = a[fpi].ff * (ans/a[ni].ff);
			// ans = mulmod(a[fpi].ff, mulmod(ans, pwr(a[ni].ff, MOD-2)));
		}
		cout << ans << endl;

	}
}

