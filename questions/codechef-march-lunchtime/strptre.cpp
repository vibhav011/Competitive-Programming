#include <bits/stdc++.h>
using namespace std;
int p = 1000000007;

long long int pwr(long long int x, int y) {
	long long int res = 1;	  // Initialize result 
  
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
	int t; cin >> t;

	while (t--) {
		int d; cin >> d;
		int extra = 0;
		long long int m = d/2;
		if (d % 2) {
			extra = (3*pwr(2, d-1)*(d+1))%p;
		}
		long long int n = pwr(2, d+1)-1;
		long long int sum = ((3*m-1) * pwr(2, 2*m+1) + 2 + extra)%p;
		sum = (sum * pwr(3, p-2)) % p;
		sum = (sum * pwr(n, p-2)) % p;
		sum = (sum * pwr(n-1, p-2)) % p;
		cout << sum << endl;
	}
}