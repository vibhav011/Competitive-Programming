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
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		set<int> xp, yp;
		for (int i = 1; i < 4*n; i++) {
			int x, y;
			cin >> x >> y;
			if (xp.find(x) == xp.end()) xp.insert(x);
			else xp.erase(x);
			if (yp.find(y) == yp.end()) yp.insert(y);
			else yp.erase(y);
		}
		cout << *xp.begin() << ' ' << *yp.begin() << endl;
	}
	
}

