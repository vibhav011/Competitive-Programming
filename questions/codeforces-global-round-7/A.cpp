#include <iostream>
using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;

		if (n == 1) cout << -1 << endl;
		else {
			cout << 4;
			while (--n) cout << 3;
			cout << endl;
		}
	}
	return 0;
}