#include <bits/stdc++.h>
using namespace std;

long long int gcd(long long int a, long long int b) {			// a <= b
	if (a > b) swap(a, b);
	if (b%a == 0) return a;
	return gcd(b%a, a);
}

long long int lcm(long long int a, long long int b) {
	return a*b/gcd(a, b);
}

int main() {
	int t; cin >> t;

	while(t--) {
		int n, m; cin >> n >> m;
		long long int lc = 1;
		for (int i = 0; i < n; i++) {
			long long int temp; cin >> temp;
			lc = lcm(lc, temp);
		}
		int j = 0;
		for (int i = 1; i <= m; i++) {
			if (gcd(i, lc) == 1) j = i;
		}
		cout << j << endl;
	}
}