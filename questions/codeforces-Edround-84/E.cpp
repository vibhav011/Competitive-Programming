#include <bits/stdc++.h>
using namespace std;
int M = 998244353;

int main() {
	int n; cin >> n;
	long long int pows[n];
	pows[0] = 1;
	for (int i = 1; i < n; i++) pows[i] = (pows[i-1] * 10) % M;

	for (int i = 1; i <= n; i++) {
		if (i == n) cout << 10 << endl;
		else if (i == n-1) cout << 180 << ' ';
		else {
			long long int ans = (pows[n-i-2] * 81) % M;
			ans = (ans * (n-1-i)) % M;
			ans = ((ans + pows[n-i-1]*18) * 10) % M;
			cout << ans << ' ';
		}
	}
}