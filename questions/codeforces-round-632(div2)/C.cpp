#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	ll n; cin >> n;
	ll a[n+1]; ll prefsum[n+2];
	prefsum[0] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		prefsum[i] = a[i] + prefsum[i-1];
	}
	ll ans = 0;
	set<ll> appeared;
	appeared.insert(0);
	int r = 1;
	for (int i = 1; i <= n; i++) {
		while (appeared.find(prefsum[r]) == appeared.end() && r <= n) {
			appeared.insert(prefsum[r]);
			r++;
		}
		ans += r-i;
		appeared.erase(prefsum[i-1]);
	}

	printf("%lld\n", ans);

	return 0;
}