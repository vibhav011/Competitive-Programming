#include <bits/stdc++.h>
using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int MOD = 1e9+7;

	int n, x;
	cin >> n >> x;

	int ans[x+1];
	int c[n];
	
	// fill(ans, ans+x+1, -1);
	ans[0] = 1;

	for (int i = 0; i < n; i++) cin >> c[i];
	sort(c, c+n);
	
	for (int i = 1; i <= x; i++) {
		ans[i] = 0;
		for (int j = 0; j < n; j++) {
			if (c[j] > i) break;
			// ans[i] = addmod(ans[i], ans[i-c[j]]);
			(ans[i] += ans[i-c[j]]) %= MOD;
		}
	}
	
	cout << ans[x] << endl;
}