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

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n; cin >> n;
	
	// if (n < 10) {
	// 	cout << "1\n";
	// 	return 0;
	// }
	int ans[n+1];
	ans[0] = 0;
	for (int i = 1; i <= n; i++) {
		ans[i] = i;
		int k = i;
		while (k > 0) {
			ans[i] = min(ans[i], 1+ans[i-k%10]);
			k = k/10;
		}
	}
	cout << ans[n] << endl;
}

