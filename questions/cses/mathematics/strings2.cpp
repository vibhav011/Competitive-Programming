#include <bits/stdc++.h>
#define ll long long int

using namespace std;

const ll MOD = 1e9+7;

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return (((a%MOD)*(b%MOD))%MOD);
}

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

int main () {
	int M = 1e6+1;
	ll fac[M];
	fac[0] = 1;
	for (int i = 1; i < M; i++)
		fac[i] = mulmod(i, fac[i-1]);

	string s; cin >> s;
	int n = s.size();
	vector<int> freq(26);
	for (int i = 0; i < n; i++) freq[s[i]-'a']++;
	ll ans = fac[n];
	for (int i = 0; i < 26; i++) {
		ans = mulmod(ans, pwr(fac[freq[i]], MOD-2));
	}
	cout << ans << endl;
}