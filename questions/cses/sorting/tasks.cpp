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
	ios_base::sync_with_stdio(0); cin.tie(0);

	ll n; cin >> n;
	vector<pll> t;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		t.pb(mp(x, y));
	}
	sort(t.begin(), t.end());
	ll ans = 0;
	ll cur = 0;
	for (int i = 0; i < n; i++) {
		cur += t[i].ff;
		ans += t[i].ss - cur;
	}
	cout << ans << endl;
}

