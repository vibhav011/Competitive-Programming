#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;

		string x; cin >> x;

		string a = "1", b = "1";

		bool oneFound = false;

		for (int i = 1; i < n; i++) {
			char c = x[i];

			if (c == '0') {a += '0'; b += '0';}
			else if (c == '1') {
				if (!oneFound) {
					a += '1';
					b += '0';
					oneFound = true;
				}
				else {
					a += '0';
					b += '1';
				}
			}
			if (c == '2') {
				if (oneFound) {
					a += '0';
					b += '2';
				}
				else {
					a += '1';
					b += '1';
				}
			}
		}
		cout << a << endl << b << endl;
	}
}