#include <bits/stdc++.h>
using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		int a[9][9];
		for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) {
			char c; cin >> c;
			a[i][j] = c - '0';
			if ((i*3+i/3)%9 == j) a[i][j] = (a[i][j] == 9) ? 8 : a[i][j]+1;
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) cout << a[i][j];
			cout << endl;
		}
	}
}