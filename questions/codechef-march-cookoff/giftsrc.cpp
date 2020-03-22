#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string s; cin >> s;

		int x = 0, y = 0;
		bool horizontal = !(s[0] == 'L' || s[0] == 'R');

		for (int i = 0; i < n; i++) {
			if (s[i] == 'L' && !horizontal) {x--; horizontal = true;}
			else if (s[i] == 'R' && !horizontal) {x++; horizontal = true;}
			else if (s[i] == 'U' && horizontal) {y++; horizontal = false;}
			else if (s[i] == 'D' && horizontal) {y--; horizontal = false;}
		}
		cout << x << ' ' << y << endl;
	}
}