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
	ll a[n];
	for (int i = 0; i < n; i++) cin >> a[i];
	ll cur = a[0], ans = a[0];
	for (int i = 1; i < n; i++) {
		cur = max(cur, 0LL) + a[i];
		ans = max(ans, cur);
	}
	cout << ans << endl;
}

