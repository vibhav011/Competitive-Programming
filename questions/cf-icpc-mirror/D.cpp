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
		int n, m, a, b;
		cin >> n >> m >> a >> b;
		int s[m+1]; s[0] = 0;
		for (int i = 0; i < m; i++) cin >> s[i+1];
		sort(s, s+m+1);
		for (int i = 1; i <= m; i++) s[i] += m+1-i;
		int pref[m+1];
		pref[0] = 0;
		for (int i = 1; i <= m; i++) pref[i] = max(pref[i-1], s[i]);

		if (a > b) {
			a = n-a+1;
			b = n-b+1;
		}
		int k = min(b-a-1, m);
		while (k > 0 && pref[k]-(m-k) >= b) k--;
		cout << k << endl;
	}
	
}

