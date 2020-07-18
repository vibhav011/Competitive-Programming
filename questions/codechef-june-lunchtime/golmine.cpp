#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define double long double

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

bool custSort(pair<double, int> &p1, pair<double, int> &p2) {
	return (p1.ff >= p2.ff);
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cout << fixed;
	cout << setprecision(15);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		// double g[n];
		double a = 0, b = 0;
		for (int i = 0; i < n; i++) {
			double g, a1, b1;
			cin >> g >> a1 >> b1;
			a += g / (a1+b1) * b1;
			b += g / (a1+b1) * a1;
		}
		// vector<pair<double, int> > ra, rb;
		// for (int i = 0; i < n; i++) {
		// 	cin >> g[i];
		// 	double a1, b1; cin >> a1 >> b1;
		// 	ra.pb(mp(g[i]/a1, i));
		// 	rb.pb(mp(g[i]/b1, i));
		// }
		// sort(ra.begin(), ra.end(), custSort);
		// sort(rb.begin(), rb.end(), custSort);
		// int i = 0, j = 0;
		// while (i < n || j < n) {
		// 	if (i == n) {
		// 		int ind2 = rb[j].ss;
		// 		b += g[ind2];
		// 		g[ind2] = 0;
		// 		j++;
		// 		continue;
		// 	}
		// 	else if (j == n) {
		// 		int ind1 = ra[i].ss;
		// 		a += g[ind1];
		// 		g[ind1] = 0;
		// 		i++;
		// 		continue;
		// 	}
		// 	if (ra[i].ss == rb[j].ss) {
		// 		int ind = ra[i].ss;
		// 		a += g[ind] / (ra[i].ff + rb[j].ff) * (ra[i].ff);
		// 		b += g[ind] / (ra[i].ff + rb[j].ff) * (rb[j].ff);
		// 		g[ind] = 0;
		// 		i++; j++;
		// 	}
		// 	else {
		// 		int ind1 = ra[i].ss;
		// 		int ind2 = rb[j].ss;
		// 		if (g[ind1]/ra[i].ff < g[ind2]/rb[j].ff) {
		// 			a += g[ind1];
		// 			g[ind1] = 0;
		// 			b += g[ind1] / ra[i].ff * rb[j].ff;
		// 			g[ind2] -= g[ind1] / ra[i].ff * rb[j].ff;
		// 			i++;
		// 		}
		// 		else if (g[ind1]/ra[i].ff > g[ind2]/rb[j].ff) {
		// 			b += g[ind2];
		// 			g[ind2] = 0;
		// 			a += g[ind2] / rb[j].ff * ra[i].ff;
		// 			g[ind1] -= g[ind2] / rb[j].ff * ra[i].ff;
		// 			j++;
		// 		}
		// 		else {
		// 			a += g[ind1];
		// 			b += g[ind2];
		// 			g[ind1] = 0;
		// 			g[ind2] = 0;
		// 			i++; j++;
		// 		}
		// 	}
		// }
		cout << a << ' ' << b << endl;
	}
}

