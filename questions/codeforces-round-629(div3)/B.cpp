#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		long long int n, k; cin >> n >> k;

		long long int p = (1+sqrt(1 + 8*k))/2;
		if (p*(p-1) == 2*k) p--;

		int d = k - p*(p-1)/2;

		for (int i = 1; i <= n-p-1; i++) cout << 'a';
		cout << 'b';
		for (int i = 1; i <= p-d; i++) cout << 'a';
		cout << 'b';
		for (int i = 1; i <= d-1; i++) cout << 'a';
		cout << endl;

	}
}