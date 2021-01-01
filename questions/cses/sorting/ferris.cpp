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

	int n, x;
	cin >> n >> x;
	vector<int> p(n), done(n, 0);
	for (int i = 0; i < n; i++) cin >> p[i];
	sort(p.begin(), p.end());
	int ans = 0;
	for (int i = n-1; i >= 0; i--) {
		if (done[i]) continue;
		done[i] = 1;
		ans++;
		int j = upper_bound(p.begin(), p.begin()+i, x-p[i]) - p.begin();
		if (!j) continue;
		j--;
		while (j >= 0 && done[j]) j--;
		if (j >= 0) done[j] = 1;
	}
	cout << ans << endl;
}

