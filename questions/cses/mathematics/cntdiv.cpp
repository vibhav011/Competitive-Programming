#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

const ll mod = 1e9+7;

int main () {
	int t; cin >> t;

	while (t--) {
		int x; cin >> x;
		if (x==1) {
			cout << "1\n";
			continue;
		}
		int ans = 2;
		int sq = sqrt(x);
		for (int i = 2; i <= sq; i++) {
			if (x%i == 0) ans += 2;
		}
		if (sq*sq == x) ans--;
		cout << ans << endl;
	}
}