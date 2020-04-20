#include <bits/stdc++.h>
using namespace std;
int M = 1000000007;

int main () {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int p[n];
		for (int i = 0; i < n; i++) cin >> p[i];
		sort(p, p+n, greater<int>());

		int sum = 0;
		for (int i = 0; i < n; i++) {
			sum = (max(p[i]-i, 0) + sum) % M;
		}
		cout << sum << endl;
	}
}