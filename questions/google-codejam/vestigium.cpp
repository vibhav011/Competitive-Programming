#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;
	for (int cn=1; cn <= t; cn++) {
		int n; cin >> n;
		int m[n+1][n+1];
		int rows = 0, cols = 0, trace = 0;

		for (int i = 1; i <= n; i++) {
			set<int> s;
			bool repeated = false;
			for (int j = 1; j <= n; j++) {
				cin >> m[i][j];
				if (i == j) trace += m[i][j];
				if (!repeated) {
					if (s.find(m[i][j]) != s.end()) {
						repeated = true;
						rows++;
					}
					s.insert(m[i][j]);
				}
			}
		}
		for (int j = 1; j <= n; j++) {
			set<int> s;
			for (int i = 1; i <= n; i++) {
				if (s.find(m[i][j]) != s.end()) {
					cols++;
					break;
				}
				s.insert(m[i][j]);
			}
		}
		printf("Case #%d: %d %d %d\n", cn, trace, rows, cols);
	}
}