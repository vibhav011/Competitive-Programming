#include <bits/stdc++.h>
using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n, x;
	cin >> n >> x;
	
	vector<vector<int> > ans(n+1, vector<int>(x+1));
	int h[n+1], s[n+1];
	for (int i = 1; i <= n; i++) cin >> h[i];
	for (int i = 1; i <= n; i++) cin >> s[i];
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= x; j++) {
			ans[i][j] = ans[i-1][j];
			if (j < h[i]) continue;
			ans[i][j] = max(ans[i][j], s[i] + ans[i-1][j-h[i]]);
		}
	}
	cout << ans[n][x] << endl;

}

