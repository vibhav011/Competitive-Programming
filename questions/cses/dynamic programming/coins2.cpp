#include <iostream>
#include <vector>
using namespace std;

int main () {
	// ios_base::sync_with_stdio(0); cin.tie(0);
	int MOD = 1e9+7;

	int n, x;
	cin >> n >> x;

	vector<vector<int> > ans(n+1, vector<int>(x+1));
	int c[n+1];
	ans[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		++ans[i][0];
	}
	// sort(c+1, c+n+1);
	int rem, i, j;
	for (j = 1; j <= n; ++j) {
		for (i = 1; i <= x; ++i) {
			ans[j][i] = ans[j-1][i];
			rem = i-c[j];
			if (rem < 0) continue;
			(ans[j][i] += ans[j][rem]) %= MOD;
		}
	}
	
	printf("%d\n", ans[n][x]); fflush(stdout);
}