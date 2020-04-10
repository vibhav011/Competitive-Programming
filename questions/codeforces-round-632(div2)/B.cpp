#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main () {
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int a[n], b[n];
		bool m_one = false, one = false;
		int m_ind = n, ind = n;
		bool notpos = false;

		for (int i = 0; i < n; i++) {
			cin >> a[i];
			if (a[i] == 1 && !one) {
				one = true;
				ind = i;
			}
			if (a[i] == -1 && !m_one) {
				m_one = true;
				m_ind = i;
			}
		}
		for (int i = 0; i < n; i++) {
			cin >> b[i];
			if (b[i] > a[i] && ind >= i) notpos = true;
			else if (b[i] < a[i] && m_ind >= i) notpos = true;
		}
		if (notpos) cout << "NO\n";
		else cout << "YES\n";
	}

	return 0;
}