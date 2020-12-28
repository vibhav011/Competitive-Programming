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

const int M = 2e5+5;
ll fac[M];

ll C(ll n, ll k) {
	if (k > n || n < 0 || k < 0) return 0;
	return mulmod(fac[n], pwr(mulmod(fac[k], fac[n-k]), MOD-2));
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	fac[0] = 1;
	for (int i = 1; i < M; i++) fac[i] = mulmod(i, fac[i-1]);

	int t; cin >> t;

	while (t--) {

		int n, m, k; cin >> n >> m >> k;
		vector<ll> freq(n+1);

		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			freq[x]++;
		}
		vector<ll> prefsum(n+1);
		prefsum[0] = 0;
		for (int i = 1; i <= n; i++) prefsum[i] = freq[i] + prefsum[i-1];

		ll ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (j > freq[i]) break;
				ans = addmod(ans, mulmod(C(freq[i], j), C(prefsum[min(i+k, n)]-prefsum[i], m-j)));
			}
		}
		cout << ans << endl;
	}
}

