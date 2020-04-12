#include <bits/stdc++.h>
#define ll long long int
using namespace std;

void zigzag(int k, bool w) {
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= i; j++) {
			int p = ((i%2)^w) ? (j+1) : (i+1-j);
			printf("%d %d\n", i+1, p);
		}
	}
}

int main () {
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		int n; cin >> n;
		printf("Case #%d:\n", cn);

		int n2 = n;
		int k = -1;
		while (n2) {
			k++;
			n2 >>= 1;
		}

		if (!(n&(n+1))) {
			zigzag(k, true);
			continue;
		}

		zigzag(k-1, 1-(k%2));
		int left = n+1 - (1 << k);
		while (left > k) {
			left -= k;
			printf("%d 2\n", k+1);
			k++;
		}
		while (left > 0) {
			left--;
			printf("%d 1\n", k+1);
			k++;
		}
	}
}