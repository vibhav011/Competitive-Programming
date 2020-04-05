#include <bits/stdc++.h>
#define ll long long int
#define M 10000001
using namespace std;

vector<ll> primes;
short cnt[M];
ll ans[M];

ll pwr(ll x, ll y) {
	ll res = 1;	  // Initialize result 
  
	while (y > 0) { 
		// If y is odd, multiply x with result 
		if (y & 1) 
			res = res * x; 
  
		// y must be even now 
		y = y>>1; // y = y/2 
		x = x * x; 
	} 
	return res; 
}

int main() {
	int t; scanf("%d", &t);
	bool is_composite[M];
	fill(is_composite, is_composite + M, false);

	cnt[1] = 1;
	ans[1] = 1;

	for (ll i = 2; i < M; i++) {
		if (!is_composite[i]) {
			primes.push_back(i);
			cnt[i] = 1;
			ans[i] = i*i - i + 1;
		}
		for (ll j = 0; j < primes.size() && i*primes[j] < M; j++) {
			is_composite[i*primes[j]] = true;
			if (i % primes[j]) {
				cnt[i*primes[j]] = 1;
				ans[i*primes[j]] = ans[i] * ans[primes[j]];
			}
			else {
				cnt[i*primes[j]] = 1 + cnt[i];
				ll p2k = pwr(primes[j], 2*cnt[i]+2);
				ans[i*primes[j]] = ans[i/pwr(primes[j], cnt[i])] * (p2k - (p2k-1)/(primes[j]+1));
				break;
			}
		}
	}

	while (t--) {
		int n; scanf("%d", &n);
		printf("%lld\n", ans[n]);
	}
}