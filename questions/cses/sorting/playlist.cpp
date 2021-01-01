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
	int a[n];
	for (int i = 0; i < n; i++) cin >> a[i];
	int ans = 0;
	set<int> ids;
	int left = 0, i = 0;
	while (i < n) {
		if (ids.find(a[i]) != ids.end()) {
			while (a[left] != a[i]) ids.erase(a[left++]);
			left++;
		}
		ids.insert(a[i++]);
		ans = max(ans, i-left);
	}
	cout << ans << endl;
}

