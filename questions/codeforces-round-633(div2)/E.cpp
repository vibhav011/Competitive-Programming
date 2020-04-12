#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		ll n; cin >> n;
		n--;
		
		ll gr = n/3 + 1;
		int ind = n%3;
		ll x = 3*gr+1;
		ll k = -1;
		while (x) {
			k++;
			x >>= 1;
		}
		ll one = 1;
		ll b = k - 2;
		if (k%2) b++;
		else {
			if (3*gr+1 != (one << k)) b += 2;
		}
		ll gr2 = gr - 1 - ((one << b) - 1)/3;

		ll ans[3];
		ans[0] = (one << b) + gr2;
		ans[1] = 0;
		ll beta = ans[0];
		int in = 0;
		while (beta) {
			ll d = beta % 4;
			if (d) ans[1] += ((d%3+1) << in);
			in += 2;
			beta >>= 2;
		}
		ans[2] = ans[0] ^ ans[1];
		cout << ans[ind] << endl;
	}
}