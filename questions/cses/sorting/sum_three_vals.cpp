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

	ll n, x, y; cin >> n >> x;
	vector<pll> a(n);
	for (int i = 0; i < n; i++) {
		cin >> y;
		a[i] = mp(y, i);
	}
	sort(a.begin(), a.end());
	for (int i = 0; i < n-2 && a[i].ff <= x/3; i++) {
		for (int k = i+1; k < n-1 && a[k].ff <= (x-a[i].ff)/2; k++) {
			int j = upper_bound(a.begin(), a.end(), mp(x-a[i].ff-a[k].ff, n)) - a.begin() - 1;
			if (j > k && a[j].ff == x-a[i].ff-a[k].ff) {
				cout << a[i].ss+1 << ' ' << a[k].ss+1 << ' ' << a[j].ss+1 << endl;
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE\n";
}

