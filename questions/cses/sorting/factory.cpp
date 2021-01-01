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

	ll n, t;
	cin >> n >> t;
	ll k[n];
	for (int i = 0; i < n; i++) cin >> k[i];

	ll lo = 1, hi = 1LL << 60LL;
	ll mid, x;
	while (lo < hi) {
		mid = (lo + hi) >> 1LL;
		x = 0;
		for (int i = 0; i < n && x < t; i++) x += mid/k[i];
		if (x < t) lo = mid+1;
		else hi = mid;
	}
	cout << lo << endl;

}

