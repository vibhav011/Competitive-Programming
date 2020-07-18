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

int ans[1000001];
int c[100], n, x;

int calc (int k) {
	if (ans[k] != -1) return ans[k];
	ans[k] = 0;
	for (int j = 0; j < n; j++) {
		if (c[j] > k) break;
		ans[k] = addmod(ans[k], calc(k-c[j]));
	}
	return ans[k];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> x;
	
	fill(ans, ans+x+1, -1);
	ans[0] = 1;
	for (int i = 0; i < n; i++) cin >> c[i];
	sort(c, c+n);
	
	cout << calc(x) << endl;
}

