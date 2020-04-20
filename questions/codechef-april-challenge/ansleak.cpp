#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n, m, k;
		cin >> n >> m >> k;
		int c[n][k];
		for (int i = 0; i < n; i++) for (int j = 0; j < k; j++) cin >> c[i][j];
		int ans[n]; memset(ans, 0, sizeof(ans));
		int score[k]; memset(score, 0, sizeof(score));
		int min_score = 0;
		for (int line = 0; line < n; line++) {
			int mode = 0, ln = 0, _ans = 0;
			for (int i = 0; i < n; i++) {
				if (ans[i]) continue;
				int freq[m+1]; memset(freq, 0, sizeof(freq));
				int freq2[m+1]; memset(freq2, 0, sizeof(freq2));
				for (int j = 0; j < k; j++) {
					freq2[c[i][j]]++;
					if (score[j] == min_score) freq[c[i][j]]++;
				}
				int mm = 0, an = 1, mm2 = 0;
				for (int ii = 1; ii <= m; ii++) {
					if (mm < freq[ii] || (m == freq[ii] && mm2 < freq2[ii])) {
						mm = freq[ii];
						mm2 = freq2[ii];
						an = ii;
					}
				}
				if (mm > mode) {
					mode = mm;
					ln = i;
					_ans = an;
				}
			}
			ans[ln] = _ans;
			for (int jj = 0; jj < k; jj++) if (c[ln][jj] == _ans) score[jj]++;
			min_score = n+1;
			for (int jj = 0; jj < k; jj++) min_score = min(min_score, score[jj]);
		}
		for (int i = 0; i < n; i++) cout << ans[i] << ' ';
		cout << endl;
	}

	return 0;
}
