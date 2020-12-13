#include <bits/stdc++.h>
#define pii pair<int, int>
#define int long long
#define ff first
#define ss second

using namespace std;

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	while (t--) {
		pii x[4], y[4];
		for (int i = 0; i < 4; i++) {
			cin >> x[i].ff >> y[i].ff;
			x[i].ss = y[i].ss = (1 << i);
		}
		bool extra = false;

		sort(x, x+4);
		sort(y, y+4);

		if (x[0].ss + x[1].ss == y[0].ss + y[1].ss ||
			x[0].ss + x[1].ss == y[2].ss + y[3].ss) {
			int ans1 = x[3].ff + x[2].ff - x[1].ff - x[0].ff + y[3].ff - y[2].ff + y[1].ff - y[0].ff;
			int ans2 = y[3].ff + y[2].ff - y[1].ff - y[0].ff + x[3].ff - x[2].ff + x[1].ff - x[0].ff;

			cout << min(ans1, ans2) << endl;
			continue;
		}

		int bot = y[1].ff - y[0].ff;
		int top = y[3].ff - y[2].ff;
		int left = x[1].ff - x[0].ff;
		int right = x[3].ff - x[2].ff;

		int min_w = x[2].ff - x[1].ff;
		int max_w = x[3].ff - x[0].ff;
		int min_h = y[2].ff - y[1].ff;
		int max_h = y[3].ff - y[0].ff;

		int ans = bot + top + left + right;

		if (max_h < min_w) {
			ans += 2*(min_w-max_h);
		}
		else if (max_w < min_h) {
			ans += 2*(min_h-max_w);
		}

		cout << ans << endl;

	}
	
}

