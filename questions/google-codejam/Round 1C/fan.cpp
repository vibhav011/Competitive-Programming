#include <iostream>
using namespace std;

int main () {
	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		int x, y;
		cin >> x >> y;
		string s; cin >> s;
		int i = 1;
		bool found = false;
		for (; i < s.size()+1; i++) {
			char c = s[i-1];
			if (c == 'N') y++;
			else if (c == 'S') y--;
			else if (c == 'E') x++;
			else x--;
			if (i >= abs(x) + abs(y)) {
				found = true;
				break;
			}
		}
		printf("Case #%d: ", cn);
		if (found) {
			cout << i << endl;
		}
		else cout << "IMPOSSIBLE\n";
	}
}