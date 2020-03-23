#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 0; i < 2*k; i++) {
		int x, y;
		cin >> x >> y;
	}
	cout << 2*n*m-2 << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n-1; j++) {
			if (i%2) cout << 'U';
			else cout << 'D'; 
		}
		if (i != m-1) cout << 'R';
	}
	int startUp = m%2;
	for (int i = startUp; i < m+startUp; i++) {
		for (int j = 0; j < n-1; j++) {
			if (i%2) cout << 'U';
			else cout << 'D'; 
		}
		if (i != m+startUp-1) cout << 'L';
	}
	cout << endl;
}