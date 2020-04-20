#include <iostream>
using namespace std;

int main () {
	int t; cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		int ans = 0;
		int n; cin >> n;
		int a[n];

		for (int i = 0; i < n; i++) {
			cin >> a[i];
			if (i > 1) {
				if (a[i-1] > a[i-2] && a[i-1] > a[i]) ans++;
			}
		}
		printf("Case #%d: %d\n", cn, ans);
	}
}