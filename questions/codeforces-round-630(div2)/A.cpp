#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while(t--) {
		int a, b, c, d, x, y, x1, y1, x2, y2;
		cin >> a >> b >> c >> d;
		cin >> x >> y >> x1 >> y1 >> x2 >> y2;

		if ((a+b) && !(x2-x1)) cout << "NO" << endl;
		else if ((c+d) && !(y2-y1)) cout << "NO" << endl;
		else {
			if (x+b-a <= x2 && x+b-a >= x1 && y+d-c <= y2 && y+d-c >= y1) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
	return 0;
}