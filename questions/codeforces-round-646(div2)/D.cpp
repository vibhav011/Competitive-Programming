#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define ffs fflush(stdout)

using namespace std;

void prnt(int a, int b, vector<int> sets[], int prsum[]) {
	cout << "? " << prsum[b] - ((a) ? prsum[a-1] : 0) << ' ';
	for (int i = a; i <= b; i++) {
		for (int j = 0; j < sets[i].size(); j++) cout << sets[i][j] << ' ';
	}
	cout << endl; ffs;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int t; cin >> t;
	
	while (t--) {
		int n, k;
		cin >> n >> k;
		vector<int> sets[k];
		int prsum[k];
		for (int i = 0; i < k; i++) {
			int c; cin >> c;
			if (i) prsum[i] = c + prsum[i-1];
			else prsum[i] = c;
			while (c--) {
				int a; cin >> a;
				sets[i].pb(a);
			}
		}
		cout << "? " << n << ' ';
		for (int i = 1; i <= n; i++) cout << i << ' ';
		cout << endl; ffs;
		int mx; cin >> mx;

		int st = 0, en = k-1, mid = (k-1)/2;
		prnt(st, mid, sets, prsum);
		int inp; cin >> inp;
		while (st < mid && inp != -1) {
			if (inp < mx) st = mid+1;
			else en = mid;
			mid = (st+en)/2;
			prnt(st, mid, sets, prsum);
			cin >> inp;
		}
		if (inp == -1) return 0;

		if (inp < mx && st < k-1) st++;

		int haha[n+1]; memset(haha, 1, sizeof(haha));
		for (int i = 0; i < sets[st].size(); i++) haha[sets[st][i]] = 0;
		cout << "? " << n - sets[st].size() << ' ';
		for (int i = 1; i <= n; i++) if (haha[i]) cout << i << ' ';
		cout << endl; ffs;
		cin >> inp;

		if (inp == -1) return 0;

		cout << "! ";
		for (int i = 0; i < k; i++) {
			if (i == st) cout << inp << ' ';
			else cout << mx << ' ';
		}

		cout << endl; ffs;
		string s; cin >> s;
		if (s == "Incorrect") break;
	}
	return 0;
}

