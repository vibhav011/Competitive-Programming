#include <bits/stdc++.h>
#define ll long long
#define int long long
#define pii pair<ll, ll> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back

using namespace std;

int gcd(int a, int b) {
	if (a > b) swap(a, b);
	if (a == 0) return b;
	if (b%a == 0) return a;
	return gcd(b%a, a);
}

int sgn(int a) {
	if (a < 0) return -1;
	if (a == 0) return 0;
	return 1;
} 

signed main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		pair<pii, pii> arr[n];
		map<pair<pii, pii>, int> cnt;
		int ans = 0;
		int x, y, u, v;
		int a, b;
		for (int i= 0; i < n; i++) {
			cin >> x >> y >> u >> v;

			a = (x-u)*(x-u);
			b = (y-v)*(y-v);
			int gc = gcd(a, a+b);
			arr[i].ff = mp(sgn(x-u)*a/gc, (a+b)/gc);
			gc = gcd(b, a+b);
			arr[i].ss = mp(sgn(y-v)*b/gc, (a+b)/gc);
			cnt[arr[i]]++;
		}
		for (int i = 0; i < n; i++) {
			ans += cnt[mp(mp(-arr[i].ff.ff, arr[i].ff.ss), mp(-arr[i].ss.ff, arr[i].ss.ss))];
		}
		cout << ans/2 << endl;
	}
	
}

