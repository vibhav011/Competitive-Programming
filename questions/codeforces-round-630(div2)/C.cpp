#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while(t--) {
		int n, k; cin >> n >> k;
		int a[k][n/k];
		
		for (int i = 0; i < n/k; i++) for (int j = 0; j < k; j++) {
			char c; cin >> c;
			a[j][i] = c-'a';
		}
		int ans = 0;
		int freq[26]; fill(freq, freq+26, 0);
		for (int i = 0; i < k/2; i++) {
			for (int j = 0; j < n/k; j++) {
				freq[a[i][j]]++;
				freq[a[k-i-1][j]]++;
			}
			int m = 0;
			for (int l = 0; l < 26; l++) m = max(m, freq[l]);
			ans += (2*(n/k)-m);
			fill(freq, freq+26, 0);
		}
		if (k%2) {
			for (int j = 0; j < n/k; j++) {
				freq[a[(k-1)/2][j]]++;
			}
			int m = 0;
			for (int l = 0; l < 26; l++) m = max(m, freq[l]);
			ans += (n/k-m);
		}
		cout << ans << endl;
	}
	return 0;
}