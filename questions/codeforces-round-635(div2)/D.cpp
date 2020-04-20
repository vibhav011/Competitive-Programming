#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		int nr, ng, nb;
		cin >> nr >> ng >> nb;
		set<ll> r, g, b;

		for (int i = 0; i < nr; i++) {int x; cin >> x; r.insert(x);}
		for (int i = 0; i < ng; i++) {int x; cin >> x; g.insert(x);}
		for (int i = 0; i < nb; i++) {int x; cin >> x; b.insert(x);}

		ll ans = ((ll)1 << 62);

		set<ll>::iterator i, j, j2, j3, k, k2, k3;
		ll x, y, z, y2, z2;

		for (i = r.begin(); i != r.end(); i++) {
			x = *i;
			j = lower_bound(g.begin(), g.end(), *i);
			k = lower_bound(b.begin(), b.end(), *i);
			if (j == g.end()) j--;
			if (k == b.end()) k--;
			j2 = (j != g.begin()) ? prev(j, 1): j;
			k2 = (k != b.begin()) ? prev(k, 1): k;
			if (*k > *j) {
				j3 = lower_bound(g.begin(), g.end(), (*i + *k)/2);
				if (j3 == g.end()) j3--;
				y = *j3; z = *k; y2 = y; z2 = z;
				if (j3 != g.begin()) j3--;
				y2 = *j3;
			}
			else if (*j > *k) {
				k3 = lower_bound(b.begin(), b.end(), (*i + *j)/2);
				if (k3 == b.end()) k3--;
				y = *j; z = *k3; y2 = y; z2 = z;
				if (k3 != b.begin()) k3--;
				z2 = *k3;
			}
			ans = min(ans, (x-y)*(x-y) + (y-z)*(y-z) + (z-x)*(z-x));
			ans = min(ans, (x-y2)*(x-y2) + (y2-z2)*(y2-z2) + (z2-x)*(z2-x));
			if (*k2 < *j2) {
				j3 = lower_bound(g.begin(), g.end(), (*i + *k2)/2);
				if (j3 == g.end()) j3--;
				y = *j3; z = *k2; y2 = y; z2 = z;
				if (j3 != g.begin()) j3--;
				y2 = *j3;
			}
			else if (*j2 < *k2) {
				k3 = lower_bound(b.begin(), b.end(), (*i + *j2)/2);
				if (k3 == b.end()) k3--;
				y = *j2; z = *k3; y2 = y; z2 = z;
				if (k3 != b.begin()) k3--;
				z2 = *k3;
			}
			ans = min(ans, (x-y)*(x-y) + (y-z)*(y-z) + (z-x)*(z-x));
			ans = min(ans, (x-y2)*(x-y2) + (y2-z2)*(y2-z2) + (z2-x)*(z2-x));
		}
		cout << ans << endl;
	}
}