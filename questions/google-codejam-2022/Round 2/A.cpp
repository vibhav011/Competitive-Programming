#include <bits/stdc++.h>
#define ll long long
#define int ll
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
using namespace std;

vector<pii> ans;

bool solve(int st, int n, int dif, int aval) {
	if (n == 1 && dif != 0) return false;
	if (dif == 0) return true;

	int ar[] = {4*n-6, 4*n-8, 4*n-10, 4*n-12};

	int i = aval;
	while (ar[i] > dif && i < 4) i++;

	if (i == 4)
		return solve(st+4*n-4, n-2, dif, 0);
	
	int a = st+i*(n-1)+1;
	int b = a+ar[i]+1;
	ans.pb(mp(a, b));
	dif -= ar[i];
	return solve(st+4*n-4, n-2, dif, i);
}

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t; cin >> t;

	for (int cn = 1; cn <= t; cn++) {
		cout << "Case #" << cn << ": ";
		
		ans.clear();

		int n, k;
		cin >> n >> k;
		int dif = n*n-1-k;

		if (dif&1) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		bool pos = solve(1, n, dif, 0);
		
		if (!pos) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		cout << ans.size() << '\n';
		for (auto &x : ans) {
			cout << x.ff << ' ' << x.ss << '\n';
		}
	}
}