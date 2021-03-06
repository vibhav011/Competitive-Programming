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

	int n; cin >> n;
	vector<pii> t;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		t.pb(mp(x, 1));
		t.pb(mp(y, -1));
	}
	sort(t.begin(), t.end());
	int ans = 0, cur = 0;
	for (int i = 0; i < 2*n; i++) {
		cur += t[i].ss;
		ans = max(ans, cur);
	}
	cout << ans << endl;
}

