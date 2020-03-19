#include <bits/stdc++.h>
using namespace std;

bool isEven(int n) {
	int ones = 0;
	while (n != 0) {
		ones += (n & 1);
		n = n>>1;
	}
	return (ones%2 == 0);
}

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		int n, q;
		//cin >> n >> q;
		scanf("%d %d", &n, &q);

		int evens = 0;

		for (int i = 0; i < n; i++) {
			int temp;
			scanf("%d", &temp);

			if (isEven(temp)) evens++;
		}

		while (q--) {
			int p;
			scanf("%d", &p);
			int e = n - evens;
			if (isEven(p)) e = evens;

			//cout << e << ' ' << n-e << endl;
			printf("%d %d\n", e, n-e);
		}
	}
}