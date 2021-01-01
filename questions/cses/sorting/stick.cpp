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
	sort(a, a+n);
	ll med = a[n/2], ans = 0;
	for (int i = 0; i < n; i++) {
		ans += abs(med - a[i]);
	}
	cout << ans << endl;
}

