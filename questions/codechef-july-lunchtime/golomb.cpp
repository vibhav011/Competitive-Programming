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


int bsh(ll val, ll ar[], int n) {		// return ind such that val >= ar[ind] and val < ar[ind+1]
	int a = 1, b = n - 1, c = (a+b)/2;
	if (val < ar[1]) return -1;
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

	int M = 2000001;
	inv6 = pwr(6, MOD-2);

	int *g = new int[M];
	ll *sum = new ll[M];
	ll *sum2 = new ll[M];
	sum[0] = 0;
	sum[1] = 1;
	sum2[0] = 0;
	sum2[1] = 1;
	g[1] = 1;
	
	for (int i = 2; i < M; i++) {
		g[i] = 1 + g[i-g[g[i-1]]];
		sum[i] = sum[i-1] + g[i];
		sum2[i] = sum2[i-1] + mulmod(g[i], pwr(i, 2));
	}

	int t; cin >> t;
	while (t--) {
		ll l, r;
		cin >> l >> r;
		int id1 = bsh(l, sum, M);
		int id2 = bsh(r, sum, M);
		if (sum[id1] < l) id1++;
		if (sum[id2] < r) id2++;

		ll ans = 0;
		ans = addmod(ans, mulmod(pwr(id1, 2), min(sum[id1]-l+1, r-l+1)));

		if (id1 < id2) ans = addmod(ans, mulmod(pwr(id2, 2), r-sum[id2-1]));

		if (id2 >= id1+2) {
			ans = addmod(ans, (sum2[id2-1]-sum2[id1]+MOD)%MOD);
		}
		cout << ans << endl;
	}
}

