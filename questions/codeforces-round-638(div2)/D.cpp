#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		
		int n2 = n;

		int b = 0;
		while (n2 > 0) {
			b++;
			n2 >>= 1;
		}
		b--;
		int x = n - (1 << b) + 1;
		if (!(n & (n+1))) {x= 0;cout << b << endl;}
		else cout << b+1 << endl;
		for (int i = 1; i <= b; i++) {
			if ((1 << (i-1)) <= x && x <= (1 << i)) {
				cout << x << ' ';
				x = -1;
				i--;
			}
			else cout << (1 << i) << ' ';
		}
		cout << endl;
	}
}