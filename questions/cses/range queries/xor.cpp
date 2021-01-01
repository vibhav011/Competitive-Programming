#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	ll n, q;
	cin >> n >> q;
	ll pref[n+1]; pref[0] = 0;
	ll x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		pref[i+1] = pref[i]^x;
	}
	while (q--) {
		ll a, b; cin >> a >> b;
		cout << (pref[b] ^ pref[a-1]) << '\n';
	}
}

