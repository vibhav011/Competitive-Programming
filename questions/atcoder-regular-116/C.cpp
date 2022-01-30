#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define MAX 200005

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y, ll mod = MOD) {
	ll res = 1;
	x = x%mod;
	while (y > 0) {
		if (y&1) res = (res*x)%mod;

		y = y>>1;
		x = (x*x)%mod;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

vector<int> primes;
vector<pair<int, int> > fact[MAX];

void factorize() {
	bool is_composite[MAX];
	fill(is_composite, is_composite+MAX, false);

	for (int i = 2; i < MAX; i++) {
		if (!is_composite[i]) {
			primes.push_back(i);
			fact[i].push_back(make_pair(i, 1));
		}
		for (int j = 0; j < primes.size() && i*primes[j] < MAX; j++) {
			is_composite[i*primes[j]] = true;

			if (i%primes[j] == 0) {
				fact[i*primes[j]] = fact[i];
				fact[i*primes[j]][0].second++;
				break;
			}
			else {
				fact[i*primes[j]] = fact[primes[j]];
				fact[i*primes[j]].insert(fact[i*primes[j]].end(), fact[i].begin(), fact[i].end());
			}
		}
	}
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	factorize();

	// for (int i = 2; i < 20; i++) {
	// 	for (pii p : fact[i]) cout << "(" << p.ff << ", " << p.ss << "), ";
	// 	cout << '\n';
	// }

	int n, m;
	cin >> n >> m;

	int fac[n+m], invfac[n+m];
	fac[0] = invfac[0] = 1;
	for (int i = 1; i < n+m; i++) {
		fac[i] = mulmod(i, fac[i-1]);
		invfac[i] = pwr(fac[i], MOD-2);
	}

	int dp[m+1];
	dp[1] = 1;
	for (int i = 2; i <= m; i++) {
		int extra = 1;
		for (pii p : fact[i]) {
			extra = mulmod(extra, (((fac[n+p.ss-1]*invfac[n-1])%MOD)*invfac[p.ss])%MOD);
		}
		dp[i] = addmod(extra, dp[i-1]);
	}
	cout << dp[m] << '\n';

}

