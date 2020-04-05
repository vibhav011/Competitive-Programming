#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n, x; cin >> n >> x;
		int a[300]; fill(a, a+300, 0);
		for (int i = 0; i < n; i++) {
			int temp; cin >> temp;
			a[temp-1] = 1;
		}
		int i = 0;
		while (x > 0) {
			if (a[i] == 0) {
				a[i] = 1;
				x--;
			}
			i++;
		}
		while (i < 300) {
			if (a[i] == 0) break;
			i++;
		}
		cout << i << endl;
	}
}