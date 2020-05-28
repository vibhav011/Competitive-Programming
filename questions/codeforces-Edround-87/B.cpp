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
		string s; cin >> s;
		int ans = 200005;
		int l[3] = {-1, -1, -1};

		for (int i = 0; i < s.size(); i++) {
			l[s[i] - '1'] = i;
			if (l[0] == -1 || l[1] == -1 || l[2] == -1) continue;
			ans = min(ans, max(l[0], max(l[1], l[2])) - min(l[0], min(l[1], l[2])) + 1);
		}
		if (ans == 200005) cout << "0\n";
		else cout << ans << endl;
	}
}