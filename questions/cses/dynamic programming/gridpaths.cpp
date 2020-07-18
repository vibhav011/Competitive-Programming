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
	
	int ans[n+1][n+1];
	ans[1][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != 1 || j != 1) ans[i][j] = -1;
			char c; cin >> c;
			if (c == '*') ans[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
		ans[i][0] = 0;
		ans[0][i] = 0;
	}
	if (ans[1][1] == 0 || ans[n][n] == 0) {
		cout << "0\n";
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (ans[i][j] == -1) {
				ans[i][j] = addmod(ans[i-1][j], ans[i][j-1]);
			}
		}
	}
	cout << ans[n][n] << endl;
}

