#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		long long int n, k;
		cin >> n >> k;

		if (n < k*k || n%2 != k%2) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
}