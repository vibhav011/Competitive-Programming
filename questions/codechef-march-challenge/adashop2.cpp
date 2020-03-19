#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int r, c;
		cin >> r >> c;

		if (r == 1 && c == 1) cout << 25 << endl;
		else if (r == c) {
			cout << 26 << endl;
			cout << 1 << ' ' << 1 << endl;
		}
		else {
			cout << 27 << endl;
			cout << (r+c)/2 << ' ' << (r+c)/2 << endl;
			cout << 1 << ' ' << 1 << endl;
		}

		int x = 1, y = 1;
		for (int i = 0; i < 6; i++) {
			cout << (++x) << ' ' << (++y) << endl;
			if (x < 5) {
				cout << 1 << ' ' << (x+y-1) << endl;
				cout << (x+y-1) << ' ' << 1 << endl;
			}
			else {
				cout << (x+y-8) << ' ' << 8 << endl;
				cout << 8 << ' ' << (x+y-8) << endl;
			}
			cout << x << ' ' << y << endl;
		}
		cout << 8 << ' ' << 8 << endl;
	}
}