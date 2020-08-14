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

inline ll submod(ll a, ll b){
	return (((a%MOD)-(b%MOD)+MOD)%MOD);
}

map<ll, ll> ans;

ll calc(ll n) {
	if (n < 3) return (n>0);
	if(ans[n]) return ans[n];
	ll k = n/2;
	ll fk = calc(k);
	ll fk2 = calc(k+1);
	if (n&1) ans[n] = addmod((fk*fk)%MOD, (fk2*fk2)%MOD);
	else ans[n] = mulmod(fk, submod(2*fk2, fk));
	return ans[n];
}

int main () {
	ll n; cin >> n;
	cout << calc(n) << endl;
}