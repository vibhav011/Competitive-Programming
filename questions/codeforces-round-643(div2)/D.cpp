#include <bits/stdc++.h>
using namespace std;

int main () {
	int n, s;
	cin >> n >> s;
	if (s >= 2*n) {
		cout << "YES\n";
		for (int i = 1; i <= n-1; i++) cout << 1 << ' ';
		cout << s-n+1 << endl << n << endl;
	}
	else cout << "NO\n";
}