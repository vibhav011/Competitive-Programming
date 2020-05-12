#include <bits/stdc++.h>
#define ll long long int
#define pll pair<ll, ll> 
#define pii pair<int, int> 
#define ff first
#define ss second
#define MAX 200005

using namespace std;

ll MOD = 998244353;

ll pwr(ll x, ll y) {
	ll res = 1;
	while (y > 0) {
		if (y&1) res = res*x;

		y = y>>1;
		x = x*x;
	}
	return res;
}

inline ll addmod(ll a, ll b){
	return ((a+b)%MOD);
}

inline ll mulmod(ll a, ll b){
	return ((a*b)%MOD);
}

int main () {
	int t; cin >> t;

	while (t--) {
		int n, k;
		cin >> n >> k;
		bool imp = true;
		int a[n];
		vector<int> ind;

		for (int i = 0; i < n; i++) {
			cin >> a[i];
			if (a[i] >= k) {
				ind.push_back(i);
				if (a[i] == k) imp = false;
			}
		}
		if (imp) {
			cout << "no\n";
			continue;
		}

		if (n == 1) {
			cout << "yes\n";
			continue;
		}

		bool found = false;

		for (int i = 1; i < ind.size(); i++) {
			if (ind[i]-ind[i-1] < 3) {
				found = true;
				break;
			}
		}

		if (found) cout << "yes\n";
		else cout << "no\n";

	}

	return 0;
}