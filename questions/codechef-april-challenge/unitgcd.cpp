#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		cout << max(1, n/2) << endl;
		if (n == 1) cout << "1 1\n";
		else {
			for (int i = 1; i <= n/2-1; i++) {
				printf("2 %d %d\n", 2*i-1, 2*i);
			}
			if (n%2) printf("3 %d %d %d\n", n-2, n-1, n);
			else printf("2 %d %d\n", n-1, n);
		}
	}
}