#include <bits/stdc++.h>
using namespace std;

int last(int b) {return b - 10*(b/10) ;}

int swapD(int a, int b) {
	int a1 = a/10, a2 = last(a), b1 = b/10, b2 = last(b);
	return 10*(b1+b2) + a1 + a2;
}

int main() {
	int t; cin >> t;

	while(t--) {
		int a, b; cin >> a >> b;
		int c = min(a, b);
		int d = max(a, b);
		a = c; b = d;

		if (d > 9) {
			if (c < 10) {
				if (c > d/10) {
					c = b/10;
					d = 10*a + last(b);
				}
				cout << c + d << endl;
			}
			else {
				cout << max(c+d, max(swapD(c, d), swapD(d, c))) << endl;
			}
		}
		else cout << c+d << endl;
	}
}