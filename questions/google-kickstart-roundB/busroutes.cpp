#include <iostream>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		ll n, d; cin >> n >> d;
		ll x[n];

		for (int i = 0; i < n; i++) {
			cin >> x[i];
		}

		for (int i = n-1; i >= 0; i--) {
			d = d - d%x[i];
		}

		printf("Case #%d: %lld\n", cn, d);
	}
}