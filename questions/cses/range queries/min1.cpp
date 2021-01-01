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

	int n, q;
	cin >> n >> q;
	int sparse[n+1][18];

	for (int i = 0; i < n; i++) cin >> sparse[i][0];

	int sz = 1; int l = 2;
	while (l <= n) {
		for (int i = 0; i < n-l+1; i++) sparse[i][sz] = min(sparse[i][sz-1], sparse[i + (l>>1)][sz-1]);
		sz++; l <<= 1;
	}

	while (q--) {
		int a, b; cin >> a >> b;
		int len = b-a+1;
		int d = -1;
		while (len) {
			d++;
			len >>= 1;
		}
		cout << min(sparse[a-1][d], sparse[b-(1<<d)][d]) << '\n';
	}
}

