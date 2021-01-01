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

	int n, m, k;
	cin >> n >> m >> k;
	int a[n], b[m];
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];

	int p = 0, q = 0;
	sort(a, a+n);
	sort(b, b+m);
	int ans = 0;
	while (p < n && q < m) {
		if (b[q] < a[p]-k) q++;
		else if (b[q] > a[p]+k) p++;
		else {
			ans++;
			p++; q++;
		}
	}
	cout << ans << endl;
}

