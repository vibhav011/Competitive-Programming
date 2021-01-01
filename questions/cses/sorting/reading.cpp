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
	ll sum = 0, mx = 0;
	ll a;
	for (int i = 0; i < n; i++) {
		cin >> a;
		sum += a;
		mx = max(mx, a);
	}
	cout << max(2*mx, sum) << endl;
}

