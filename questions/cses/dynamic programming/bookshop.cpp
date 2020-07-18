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

int ans[100001];
int h[1000], s[1000], n, x;
bool aval[1000];

int calc (int k) {
	if (ans[k] != -1) return ans[k];
	ans[k] = ans[k-1];
	for (int j = 0; j < n; j++) {
		if (k >= h[j] && aval[j]) {
			aval[j] = false;
			ans[k] = max(ans[k], s[j]+calc(k-h[j]));
			aval[j] = true;
		}
	}
	return ans[k];
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> n >> x;
	
	fill(ans, ans+x+1, -1);
	ans[0] = 0;
	for (int i = 0; i < n; i++) cin >> h[i];
	for (int i = 0; i < n; i++) cin >> s[i];
	
	memset(aval, true, sizeof(aval));
	
	cout << calc(x) << endl;
}

