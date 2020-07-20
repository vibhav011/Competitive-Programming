#include <bits/stdc++.h>
using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int MOD = 1e9+7;

	int n, x;
	cin >> n >> x;

	vector<vector<int> > ans(x+1, vector<int>(n));
	int c[n];
	
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		ans[0][i] = 1;
	}
	sort(c, c+n);
	
	for (int i = 1; i <= x; i++) {
		for (int j = 0; j < n; j++) {
			if (j > 0) ans[i][j] = ans[i][j-1];
			if (c[j] > i) continue;
			(ans[i][j] += ans[i-c[j]][j]) %= MOD;
		}
	}
	
	cout << ans[x][n-1] << endl;
}