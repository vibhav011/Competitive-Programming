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
	vector<int> t;
	while (n--) {
		int x; cin >> x;
		if (t.empty()) t.pb(x);
		else {
			int i = upper_bound(t.begin(), t.end(), x) - t.begin();
			if (i == t.size()) t.pb(x);
			else t[i] = x;
		}
	}
	cout << t.size() << endl;
}

