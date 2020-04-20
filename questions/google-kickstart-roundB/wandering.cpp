#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		int w, h, l, u, r, d;
		cin >> w >> h >> l >> u >> r >> d;

		double ans[w+1][h+1];
		for (int i = 0; i <= w; i++) {
			for (int j = 0; j <= h; j++) {
				if (!i || !j || (i == r && j >= u && j <= d) || (j == d && i >= l && i <= r)) ans[i][j] = 0;
				else if (i == 1 && j == 1) ans[i][j] = 1;
				else {
					double x = (i < w) ? 0.5 : 1;
					double y = (j < h) ? 0.5 : 1;
					ans[i][j] = y*ans[i-1][j] + x*ans[i][j-1];
				}
			}
		}

		printf("Case #%d: %f\n", cn, ans[w][h]);
	}
}