// incomplete

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll MOD = 1e9+7;

	int n, m;
	cin >> n >> m;

	int x[n+1];
	
	vector<vector<ll> > cnt(m+1, vector<ll>(n+1));
	for (int i = 1; i <= n; i++) cin >> x[i];

	if (m==1) {
		cout << "1\n";
		return 0;
	}

	cnt[0][0] = 1;
	cnt[1][0] = 1;
	
	for (int j = 1; j <= n; j++) {
		for (int i = 0; i < m; i++) {
			if (i == m-1) cnt[i][j] = (cnt[i][j-1] + cnt[i-1][j-1]) % MOD;
			cnt[i][j] = (cnt[i][j-1] + cnt[abs(i-1)][j-1] + cnt[i+1][j-1]) % MOD;
		}
	}
	ll ans = 0;
	int fi = 0, li = n;
	for (int i = 1; i <= n; i++) {
		if (x[i]) {
			fi = i;
			break;
		}
	}
	for (int i = n; i > 0; i--) {
		if (x[i]) {
			li = i;
			break;
		}
	}
	if (!fi) {
		if (n == 1) ans = m;
		else {
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= m; j++) {
					printf("(%d, %d) : %lld\n", i, j, cnt[abs(i-j)][n-2]);
					(ans += cnt[abs(i-j)][n-2]) %= MOD;
				}
			}
		}
	}
	else {
		ll mul1 = 0, mul2 = 0;
		for (int i = 1; i <= m; i++) {
			if (fi > 1) (mul1 += cnt[abs(i-x[fi])][fi-2]) %= MOD;
			if (li < n) (mul2 += cnt[abs(i-x[li])][n-li-1]) %= MOD;
		}
		if (!mul1) mul1 = 1;
		if (!mul2) mul2 = 1;
		ans = (mul1*mul2)%MOD;
		int temp = 0, last = x[1], cur = 0;
		for (int i = 2; i <= n; i++) {
			if (x[i]) {
				ans = (ans * cnt[abs(x[i]-last)][cur]) % MOD;
				cur = 0;
				last = x[i];
			}
			else cur++;
		}
	}
	// cout << cnt[0][1] << endl;
	cout << ans << endl;
}

