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
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		ll l, r; cin >> l >> r;
		ll i = 1;
		ll *x, *y;
		while (i <= max(l, r)) {
			if (l >= r) {x = &l; y = &r;}
			else {x = &r; y = &l;}
			ll j = (sqrt(4*i*i - 4*i + 8*(*x - *y) + 1) - 1)/2;

			ll sum = (j-i+1)*(i+j)/2;

			if (sum + j + 1 <= *x) {
				if ((*x - *y) == sum) {
					if (x == &l) j++;
				}
				else j++;
			}
			
			*x -= (j-i+1)*(i+j)/2;
			i = j+1;
		}
		printf("Case #%d: %lld %lld %lld\n", cn, i-1, l, r);
	}
}

