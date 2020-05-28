#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int main () {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		pair<int, pii> ar[n];

		for (int i = 0; i < n; i++) {
			cin >> ar[i].ss.ff >> ar[i].ss.ss >> ar[i].ff;
		}

		bool imp = false;
		for (int i = 0; i < n && !imp; i++) {
			int x = ar[i].ss.ff, y = ar[i].ss.ss;
			int cnt = 1;
			for (int j = 0; j < n; j++) {
				if (i == j || ar[j].ff != ar[i].ff) continue;

				if (y >= ar[j].ss.ff && x <= ar[j].ss.ss) {
					x = max(ar[j].ss.ff, x);
					y = min(ar[j].ss.ss, y);
					cnt++;
				}
				if (cnt == 3) {
					imp = true;
					break;
				}
			}
		}
		if (imp) cout << "NO\n";
		else cout << "YES\n";
	}
}
