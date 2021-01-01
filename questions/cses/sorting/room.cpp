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
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n; cin >> n;
	vector<pair<pii, int> > t;
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		t.pb(mp(mp(x, 1), i));
		t.pb(mp(mp(y+1, -1), i));
	}
	sort(t.begin(), t.end());
	int ans = 0, cur = 0;
	vector<int> al(n);
	set<int> occ, aval;
	set<int>::iterator it;

	for (int i = 0; i < 2*n; i++) {
		cur += t[i].ff.ss;
		ans = max(ans, cur);
		if (t[i].ff.ss == 1) {
			if (aval.empty()) occ.insert(al[t[i].ss] = cur);
			else {
				it = aval.begin();
				al[t[i].ss] = *it;
				occ.insert(*it);
				aval.erase(it);
			}
		}
		else {
			occ.erase(al[t[i].ss]);
			aval.insert(al[t[i].ss]);
		}
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++) cout << al[i] << ' ';
	cout << endl;
}

