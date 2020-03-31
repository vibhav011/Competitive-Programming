#include <iostream>
#define ll long long int
using namespace std;
ll p = 998244353;

ll pwr(ll x, ll y) {
	ll res = 1;	  // Initialize result 
  
	x = x % p;  // Update x if it is more than or 
				// equal to p 
  
	while (y > 0) { 
		// If y is odd, multiply x with result 
		if (y & 1) 
			res = (res*x) % p; 
  
		// y must be even now 
		y = y>>1; // y = y/2 
		x = (x*x) % p; 
	} 
	return res; 
}

int main() {
	ll n, m, l, r;
	cin >> n >> m >> l >> r;

	ll sub = 0;
	if (!((n%2) && (m%2))) sub = ((pwr(r-l+1, n*m)-((r-l+1)&1))*pwr(2, p-2))%p;
	ll ans = pwr(r-l+1, n*m)-sub;
	if (ans < 0) ans += p;
	cout << ans << endl;

	return 0;
}